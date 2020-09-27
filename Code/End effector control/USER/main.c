#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
 



 int main(void)
 {		
 	int m=0;
	
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	
	 
 	TIM3_PWM_Init_ch1_3(19999,71);	 //?P PWM频率=72000000/(20000*72)=50hz
	 LED_Init();
	
	TIM_SetCompare1(TIM3,Steer1_Pmb);
	TIM_SetCompare2(TIM3,Steer2_Pmb);	
	TIM_SetCompare3(TIM3,Steer3_Cath);

while(1)
{

	switch(USART_RX_STA)
	{
	
		case(1):                     //爪子合拢
		{
		for(m=1;m<=21;m++)
			{
			TIM_SetCompare1(TIM3,Steer1_Pmb+10*m);
	TIM_SetCompare2(TIM3,Steer2_Pmb+12*m);
			delay_ms(20);
			}
			TIM_SetCompare1(TIM3,Steer1_Cath);
	TIM_SetCompare2(TIM3,Steer2_Cath);
			USART_RX_STA=0;
             USART_SendData(USART1,0X23);//告知单片机1运动开始
             while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)!= SET); 			
			break;
		
		  }
		
		case(2):           //闭合爪子
		{
		GPIO_SetBits(GPIOD,GPIO_Pin_8);
	  GPIO_SetBits(GPIOD,GPIO_Pin_9);
			USART_RX_STA=0;
             USART_SendData(USART1,0X24);//告知单片机2运动开始
             while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)!= SET); 		
			break;
		
		}
		

		
		case(3):           //拉扯双爪,拉扯开鸭内脏
		{
			for(m=1;m<=100;m++)
			{TIM_SetCompare3(TIM3,Steer3_Cath+11*m);
				delay_ms(15);
			}
			TIM_SetCompare3(TIM3,Steer3_Depart);
			
		for(m=1;m<=42;m++)
			{	
			TIM_SetCompare1(TIM3,Steer1_Cath-10*m);
	TIM_SetCompare2(TIM3,Steer2_Cath-12*m);
			delay_ms(20);
			}
			TIM_SetCompare1(TIM3,Steer1_Depart);
	TIM_SetCompare2(TIM3,Steer2_Depart);
			USART_RX_STA=0;
             USART_SendData(USART1,0X25);//告知单片机2运动开始
             while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)!= SET); 			
			break;
		
		}
		
		case(4):			//分开左单爪
		{
			GPIO_ResetBits(GPIOD,GPIO_Pin_9);
		USART_RX_STA=0;
             USART_SendData(USART1,0X26);//告知单片机2运动开始
             while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)!= SET); 			
		break;
		}
	
		case(5):     //分开右端爪
		{ 
			GPIO_ResetBits(GPIOD,GPIO_Pin_8);
		USART_RX_STA=0;
             USART_SendData(USART1,0X27);//告知单片机2运动开始
             while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)!= SET); 			
			break;
		}
	
		case(6):    //双爪还原为垂直态，底板转化为catch状态
		{
		for(m=1;m<=100;m++)
			{TIM_SetCompare3(TIM3,Steer3_Depart-11*m);
				delay_ms(15);
			}
			TIM_SetCompare3(TIM3,Steer3_Cath);
			
		for(m=1;m<=21;m++)
			{
			TIM_SetCompare1(TIM3,Steer1_Depart+10*m);
	TIM_SetCompare2(TIM3,Steer2_Depart+11*m);
			delay_ms(20);
			}
			TIM_SetCompare1(TIM3,Steer1_Pmb);
	TIM_SetCompare2(TIM3,Steer2_Pmb);
			USART_RX_STA=0;
			break;
		}

	}
 }

}