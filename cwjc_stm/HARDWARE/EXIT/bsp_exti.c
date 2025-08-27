/**
  ******************************************************************************
  * @file    bsp_exti.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   I/O���ж�Ӧ��bsp
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:���� F103-ָ���� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "bsp_exti.h"

 /**
  * @brief  ����Ƕ�������жϿ�����NVIC
  * @param  ��
  * @retval ��
  */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* ����NVICΪ���ȼ���1 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* �����ж�Դ������1 */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  /* ������ռ���ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* ���������ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* ʹ���ж�ͨ�� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* �����ж�Դ������2������ʹ������������� */  
  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
  NVIC_Init(&NVIC_InitStructure);
	  /* �����ж�Դ������2������ʹ������������� */  
  NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
  NVIC_Init(&NVIC_InitStructure);
		  /* �����ж�Դ������2������ʹ������������� */  
  NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
  NVIC_Init(&NVIC_InitStructure);
		  /* �����ж�Դ������2������ʹ������������� */  
  NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
  NVIC_Init(&NVIC_InitStructure);
	
			  /* �����ж�Դ������2������ʹ������������� */  
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
  NVIC_Init(&NVIC_InitStructure);
	
//				  /* �����ж�Դ������2������ʹ������������� */  
//  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
//  NVIC_Init(&NVIC_InitStructure);
}

 /**
  * @brief  ���� IOΪEXTI�жϿڣ��������ж����ȼ�
  * @param  ��
  * @retval ��
  */
void EXTI_Key_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;

	/*��������GPIO�ڵ�ʱ��*/
	RCC_APB2PeriphClockCmd((RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO),ENABLE);
												
	/* ���� NVIC �ж�*/
	NVIC_Configuration();
	

		/*--------------------------KEY4����-----------------------------*/
	/* ѡ�񰴼��õ���GPIO */	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  /* ����Ϊ�������� */	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* ѡ��EXTI���ź�Դ */
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource3); 
  EXTI_InitStructure.EXTI_Line = EXTI_Line3;
	
	/* EXTIΪ�ж�ģʽ */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* �������ж� */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  /* ʹ���ж� */	
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
		/*--------------------------KEY5����-----------------------------*/
	/* ѡ�񰴼��õ���GPIO */	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  /* ����Ϊ�������� */	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* ѡ��EXTI���ź�Դ */
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource4); 
  EXTI_InitStructure.EXTI_Line = EXTI_Line4;
	
	/* EXTIΪ�ж�ģʽ */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* �������ж� */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  /* ʹ���ж� */	
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	
		/*--------------------------KEY6����-----------------------------*/
	/* ѡ�񰴼��õ���GPIO */	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  /* ����Ϊ�������� */	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* ѡ��EXTI���ź�Դ */
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource5); 
  EXTI_InitStructure.EXTI_Line = EXTI_Line5;
	
	/* EXTIΪ�ж�ģʽ */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* �������ж� */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  /* ʹ���ж� */	
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);


  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  /* ����Ϊ�������� */	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* ѡ��EXTI���ź�Դ */
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource6); 
  EXTI_InitStructure.EXTI_Line = EXTI_Line6;
	
	/* EXTIΪ�ж�ģʽ */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* �������ж� */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  /* ʹ���ж� */	
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	
}
/*********************************************END OF FILE**********************/
