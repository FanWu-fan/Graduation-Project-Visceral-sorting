#include "faststop.h"
#include "delay.h"
#include "usart.h"

//������ʼ������
void KEY_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOG,ENABLE);//ʹ��PORTEʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;//KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE2
	
// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //LED0-->PB.5 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
// GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
// GPIO_ResetBits(GPIOB,GPIO_Pin_5);						 //PB.5 �����

// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //LED1-->PE.5 �˿�����, �������
// GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
// GPIO_SetBits(GPIOE,GPIO_Pin_5); 						 //PE.5 ����� 
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //LED1-->PE.5 �˿�����, �������
 GPIO_Init(GPIOG, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_SetBits(GPIOG,GPIO_Pin_5); 						 //PE.5 ����� 	

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;				 //LED0-->PB.5 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //��������
 GPIO_Init(GPIOE, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5	
	
}  
  
  
//�ⲿ�ж�2�������
void FASTSTOP_Init(void)
{
 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

      KEY_Init();	 //	�����˿ڳ�ʼ��
	
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��

    //GPIOE.2 �ж����Լ��жϳ�ʼ������   �½��ش���
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line2;	//KEY2
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;	      //ʹ�ܰ���KEY���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//��ռ���ȼ�0�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//�����ȼ�0
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 




}

//�ⲿ�ж�2������� 
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
	EXTI_ClearITPendingBit(EXTI_Line2); //���LINE2�ϵ��жϱ�־λ  

}
 
