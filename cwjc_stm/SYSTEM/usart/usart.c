#include "sys.h"
#include "usart.h"
/* 加入以下代码,支持printf函数,而不需要选择use MicroLIB */
#if 1
#pragma import(__use_no_semihosting)
/* 标准库需要的支持函数 */
struct __FILE
{
	int handle;
};

FILE __stdout;
/* 定义_sys_exit()以避免使用半主机模式 */
_sys_exit( int x )
{
	x = x;
}
/* 重定义fputc函数 */
int fputc( int ch, FILE *f )
{
	while ( (USART1->SR & 0X40) == 0 )
		;            /* 循环发送,直到发送完毕 */
	USART1->DR = (u8) ch;
	return(ch);
}


#endif


#if EN_USART1_RX                /* 如果使能了接收 */
/*
 * 串口1中断服务程序
 * 注意,读取USARTx->SR能避免莫名其妙的错误
 */
u8 USART_RX_BUF[USART_REC_LEN]; /* 接收缓冲,最大USART_REC_LEN个字节. */
/*
 * 接收状态
 * bit15，	接收完成标志
 * bit14，	接收到0x0d
 * bit13~0，	接收到的有效字节数目
 */
u16 USART_RX_STA = 0;           /* 接收状态标记 */

void USART1_INIT( u32 bound )
{
	/* GPIO端口设置 */
	GPIO_InitTypeDef	GPIO_InitStructure;
	USART_InitTypeDef	USART_InitStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE );         /* 使能USART1，GPIOA时钟 */

	/* USART1_TX   GPIOA.9 */
	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_9;                                           /* PA.9 */
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AF_PP;                                      /*复用推挽输出 */
	GPIO_Init( GPIOA, &GPIO_InitStructure );                                                /* 初始化GPIOA.9 */

	/* USART1_RX	  GPIOA.10初始化 */
	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_10;                                          /* PA10 */
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_IN_FLOATING;                                /* 浮空输入 */
	GPIO_Init( GPIOA, &GPIO_InitStructure );                                                /* 初始化GPIOA.10 */

	/* Usart1 NVIC 配置 */
	NVIC_InitStructure.NVIC_IRQChannel			= USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 3;                            /* 抢占优先级3 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority		= 3;                            /* 子优先级3 */
	NVIC_InitStructure.NVIC_IRQChannelCmd			= ENABLE;                       /* IRQ通道使能 */
	NVIC_Init( &NVIC_InitStructure );                                                       /* 根据指定的参数初始化VIC寄存器 */

	/* USART 初始化设置 */

	USART_InitStructure.USART_BaudRate		= bound;                                /* 串口波特率 */
	USART_InitStructure.USART_WordLength		= USART_WordLength_8b;                  /* 字长为8位数据格式 */
	USART_InitStructure.USART_StopBits		= USART_StopBits_1;                     /* 一个停止位 */
	USART_InitStructure.USART_Parity		= USART_Parity_No;                      /* 无奇偶校验位 */
	USART_InitStructure.USART_HardwareFlowControl	= USART_HardwareFlowControl_None;       /* 无硬件数据流控制 */
	USART_InitStructure.USART_Mode			= USART_Mode_Rx | USART_Mode_Tx;        /* 收发模式 */

	USART_Init( USART1, &USART_InitStructure );                                             /* 初始化串口1 */
	USART_ITConfig( USART1, USART_IT_RXNE, ENABLE );                                        /* 开启串口接受中断 */
	USART_Cmd( USART1, ENABLE );                                                            /* 使能串口1 */


	TIM2_Int_Init( 1000 - 1, 7200 - 1 );                                                    /* 10ms中断 */
	USART_RX_STA = 0;                                                                       /* 清零 */
	TIM_Cmd( TIM2, DISABLE );                                                               /* 关闭定时器4 */
}


void TIM2_Int_Init( u16 arr, u16 psc )
{
	NVIC_InitTypeDef	NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM2, ENABLE );                  /* TIM3时钟使能 */

	/* 定时器TIM7初始化 */
	TIM_TimeBaseStructure.TIM_Period	= arr;                          /* 设置在下一个更新事件装入活动的自动重装载寄存器周期的值 */
	TIM_TimeBaseStructure.TIM_Prescaler	= psc;                          /* 设置用来作为TIMx时钟频率除数的预分频值 */
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                 /* 设置时钟分割:TDTS = Tck_tim */
	TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;           /* TIM向上计数模式 */
	TIM_TimeBaseInit( TIM2, &TIM_TimeBaseStructure );                       /* 根据指定的参数初始化TIMx的时间基数单位 */

	TIM_ITConfig( TIM2, TIM_IT_Update, ENABLE );                            /* 使能指定的TIM3中断,允许更新中断 */

	TIM_Cmd( TIM2, ENABLE );                                                /* 开启定时器4 */

	NVIC_InitStructure.NVIC_IRQChannel			= TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 0;            /* 抢占优先级0 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority		= 2;            /* 子优先级2 */
	NVIC_InitStructure.NVIC_IRQChannelCmd			= ENABLE;       /* IRQ通道使能 */
	NVIC_Init( &NVIC_InitStructure );                                       /* 根据指定的参数初始化VIC寄存器 */
}


/* 定时器4中断服务程序 */
void TIM2_IRQHandler( void )
{
//	printf( "usart1 end %s \r\n", USART_RX_BUF );
	/* printf("定时器4中断\r\n"); */
	if ( TIM_GetITStatus( TIM2, TIM_IT_Update ) != RESET )          /* 是更新中断 */
	{
		USART_RX_STA = 0;                                 /* 标记接收完成 */
		TIM_ClearITPendingBit( TIM2, TIM_IT_Update );           /* 清除TIM3更新中断标志 */
		TIM_Cmd( TIM2, DISABLE );                               /* 关闭TIM3 */
		
//		printf( "\r\n usart1 end %s \r\n", USART_RX_BUF );
	}
}


void USART1_IRQHandler( void )                                          /* 串口1中断服务程序 */
{
	u8 Res;


	if ( USART_GetITStatus( USART1, USART_IT_RXNE ) != RESET )      /* 接收中断(接收到的数据必须是0x0d 0x0a结尾) */
	{
		Res = USART_ReceiveData( USART1 );                      /* 读取接收到的数据 */
		TIM_Cmd( TIM2, ENABLE );
		USART_RX_BUF[USART_RX_STA++] = Res;
		TIM_SetCounter( TIM2, 0 );
//		if ( (USART_RX_STA & (1 << 15) ) == 0 )                 /* 接收完的一批数据,还没有被处理,则不再接收其他数据 */
//		{
//			printf("1");
//			if ( USART_RX_STA < 1024 )                      /* 还可以接收数据 */
//			{
//				printf("2");
//				TIM_SetCounter( TIM2, 0 );              /* 计数器清空                                        //计数器清空 */
//				if ( USART_RX_STA == 0 )                /* 使能定时器4的中断 */
//				{
//					TIM_Cmd( TIM2, ENABLE );        /* 使能定时器4 */
//				}
//				USART_RX_BUF[USART_RX_STA++] = Res;     /* 记录接收到的值 */
//				printf("%s",USART_RX_BUF);
//			}else{
//				USART_RX_STA |= 1 << 15;                /* 强制标记接收完成 */
//				printf("3");
//			}
//		}
	}
}


#endif
void uart1_test( void )
{
	u32		len, t;
	static u32	times = 0;
	if ( USART_RX_STA & 0x8000 )
	{
		len = USART_RX_STA & 0x3fff;                            /* 得到此次接收到的数据长度 */
		printf( "\r\n usart1:您发送的消息为:\r\n" );
		for ( t = 0; t < len; t++ )
		{
			USART_SendData( USART1, USART_RX_BUF[t] );      /* 向串口1发送数据 */
			while ( USART_GetFlagStatus( USART1, USART_FLAG_TC ) != SET )
				;                                       /* 等待发送结束 */
		}
		printf( "\r\n\r\n" );                                   /* 插入换行 */
		USART_RX_STA = 0;
	}else{
		times++;
		if ( times % 200 == 0 )
			printf( "usart:请输入数据,以回车键结束\r\n" );
	}
}


void USART1_Put_Char( unsigned char c )
{
	USART_SendData( USART1, c );
	while ( USART_GetFlagStatus( USART1, USART_FLAG_TXE ) == RESET )
		;
}


