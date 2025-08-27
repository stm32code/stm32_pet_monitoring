#include "PWM.h"

void PWM_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	TIM_OCInitTypeDef TIM_OCInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
//	GPIO_ResetBits(GPIOB,GPIO_Pin_9);
	
	//定时器初始化
	TIM_TimeBaseStruct.TIM_Period=9999;//初值
	TIM_TimeBaseStruct.TIM_Prescaler=143;//预分频
	TIM_TimeBaseStruct.TIM_ClockDivision=0;
	TIM_TimeBaseStruct.TIM_CounterMode=TIM_CounterMode_Up;//向上
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStruct);
	
	//pwm 初始化
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;

	TIM_OC1Init(TIM4,&TIM_OCInitStructure);
//	TIM_OC2Init(TIM4,&TIM_OCInitStructure);
//	TIM_OC3Init(TIM4,&TIM_OCInitStructure);
//  TIM_OC4Init(TIM4,&TIM_OCInitStructure);
	
	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
//  TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
//	TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);
//	TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable);
	
	TIM_Cmd(TIM4,ENABLE);

	TIM_SetCompare1(TIM4,400);
//	TIM_SetCompare2(TIM4,400);
//	TIM_SetCompare3(TIM4,400);
//	TIM_SetCompare4(TIM4,400);
}

void pwm1(){
	printf("舵机1运转\n\r");
		TIM_SetCompare1(TIM4,1200);//打开
		delay_ms( 1000 );
		delay_ms( 1000 );
		delay_ms( 1000 );
		delay_ms( 1000 );
		TIM_SetCompare1(TIM4,400);//时间到关闭
		delay_ms( 1000 );
		delay_ms( 1000 );
		delay_ms( 1000 );
		delay_ms( 1000 );
}

void pwm2(){
	printf("舵机2运转\n\r");
		TIM_SetCompare2(TIM4,1200);//打开
		delay_ms( 1000 );
		delay_ms( 1000 );
		delay_ms( 1000 );
		delay_ms( 1000 );
		TIM_SetCompare2(TIM4,400);//时间到关闭
		delay_ms( 1000 );
		delay_ms( 1000 );
		delay_ms( 1000 );
		delay_ms( 1000 );
}

void pwm3(){
	printf("舵机3运转\n\r");
		TIM_SetCompare3(TIM4,1200);//打开
		delay_ms( 1000 );
		delay_ms( 1000 );
		delay_ms( 1000 );
		delay_ms( 1000 );
		TIM_SetCompare3(TIM4,400);//时间到关闭
		delay_ms( 1000 );
		delay_ms( 1000 );
		delay_ms( 1000 );
		delay_ms( 1000 );
}

void pwm4(){ 
	printf("舵机4运转\n\r");
		TIM_SetCompare4(TIM4,1200);//打开
		delay_ms( 1000 );
		delay_ms( 1000 );
		delay_ms( 1000 );
		delay_ms( 1000 );
		TIM_SetCompare4(TIM4,400);//时间到关闭
		delay_ms( 1000 );
		delay_ms( 1000 );
		delay_ms( 1000 );
		delay_ms( 1000 );
}