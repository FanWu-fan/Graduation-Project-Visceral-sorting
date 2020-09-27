#include "led.h"



//��ʼ��PD9Ϊ2��צ   PD8Ϊ1��צ  ��Ϊ�߱պ� ��Ϊ���ſ�
//LED IO��ʼ��

void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	 
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOD, &GPIO_InitStructure);					
 GPIO_ResetBits(GPIOD,GPIO_Pin_8);						 

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	    		 
 GPIO_Init(GPIOD, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_ResetBits(GPIOD,GPIO_Pin_9); 						
}
 
