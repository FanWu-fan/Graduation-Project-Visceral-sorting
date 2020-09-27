#include "pwm.h"
#include  "string.h"

/*电机1使用到的Slave Timer   TIM4*/
void Initial_Motor1_SlaveTimer(void)
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	memset(&TIM_OCInitStructure,0,sizeof(TIM_OCInitStructure));
	memset(&TIM_TimeBaseStructure,0,sizeof(TIM_TimeBaseStructure));
	
	/*外设使能*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	TIM_DeInit(TIM4);
	//中断NVIC设置：允许中断，设置优先级
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;                 //更新事件
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =PWM1_PreemptionPriority;        //抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =PWM1_SubPriority;              //响应优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //允许中断
	NVIC_Init(&NVIC_InitStructure);

	//设定定时器周期、预分频，
	TIM_TimeBaseStructure.TIM_Period = 65535;                        //自动装载计数器周期值
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;                  //时钟分隔
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);               //初始化
	
	/* Output Compare Inactive Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode                        = TIM_OCMode_Inactive;//假如计数器值等于CCR，强制为低电平
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
/*电机2使用到的Slave Timer  TIM8*/
void Initial_Motor2_SlaveTimer(void)
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	memset(&TIM_OCInitStructure,0,sizeof(TIM_OCInitStructure));
	memset(&TIM_TimeBaseStructure,0,sizeof(TIM_TimeBaseStructure));
	
	/*外设使能*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	TIM_DeInit(TIM8);
	//中断NVIC设置：允许中断，设置优先级
	NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_IRQn;                 //更新事件
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =PWM2_PreemptionPriority;        //抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =PWM2_SubPriority;              //响应优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //允许中断
	NVIC_Init(&NVIC_InitStructure);

	//设定定时器周期、预分频
	TIM_TimeBaseStructure.TIM_Period = 32;                        //自动装载计数器周期值
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;                  //时钟分隔
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //计数模式
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);               //初始化
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

/*电机3使用到的Slave Timer TIM5*/
void Initial_Motor3_SlaveTimer(void)
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	memset(&TIM_OCInitStructure,0,sizeof(TIM_OCInitStructure));
	memset(&TIM_TimeBaseStructure,0,sizeof(TIM_TimeBaseStructure));
	
	/*外设使能*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	TIM_DeInit(TIM5);
	//中断NVIC设置：允许中断，设置优先级
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;                 //更新事件
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =PWM3_PreemptionPriority;        //抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =PWM3_SubPriority;              //响应优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //允许中断
	NVIC_Init(&NVIC_InitStructure);

	//设定定时器周期、预分频，
	TIM_TimeBaseStructure.TIM_Period = 65535;                        //自动装载计数器周期值
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;                  //时钟分隔
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //计数模式
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);               //初始化
	
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



/*电机1的PWM输出初始化，使用的是定时器1*/
void Initial_PWM_Motor1(void)
{
	TIM_TimeBaseInitTypeDef TIM_BaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
      GPIO_InitTypeDef  GPIO_InitStructure;
	memset(&TIM_OCInitStructure,0,sizeof(TIM_OCInitStructure));//为新申请的内存做初始化工作
	memset(&TIM_BaseInitStructure,0,sizeof(TIM_BaseInitStructure));
	
	/*外设使能*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
	TIM_DeInit(TIM1);

	/*使能电机使用到的外设时钟PA8*/
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA| RCC_APB2Periph_AFIO, ENABLE);
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_InitStructure.GPIO_Pin =GPIO_Pin_8;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
      GPIO_Init(GPIOA, &GPIO_InitStructure);
      GPIO_ResetBits(GPIOA,GPIO_Pin_8);
	
	//中断NVIC设置：允许中断，设置优先级
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;     
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;   
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             
	NVIC_Init(&NVIC_InitStructure);
	
      //初始化定时器参数
	TIM_BaseInitStructure.TIM_Period =800;	//设置自动重装载值，频率设定为1000
	TIM_BaseInitStructure.TIM_Prescaler =71; 	//设定定时器预分频，
	TIM_BaseInitStructure.TIM_ClockDivision = 0;//时钟分割
	TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_BaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_BaseInitStructure);
      
	//初始化输出比较通道
	TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM2;       //PWM2模式
	TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable;  //信号输出到对应的输出引脚
	TIM_OCInitStructure.TIM_Pulse = 150;   //脉冲宽度  CCR
	TIM_OC1Init(TIM1,&TIM_OCInitStructure);   //OC1通道初始化

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);//使能预装载寄存器
	TIM_ARRPreloadConfig(TIM1, ENABLE);
	
	//清中断，以免一启用中断后立即产生中断
	TIM_ClearFlag(TIM1, TIM_FLAG_Update);
#ifndef MOTOR_PWM_USEDMA
	/* Select the Master Slave Mode */
	TIM_SelectMasterSlaveMode(TIM1, TIM_MasterSlaveMode_Enable);
	/* Master Mode selection */
	TIM_SelectOutputTrigger(TIM1, TIM_TRGOSource_Update);//将主定时器的更新事件作为触发输出
	Initial_Motor1_SlaveTimer();//初始化从定时器
#else
	Initial_Motor1_DMA();
	/* 使能DMA*/         
  TIM_DMACmd(TIM1, TIM_DMA_Update, DISABLE);
#endif
      //TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM1,DISABLE);
	TIM_CtrlPWMOutputs(TIM1,ENABLE); //使能PWM输出
	//TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
	
}

/*电机2的PWM输出初始化，使用的是定时器2*/
void Initial_PWM_Motor2(void)
{
      TIM_TimeBaseInitTypeDef TIM_BaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
      GPIO_InitTypeDef  GPIO_InitStructure;	

	memset(&TIM_OCInitStructure,0,sizeof(TIM_OCInitStructure));
	memset(&TIM_BaseInitStructure,0,sizeof(TIM_BaseInitStructure));
	
	/*外设使能*/
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_DeInit(TIM2);
	
	/*使能电机使用到的外设时钟PA0*/
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
      GPIO_Init(GPIOA, &GPIO_InitStructure);
      GPIO_ResetBits(GPIOA,GPIO_Pin_0);	
	
  //中断NVIC设置：允许中断，设置优先级
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;    //更新事件 	TIM2_IRQHandler
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =PWM2_PreemptionPriority;   //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = PWM2_SubPriority;          //响应优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //允许中断
	NVIC_Init(&NVIC_InitStructure);
	
	//设定定时器周期、预分频
	TIM_BaseInitStructure.TIM_Period =800;
	TIM_BaseInitStructure.TIM_Prescaler =71; 
	TIM_BaseInitStructure.TIM_ClockDivision = 0;
	TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_BaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_BaseInitStructure);	
	
	//PWM模式的设置，参考STM32文档
	TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM2;       //PWM2模式 
	TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable;  //信号输出到对应的输出引脚                  
	TIM_OCInitStructure.TIM_Pulse =150;   //脉冲宽度  
	TIM_OC1Init(TIM2,&TIM_OCInitStructure);   //OC1通道初始化
	
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM2, ENABLE);
  //清中断，以免一启用中断后立即产生中断
//	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
#ifndef MOTOR_PWM_USEDMA	
	/* Select the Master Slave Mode */
	TIM_SelectMasterSlaveMode(TIM2, TIM_MasterSlaveMode_Enable);
	/* Master Mode selection */
	TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);
	Initial_Motor2_SlaveTimer();
#else
	Initial_Motor2_DMA();
	/* 使能DMA*/         
  TIM_DMACmd(TIM2, TIM_DMA_Update, ENABLE);
#endif
	TIM_Cmd(TIM2, DISABLE); 
}

/*电机3的PWM输出初始化，使用的是定时器3*/
void Initial_PWM_Motor3(void)
{
	TIM_TimeBaseInitTypeDef TIM_BaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
      GPIO_InitTypeDef  GPIO_InitStructure;	

	/*使能电机使用到的外设时钟PA6*/
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_InitStructure.GPIO_Pin =GPIO_Pin_6;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
      GPIO_Init(GPIOA, &GPIO_InitStructure);
      GPIO_ResetBits(GPIOA,GPIO_Pin_6);	
	
	memset(&TIM_OCInitStructure,0,sizeof(TIM_OCInitStructure));
	memset(&TIM_BaseInitStructure,0,sizeof(TIM_BaseInitStructure));
	
	/*外设使能*/
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	TIM_DeInit(TIM3);
  
	//中断NVIC设置：允许中断，设置优先级
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;    //更新事件 	TIM3_IRQHandler
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =PWM3_PreemptionPriority;   //抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = PWM3_SubPriority;          //响应优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //允许中断
	NVIC_Init(&NVIC_InitStructure);
	
	//设定定时器周期、预分频
	TIM_BaseInitStructure.TIM_Period =800;
	TIM_BaseInitStructure.TIM_Prescaler =71; 
	TIM_BaseInitStructure.TIM_ClockDivision = 0;
	TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_BaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_BaseInitStructure);	
	
	//PWM模式的设置，参考STM32文档
	TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM2;       //PWM2模式 
	TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable;  //信号输出到对应的输出引脚 
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; //互补信号输出到对应的输出引脚                  
	TIM_OCInitStructure.TIM_Pulse =150;   //脉冲宽度 
	TIM_OCInitStructure.TIM_OCPolarity   = TIM_OCPolarity_Low;   //互补输出高电平有效 
	TIM_OCInitStructure.TIM_OCNPolarity  = TIM_OCNPolarity_High;    //互补输出高电平有效      
	TIM_OCInitStructure.TIM_OCIdleState  = TIM_OCIdleState_Reset;  //输出空闲状态为1 
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;   //互补输出空闲状态为0   
	TIM_OC1Init(TIM3,&TIM_OCInitStructure);   //OC1通道初始化

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM3, ENABLE);
	//清中断，以免一启用中断后立即产生中断
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
#ifndef MOTOR_PWM_USEDMA	
	/* Select the Master Slave Mode */
	TIM_SelectMasterSlaveMode(TIM3, TIM_MasterSlaveMode_Enable);
	/* Master Mode selection */
	TIM_SelectOutputTrigger(TIM3, TIM_TRGOSource_Update);
	Initial_Motor3_SlaveTimer();
#else
	Initial_Motor3_DMA();
	/* 使能DMA*/         
  TIM_DMACmd(TIM3, TIM_DMA_Update, ENABLE);
#endif
	TIM_Cmd(TIM3, DISABLE); 
}













