#include "sys.h"
#include "usart.h"
/* �������´���,֧��printf����,������Ҫѡ��use MicroLIB */
#if 1
#pragma import(__use_no_semihosting)
/* ��׼����Ҫ��֧�ֺ��� */
struct __FILE
{
	int handle;
};

FILE __stdout;
/* ����_sys_exit()�Ա���ʹ�ð�����ģʽ */
_sys_exit( int x )
{
	x = x;
}
/* �ض���fputc���� */
int fputc( int ch, FILE *f )
{
	while ( (USART1->SR & 0X40) == 0 )
		;            /* ѭ������,ֱ��������� */
	USART1->DR = (u8) ch;
	return(ch);
}


#endif


#if EN_USART1_RX                /* ���ʹ���˽��� */
/*
 * ����1�жϷ������
 * ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���
 */
u8 USART_RX_BUF[USART_REC_LEN]; /* ���ջ���,���USART_REC_LEN���ֽ�. */
/*
 * ����״̬
 * bit15��	������ɱ�־
 * bit14��	���յ�0x0d
 * bit13~0��	���յ�����Ч�ֽ���Ŀ
 */
u16 USART_RX_STA = 0;           /* ����״̬��� */

void USART1_INIT( u32 bound )
{
	/* GPIO�˿����� */
	GPIO_InitTypeDef	GPIO_InitStructure;
	USART_InitTypeDef	USART_InitStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE );         /* ʹ��USART1��GPIOAʱ�� */

	/* USART1_TX   GPIOA.9 */
	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_9;                                           /* PA.9 */
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AF_PP;                                      /*����������� */
	GPIO_Init( GPIOA, &GPIO_InitStructure );                                                /* ��ʼ��GPIOA.9 */

	/* USART1_RX	  GPIOA.10��ʼ�� */
	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_10;                                          /* PA10 */
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_IN_FLOATING;                                /* �������� */
	GPIO_Init( GPIOA, &GPIO_InitStructure );                                                /* ��ʼ��GPIOA.10 */

	/* Usart1 NVIC ���� */
	NVIC_InitStructure.NVIC_IRQChannel			= USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 3;                            /* ��ռ���ȼ�3 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority		= 3;                            /* �����ȼ�3 */
	NVIC_InitStructure.NVIC_IRQChannelCmd			= ENABLE;                       /* IRQͨ��ʹ�� */
	NVIC_Init( &NVIC_InitStructure );                                                       /* ����ָ���Ĳ�����ʼ��VIC�Ĵ��� */

	/* USART ��ʼ������ */

	USART_InitStructure.USART_BaudRate		= bound;                                /* ���ڲ����� */
	USART_InitStructure.USART_WordLength		= USART_WordLength_8b;                  /* �ֳ�Ϊ8λ���ݸ�ʽ */
	USART_InitStructure.USART_StopBits		= USART_StopBits_1;                     /* һ��ֹͣλ */
	USART_InitStructure.USART_Parity		= USART_Parity_No;                      /* ����żУ��λ */
	USART_InitStructure.USART_HardwareFlowControl	= USART_HardwareFlowControl_None;       /* ��Ӳ������������ */
	USART_InitStructure.USART_Mode			= USART_Mode_Rx | USART_Mode_Tx;        /* �շ�ģʽ */

	USART_Init( USART1, &USART_InitStructure );                                             /* ��ʼ������1 */
	USART_ITConfig( USART1, USART_IT_RXNE, ENABLE );                                        /* �������ڽ����ж� */
	USART_Cmd( USART1, ENABLE );                                                            /* ʹ�ܴ���1 */


	TIM2_Int_Init( 1000 - 1, 7200 - 1 );                                                    /* 10ms�ж� */
	USART_RX_STA = 0;                                                                       /* ���� */
	TIM_Cmd( TIM2, DISABLE );                                                               /* �رն�ʱ��4 */
}


void TIM2_Int_Init( u16 arr, u16 psc )
{
	NVIC_InitTypeDef	NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM2, ENABLE );                  /* TIM3ʱ��ʹ�� */

	/* ��ʱ��TIM7��ʼ�� */
	TIM_TimeBaseStructure.TIM_Period	= arr;                          /* ��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ */
	TIM_TimeBaseStructure.TIM_Prescaler	= psc;                          /* ����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ */
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                 /* ����ʱ�ӷָ�:TDTS = Tck_tim */
	TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;           /* TIM���ϼ���ģʽ */
	TIM_TimeBaseInit( TIM2, &TIM_TimeBaseStructure );                       /* ����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ */

	TIM_ITConfig( TIM2, TIM_IT_Update, ENABLE );                            /* ʹ��ָ����TIM3�ж�,��������ж� */

	TIM_Cmd( TIM2, ENABLE );                                                /* ������ʱ��4 */

	NVIC_InitStructure.NVIC_IRQChannel			= TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 0;            /* ��ռ���ȼ�0 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority		= 2;            /* �����ȼ�2 */
	NVIC_InitStructure.NVIC_IRQChannelCmd			= ENABLE;       /* IRQͨ��ʹ�� */
	NVIC_Init( &NVIC_InitStructure );                                       /* ����ָ���Ĳ�����ʼ��VIC�Ĵ��� */
}


/* ��ʱ��4�жϷ������ */
void TIM2_IRQHandler( void )
{
//	printf( "usart1 end %s \r\n", USART_RX_BUF );
	/* printf("��ʱ��4�ж�\r\n"); */
	if ( TIM_GetITStatus( TIM2, TIM_IT_Update ) != RESET )          /* �Ǹ����ж� */
	{
		USART_RX_STA = 0;                                 /* ��ǽ������ */
		TIM_ClearITPendingBit( TIM2, TIM_IT_Update );           /* ���TIM3�����жϱ�־ */
		TIM_Cmd( TIM2, DISABLE );                               /* �ر�TIM3 */
		
//		printf( "\r\n usart1 end %s \r\n", USART_RX_BUF );
	}
}


void USART1_IRQHandler( void )                                          /* ����1�жϷ������ */
{
	u8 Res;


	if ( USART_GetITStatus( USART1, USART_IT_RXNE ) != RESET )      /* �����ж�(���յ������ݱ�����0x0d 0x0a��β) */
	{
		Res = USART_ReceiveData( USART1 );                      /* ��ȡ���յ������� */
		TIM_Cmd( TIM2, ENABLE );
		USART_RX_BUF[USART_RX_STA++] = Res;
		TIM_SetCounter( TIM2, 0 );
//		if ( (USART_RX_STA & (1 << 15) ) == 0 )                 /* �������һ������,��û�б�����,���ٽ����������� */
//		{
//			printf("1");
//			if ( USART_RX_STA < 1024 )                      /* �����Խ������� */
//			{
//				printf("2");
//				TIM_SetCounter( TIM2, 0 );              /* ���������                                        //��������� */
//				if ( USART_RX_STA == 0 )                /* ʹ�ܶ�ʱ��4���ж� */
//				{
//					TIM_Cmd( TIM2, ENABLE );        /* ʹ�ܶ�ʱ��4 */
//				}
//				USART_RX_BUF[USART_RX_STA++] = Res;     /* ��¼���յ���ֵ */
//				printf("%s",USART_RX_BUF);
//			}else{
//				USART_RX_STA |= 1 << 15;                /* ǿ�Ʊ�ǽ������ */
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
		len = USART_RX_STA & 0x3fff;                            /* �õ��˴ν��յ������ݳ��� */
		printf( "\r\n usart1:�����͵���ϢΪ:\r\n" );
		for ( t = 0; t < len; t++ )
		{
			USART_SendData( USART1, USART_RX_BUF[t] );      /* �򴮿�1�������� */
			while ( USART_GetFlagStatus( USART1, USART_FLAG_TC ) != SET )
				;                                       /* �ȴ����ͽ��� */
		}
		printf( "\r\n\r\n" );                                   /* ���뻻�� */
		USART_RX_STA = 0;
	}else{
		times++;
		if ( times % 200 == 0 )
			printf( "usart:����������,�Իس�������\r\n" );
	}
}


void USART1_Put_Char( unsigned char c )
{
	USART_SendData( USART1, c );
	while ( USART_GetFlagStatus( USART1, USART_FLAG_TXE ) == RESET )
		;
}


