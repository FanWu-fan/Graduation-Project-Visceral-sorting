#include "manipulator.h"
void Hanipulator_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);	 //使能PB,PE端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;				 //LED0-->PG.9 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOG, &GPIO_InitStructure);					 //根据设定参数初始化GPIOG.9
 GPIO_ResetBits(GPIOG,GPIO_Pin_9);						 //PB.5 输出高

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	    		 //LED1-->PG.10 端口配置, 推挽输出
 GPIO_Init(GPIOG, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
 GPIO_SetBits(GPIOG,GPIO_Pin_10); 						 //PG.10 输出高 
}
 
