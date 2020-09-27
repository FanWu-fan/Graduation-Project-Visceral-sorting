#include "pwm.h"
#include  "string.h"

/*���1ʹ�õ���Slave Timer   TIM4*/
void Initial_Motor1_SlaveTimer(void)
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	memset(&TIM_OCInitStructure,0,sizeof(TIM_OCInitStructure));
	memset(&TIM_TimeBaseStructure,0,sizeof(TIM_TimeBaseStructure));
	
	/*����ʹ��*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	TIM_DeInit(TIM4);
	//�ж�NVIC���ã������жϣ��������ȼ�
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;                 //�����¼�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =PWM1_PreemptionPriority;        //��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =PWM1_SubPriority;              //��Ӧ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //�����ж�
	NVIC_Init(&NVIC_InitStructure);

	//�趨��ʱ�����ڡ�Ԥ��Ƶ��
	TIM_TimeBaseStructure.TIM_Period = 65535;                        //�Զ�װ�ؼ���������ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;                  //ʱ�ӷָ�
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //����ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);               //��ʼ��
	
	/* Output Compare Inactive Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode                        = TIM_OCMode_Inactive;//���������ֵ����CCR��ǿ��Ϊ�͵�ƽ
	TIM_OCInitStructure.TIM_OCPolarity                = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState                = TIM_OutputState_Disable;
	TIM_OCInitStructure.TIM_Pulse                        = 0xFFFF;                                       
    
      TIM_OC1Init(TIM4, &TIM_OCInitStructure);
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);
	
	/* Slave Mode selection: TIM4 */
	TIM_SelectSlaveMode(TIM4, TIM_SlaveMode_External1);
	TIM_SelectInputTrigger(TIM4, TIM_TS_ITR0);
	
	TIM4->CNT=0;
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM4, DISABLE);
	
}
/*���2ʹ�õ���Slave Timer  TIM8*/
void Initial_Motor2_SlaveTimer(void)
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	memset(&TIM_OCInitStructure,0,sizeof(TIM_OCInitStructure));
	memset(&TIM_TimeBaseStructure,0,sizeof(TIM_TimeBaseStructure));
	
	/*����ʹ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	TIM_DeInit(TIM8);
	//�ж�NVIC���ã������жϣ��������ȼ�
	NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_IRQn;                 //�����¼�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =PWM2_PreemptionPriority;        //��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =PWM2_SubPriority;              //��Ӧ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //�����ж�
	NVIC_Init(&NVIC_InitStructure);

	//�趨��ʱ�����ڡ�Ԥ��Ƶ
	TIM_TimeBaseStructure.TIM_Period = 32;                        //�Զ�װ�ؼ���������ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;                  //ʱ�ӷָ�
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //����ģʽ
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);               //��ʼ��
#if 1
	/* Output Compare Active Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode                        = TIM_OCMode_Inactive;
	TIM_OCInitStructure.TIM_OCPolarity                = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState                = TIM_OutputState_Disable;
	TIM_OCInitStructure.TIM_Pulse                        = 32;                                       
      TIM_OC1Init(TIM8, &TIM_OCInitStructure);
	TIM_ClearFlag(TIM8, TIM_FLAG_Update);
#endif
	/* Slave Mode selection: TIM8 */
	//Clk from TIM2
	TIM_SelectSlaveMode(TIM8, TIM_SlaveMode_External1);
	TIM_SelectInputTrigger(TIM8, TIM_TS_ITR1);	
	
	TIM8->CNT=0;
	TIM_ITConfig(TIM8, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM8, DISABLE);
	
}

/*���3ʹ�õ���Slave Timer TIM5*/
void Initial_Motor3_SlaveTimer(void)
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	memset(&TIM_OCInitStructure,0,sizeof(TIM_OCInitStructure));
	memset(&TIM_TimeBaseStructure,0,sizeof(TIM_TimeBaseStructure));
	
	/*����ʹ��*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	TIM_DeInit(TIM5);
	//�ж�NVIC���ã������жϣ��������ȼ�
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;                 //�����¼�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =PWM3_PreemptionPriority;        //��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =PWM3_SubPriority;              //��Ӧ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //�����ж�
	NVIC_Init(&NVIC_InitStructure);

	//�趨��ʱ�����ڡ�Ԥ��Ƶ��
	TIM_TimeBaseStructure.TIM_Period = 65535;                        //�Զ�װ�ؼ���������ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;                  //ʱ�ӷָ�
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //����ģʽ
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);               //��ʼ��
	
	/* Output Compare Active Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode                        = TIM_OCMode_Inactive;
	TIM_OCInitStructure.TIM_OCPolarity                = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState                = TIM_OutputState_Disable;
	TIM_OCInitStructure.TIM_Pulse                        = 0xFFFF;                                       
    
  TIM_OC1Init(TIM5, &TIM_OCInitStructure);
	TIM_ClearFlag(TIM5, TIM_FLAG_Update);
	/* Slave Mode selection: TIM5 */
	TIM_SelectSlaveMode(TIM5, TIM_SlaveMode_External1);
	TIM_SelectInputTrigger(TIM5, TIM_TS_ITR1);	
	
	TIM5->CNT=0;
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM5, DISABLE);
	
}



/*���1��PWM�����ʼ����ʹ�õ��Ƕ�ʱ��1*/
void Initial_PWM_Motor1(void)
{
	TIM_TimeBaseInitTypeDef TIM_BaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
      GPIO_InitTypeDef  GPIO_InitStructure;
	memset(&TIM_OCInitStructure,0,sizeof(TIM_OCInitStructure));//Ϊ��������ڴ�����ʼ������
	memset(&TIM_BaseInitStructure,0,sizeof(TIM_BaseInitStructure));
	
	/*����ʹ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
	TIM_DeInit(TIM1);

	/*ʹ�ܵ��ʹ�õ�������ʱ��PA8*/
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA| RCC_APB2Periph_AFIO, ENABLE);
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_InitStructure.GPIO_Pin =GPIO_Pin_8;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
      GPIO_Init(GPIOA, &GPIO_InitStructure);
      GPIO_ResetBits(GPIOA,GPIO_Pin_8);
	
	//�ж�NVIC���ã������жϣ��������ȼ�
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;     
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;   
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             
	NVIC_Init(&NVIC_InitStructure);
	
      //��ʼ����ʱ������
	TIM_BaseInitStructure.TIM_Period =800;	//�����Զ���װ��ֵ��Ƶ���趨Ϊ1000
	TIM_BaseInitStructure.TIM_Prescaler =71; 	//�趨��ʱ��Ԥ��Ƶ��
	TIM_BaseInitStructure.TIM_ClockDivision = 0;//ʱ�ӷָ�
	TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
	TIM_BaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_BaseInitStructure);
      
	//��ʼ������Ƚ�ͨ��
	TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM2;       //PWM2ģʽ
	TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable;  //�ź��������Ӧ���������
	TIM_OCInitStructure.TIM_Pulse = 150;   //������  CCR
	TIM_OC1Init(TIM1,&TIM_OCInitStructure);   //OC1ͨ����ʼ��

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);//ʹ��Ԥװ�ؼĴ���
	TIM_ARRPreloadConfig(TIM1, ENABLE);
	
	//���жϣ�����һ�����жϺ����������ж�
	TIM_ClearFlag(TIM1, TIM_FLAG_Update);
#ifndef MOTOR_PWM_USEDMA
	/* Select the Master Slave Mode */
	TIM_SelectMasterSlaveMode(TIM1, TIM_MasterSlaveMode_Enable);
	/* Master Mode selection */
	TIM_SelectOutputTrigger(TIM1, TIM_TRGOSource_Update);//������ʱ���ĸ����¼���Ϊ�������
	Initial_Motor1_SlaveTimer();//��ʼ���Ӷ�ʱ��
#else
	Initial_Motor1_DMA();
	/* ʹ��DMA*/         
  TIM_DMACmd(TIM1, TIM_DMA_Update, DISABLE);
#endif
      //TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM1,DISABLE);
	TIM_CtrlPWMOutputs(TIM1,ENABLE); //ʹ��PWM���
	//TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
	
}

/*���2��PWM�����ʼ����ʹ�õ��Ƕ�ʱ��2*/
void Initial_PWM_Motor2(void)
{
      TIM_TimeBaseInitTypeDef TIM_BaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
      GPIO_InitTypeDef  GPIO_InitStructure;	

	memset(&TIM_OCInitStructure,0,sizeof(TIM_OCInitStructure));
	memset(&TIM_BaseInitStructure,0,sizeof(TIM_BaseInitStructure));
	
	/*����ʹ��*/
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_DeInit(TIM2);
	
	/*ʹ�ܵ��ʹ�õ�������ʱ��PA0*/
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
      GPIO_Init(GPIOA, &GPIO_InitStructure);
      GPIO_ResetBits(GPIOA,GPIO_Pin_0);	
	
  //�ж�NVIC���ã������жϣ��������ȼ�
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;    //�����¼� 	TIM2_IRQHandler
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =PWM2_PreemptionPriority;   //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = PWM2_SubPriority;          //��Ӧ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //�����ж�
	NVIC_Init(&NVIC_InitStructure);
	
	//�趨��ʱ�����ڡ�Ԥ��Ƶ
	TIM_BaseInitStructure.TIM_Period =800;
	TIM_BaseInitStructure.TIM_Prescaler =71; 
	TIM_BaseInitStructure.TIM_ClockDivision = 0;
	TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_BaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_BaseInitStructure);	
	
	//PWMģʽ�����ã��ο�STM32�ĵ�
	TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM2;       //PWM2ģʽ 
	TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable;  //�ź��������Ӧ���������                  
	TIM_OCInitStructure.TIM_Pulse =150;   //������  
	TIM_OC1Init(TIM2,&TIM_OCInitStructure);   //OC1ͨ����ʼ��
	
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM2, ENABLE);
  //���жϣ�����һ�����жϺ����������ж�
//	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
#ifndef MOTOR_PWM_USEDMA	
	/* Select the Master Slave Mode */
	TIM_SelectMasterSlaveMode(TIM2, TIM_MasterSlaveMode_Enable);
	/* Master Mode selection */
	TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);
	Initial_Motor2_SlaveTimer();
#else
	Initial_Motor2_DMA();
	/* ʹ��DMA*/         
  TIM_DMACmd(TIM2, TIM_DMA_Update, ENABLE);
#endif
	TIM_Cmd(TIM2, DISABLE); 
}

/*���3��PWM�����ʼ����ʹ�õ��Ƕ�ʱ��3*/
void Initial_PWM_Motor3(void)
{
	TIM_TimeBaseInitTypeDef TIM_BaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
      GPIO_InitTypeDef  GPIO_InitStructure;	

	/*ʹ�ܵ��ʹ�õ�������ʱ��PA6*/
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_InitStructure.GPIO_Pin =GPIO_Pin_6;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
      GPIO_Init(GPIOA, &GPIO_InitStructure);
      GPIO_ResetBits(GPIOA,GPIO_Pin_6);	
	
	memset(&TIM_OCInitStructure,0,sizeof(TIM_OCInitStructure));
	memset(&TIM_BaseInitStructure,0,sizeof(TIM_BaseInitStructure));
	
	/*����ʹ��*/
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	TIM_DeInit(TIM3);
  
	//�ж�NVIC���ã������жϣ��������ȼ�
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;    //�����¼� 	TIM3_IRQHandler
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =PWM3_PreemptionPriority;   //��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = PWM3_SubPriority;          //��Ӧ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //�����ж�
	NVIC_Init(&NVIC_InitStructure);
	
	//�趨��ʱ�����ڡ�Ԥ��Ƶ
	TIM_BaseInitStructure.TIM_Period =800;
	TIM_BaseInitStructure.TIM_Prescaler =71; 
	TIM_BaseInitStructure.TIM_ClockDivision = 0;
	TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_BaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_BaseInitStructure);	
	
	//PWMģʽ�����ã��ο�STM32�ĵ�
	TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM2;       //PWM2ģʽ 
	TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable;  //�ź��������Ӧ��������� 
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; //�����ź��������Ӧ���������                  
	TIM_OCInitStructure.TIM_Pulse =150;   //������ 
	TIM_OCInitStructure.TIM_OCPolarity   = TIM_OCPolarity_Low;   //��������ߵ�ƽ��Ч 
	TIM_OCInitStructure.TIM_OCNPolarity  = TIM_OCNPolarity_High;    //��������ߵ�ƽ��Ч      
	TIM_OCInitStructure.TIM_OCIdleState  = TIM_OCIdleState_Reset;  //�������״̬Ϊ1 
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;   //�����������״̬Ϊ0   
	TIM_OC1Init(TIM3,&TIM_OCInitStructure);   //OC1ͨ����ʼ��

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM3, ENABLE);
	//���жϣ�����һ�����жϺ����������ж�
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
#ifndef MOTOR_PWM_USEDMA	
	/* Select the Master Slave Mode */
	TIM_SelectMasterSlaveMode(TIM3, TIM_MasterSlaveMode_Enable);
	/* Master Mode selection */
	TIM_SelectOutputTrigger(TIM3, TIM_TRGOSource_Update);
	Initial_Motor3_SlaveTimer();
#else
	Initial_Motor3_DMA();
	/* ʹ��DMA*/         
  TIM_DMACmd(TIM3, TIM_DMA_Update, ENABLE);
#endif
	TIM_Cmd(TIM3, DISABLE); 
}













