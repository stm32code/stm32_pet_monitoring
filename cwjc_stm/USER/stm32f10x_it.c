/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h" 
#include "OLED_I2C.h"
extern int hruL ;
extern int hrdL;
extern float tempuL ;
extern float tempdL ;
extern int option ;
extern int cyTime ;
extern int cyTimeFlag;
extern int cy;
 
void NMI_Handler(void)
{
}
 
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}
 
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

 
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}
 
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}
 
void SVC_Handler(void)
{
}
 
void DebugMon_Handler(void)
{
}
 
void PendSV_Handler(void)
{
}
 
void SysTick_Handler(void)
{
}

void EXTI3_IRQHandler(void)
{
  //确保是否产生了EXTI Line中断
	if(EXTI_GetITStatus(EXTI_Line3) != RESET) 
	{
			
		printf("\n\r 333 \n\r");
    //清除中断标志位
		EXTI_ClearITPendingBit(EXTI_Line3);     
	}  
}

void EXTI4_IRQHandler(void)
{
	u8		str[100];
	delay_ms( 300 );
  //确保是否产生了EXTI Line中断
	if(EXTI_GetITStatus(EXTI_Line4) != RESET) 
	{
		printf("\n\r 444 cyTime:%d\n\r",cyTime);
		if(cyTime == 0){
			cyTime = 60;
		}else if(cyTime == 60){
			cyTime = 120;
		}else if(cyTime == 120){
			cyTime = 180;
		}else if(cyTime == 180){
			cyTime = 240;
		}else if(cyTime == 240){
			cyTime = 300;
		}else if(cyTime == 300){
			cyTime = 0;
		}
    //清除中断标志位
		EXTI_ClearITPendingBit(EXTI_Line4);     
	}  
}
void EXTI9_5_IRQHandler(void)
{
	u8		str[100];
	
	delay_ms( 300 );
  //确保是否产生了EXTI Line中断
	if(EXTI_GetITStatus(EXTI_Line5) != RESET) 
	{
		printf("\n\r 555 \n\r");		
		if(cyTimeFlag == 0){
			cyTimeFlag = 1;
		}else{
			cyTime = 0;
			cyTimeFlag = 1;
		}
    //清除中断标志位
		EXTI_ClearITPendingBit(EXTI_Line5);     
	}  
	
	
	if(EXTI_GetITStatus(EXTI_Line6) != RESET) 
	{
		printf("\n\r 666 \n\r");	
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		cyTime = 0;
		cyTimeFlag = 0;
		cy = 1;
    //清除中断标志位
		EXTI_ClearITPendingBit(EXTI_Line6);     
	}  

}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
