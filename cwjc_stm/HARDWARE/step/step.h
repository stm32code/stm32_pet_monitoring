#ifndef  __STEP_H
#define __STEP_H
#include "stdbool.h"
void Step_Motor_GPIO_Init(void);
void SetMotor(unsigned char InputData);//���ݴ��͵�����Inputdata���������������
void motorNcircle(int n,bool position);//nΪ�������ת����Ȧ����positionΪ��ת���߷�ת


#endif

