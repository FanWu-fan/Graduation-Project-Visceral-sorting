#include "manipulator.h"
void Hanipulator_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;				 //LED0-->PG.9 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOG, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOG.9
 GPIO_ResetBits(GPIOG,GPIO_Pin_9);						 //PB.5 �����

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	    		 //LED1-->PG.10 �˿�����, �������
 GPIO_Init(GPIOG, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_SetBits(GPIOG,GPIO_Pin_10); 						 //PG.10 ����� 
}
 
