#include "faststop.h"
#include "delay.h"
#include "usart.h"

//按键初始化函数
void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOG,ENABLE);//使能PORTE时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;//KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE2
	
// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //LED0-->PB.5 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
// GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
// GPIO_ResetBits(GPIOB,GPIO_Pin_5);						 //PB.5 输出高

// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //LED1-->PE.5 端口配置, 推挽输出
// GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
// GPIO_SetBits(GPIOE,GPIO_Pin_5); 						 //PE.5 输出高 
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //LED1-->PE.5 端口配置, 推挽输出
 GPIO_Init(GPIOG, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
 GPIO_SetBits(GPIOG,GPIO_Pin_5); 						 //PE.5 输出高 	

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;				 //LED0-->PB.5 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //推挽输入
 GPIO_Init(GPIOE, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5	
	
}  
  
  
//外部中断2服务程序
void FASTSTOP_Init(void)
{
 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

      KEY_Init();	 //	按键端口初始化
	
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟

    //GPIOE.2 中断线以及中断初始化配置   下降沿触发
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line2;	//KEY2
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;	      //使能按键KEY所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//抢占优先级0， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//子优先级0
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 




}

//外部中断2服务程序 
void EXTI2_IRQHandler(void)
{
     TIM_Cmd(TIM1, DISABLE);
     TIM_Cmd(TIM2, DISABLE);	
     TIM_Cmd(TIM3, DISABLE);
     TIM_Cmd(TIM4, DISABLE);
     TIM_Cmd(TIM8, DISABLE);
     TIM_Cmd(TIM5, DISABLE);
     //PBout(5)=!PBout(5);	
	delay_ms(1000);
	printf("ENTER\r\n ");	
	EXTI_ClearITPendingBit(EXTI_Line2); //清除LINE2上的中断标志位  

}
 
