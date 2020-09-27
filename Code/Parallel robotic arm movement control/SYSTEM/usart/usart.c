#include "sys.h"
#include "usart.h"	  
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif

 

//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

/*使用microLib的方法*/
 /* 
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  { 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}
*/
 


u8 USART1_RX_BUF[200];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART1_RX_STA=0;       //接收状态标记	  
  
void uart1_init(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//使能USART1时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能GPIOA时钟
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10 

  //Usart1	NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART1, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART1, ENABLE);                    //使能串口1

}
u32 q=0;
void USART1_IRQHandler(void)                	//串口1中断服务程序
	{
	u8 Res;

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
		Res =USART_ReceiveData(USART1);	//读取接收到的数据
		q=Res;

			
				{	
				if(Res==0x23)USART1_RX_STA|=0x8000;
				else
					{
					USART1_RX_BUF[USART1_RX_STA&0X3FFF]=Res ;
					USART1_RX_STA++;
					if(USART1_RX_STA>(200-1))USART1_RX_STA=0;//接收数据错误,重新开始接收	  
					}		 
				}
			 		 
     } 

} 




//串口2中断服务程序	
u8 USART2_RX_BUFx[USART2_REC_LEN],USART2_RX_BUFy[USART2_REC_LEN],USART2_RX_BUFz[USART2_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART2_RX_STAx=0,USART2_RX_STAy=0,USART2_RX_STAz=0;       //接收状态标记	  
  
void uart2_init(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//使能USART2时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能GPIOA时钟
	
	//USART2_TX   GPIOA.2
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.2
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.2
   
  //USART2_RX	  GPIOA.3初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.3  

  //Usart2 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART2, &USART_InitStructure); //初始化串口2
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART2, ENABLE);                    //使能串口2 

}

u32 s=3,l=0,f=0,m;
void USART2_IRQHandler(void)                	//串口2中断服务程序
	{
	u8 Res;

	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
	    
		Res =USART_ReceiveData(USART2);	//读取接收到的数据
		if(Res==0x21) 	f++;	
		if(f>0)	
		{if(Res ==0x0d&&f==1) f++;
		if(Res ==0x0a&&f==2) f++;}
		
		  

	       
		
		else{
		if((USART2_RX_STAx&0x8000)==0)//接收未完成  读取x轴坐标
			{
				
			if(USART2_RX_STAx&0x4000)//接收到了0x0d
				{
				if(Res!=0x0a)USART2_RX_STAx=0;//接收错误,重新开始
				else USART2_RX_STAx|=0x8000;	//接收完成了
    				return;	
				}
			else //还没收到0X0D
				{	
				if(Res==0x0d)USART2_RX_STAx|=0x4000;
				else
					{
					USART2_RX_BUFx[USART2_RX_STAx&0X3FFF]=Res ;
					USART2_RX_STAx++;
					if(USART2_RX_STAx>(USART2_REC_LEN-1))USART2_RX_STAx=0;//接收数据错误,重新开始接收((USART2_RX_STAy&0x8000)==0)	  
					}		 
				}
			}  

		if(((USART2_RX_STAx&0x8000)==0x8000)&&((USART2_RX_STAy&0x8000)==0))//接收未完成  读取y轴坐标
			{
			                  s++;
                          				
			if(USART2_RX_STAy&0x4000)//接收到了0x0d
				{
				if(Res!=0x0a)USART2_RX_STAy=0;//接收错误,重新开始
				else USART2_RX_STAy|=0x8000;	//接收完成了
                        return;					
				}
			else //还没收到0X0D
				{	
				if(Res==0x0d)USART2_RX_STAy|=0x4000;
				else
					{
					USART2_RX_BUFy[USART2_RX_STAy&0X3FFF]=Res ;
					USART2_RX_STAy++;
					if(USART2_RX_STAy>(USART2_REC_LEN-1))USART2_RX_STAy=0;//接收数据错误,重新开始接收((USART2_RX_STAy&0x8000)==0)	  
					}		 
				}
			} 

             if((USART2_RX_STAy&0x8000)==0x8000)//接收未完成  读取z轴坐标
			{
			if(USART2_RX_STAz&0x4000)//接收到了0x0d
				{
				if(Res!=0x0a)USART2_RX_STAz=0;//接收错误,重新开始
				else USART2_RX_STAz|=0x8000;	//接收完成了 
				}
			else //还没收到0X0D
				{	
				if(Res==0x0d)USART2_RX_STAz|=0x4000;
				else
					{
					USART2_RX_BUFz[USART2_RX_STAz&0X3FFF]=Res ;
					USART2_RX_STAz++;
					if(USART2_RX_STAz>(USART2_REC_LEN-1))USART2_RX_STAz=0;//接收数据错误,重新开始接收	  
					}		 
				}
			}  

		}
			
     } 
											 

} 
	


u8 USART3_RX_BUF[200];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART3_RX_STA=0;       //接收状态标记	  
  
void uart3_init(u32 bound){
  //GPIO端口设置
      GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//使能USART3时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//使能GPIOB时钟
  
	//USART3_TX   GPIOB.10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB.10
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB.10
   
  //USART3_RX	  GPIOB.11初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PB11
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB.11  

  //Usart3 NVIC 配置
      NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART3, &USART_InitStructure); //初始化串口3
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART3, ENABLE);                    //使能串口3 

}
u32 q2=0;
void USART3_IRQHandler(void)                	//串口3中断服务程序
	{
	u8 Res;


	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
		Res =USART_ReceiveData(USART3);	//读取接收到的数据
		q2=Res;

			
				{	
				if(Res==0x23)USART3_RX_STA=1;
				if(Res==0x24)USART3_RX_STA=2;
				if(Res==0x25)USART3_RX_STA=3;	
				if(Res==0x26)USART3_RX_STA=4;	
				if(Res==0x27)USART3_RX_STA=5;						
//				else
//					{
//					USART3_RX_BUF[USART3_RX_STA&0X3FFF]=Res ;
//					USART3_RX_STA++;
//					if(USART3_RX_STA>(200-1))USART3_RX_STA=0;//接收数据错误,重新开始接收	  
//					}		 
				}
			 		 
     } 
											 

} 
	
	long double      aimx,aimy,aimz;
void readusart(void)
{
	u8               len1,len2,len3;

  len1=USART2_RX_STAx&0x3fff;//得到此次接收到的数据长度
			   printf("\r\n您发送的消息为:\r\n\r\n");
			
			if(USART2_RX_BUFx[0]==0x2d)   ////////////////获取X轴坐标
		{    switch(len1)
			{case 2: aimx=((USART2_RX_BUFx[1]-48))*(-1); break;
			 case 3: aimx=((USART2_RX_BUFx[1]-48)*10+(USART2_RX_BUFx[2]-48))*(-1); break;
			 case 4: aimx=((USART2_RX_BUFx[1]-48)*100+(USART2_RX_BUFx[2]-48)*10+(USART2_RX_BUFx[3]-48))*(-1);
				
		     }	
		}	
		
			else 
		{    switch(len1)
			{case 1: aimx=((USART2_RX_BUFx[0]-48));  break;
			 case 2: aimx=((USART2_RX_BUFx[0]-48)*10+(USART2_RX_BUFx[1]-48));  break;
			 case 3: aimx=((USART2_RX_BUFx[0]-48)*100+(USART2_RX_BUFx[1]-48)*10+(USART2_RX_BUFx[2]-48)); 
				
		     }	
		}	
		      printf("aimx:%Lf \r  ",aimx);
			printf("\r\n\r\n");//插入换行
			USART2_RX_STAx=0;
			
			   len2=USART2_RX_STAy&0x3fff;//得到此次接收到的数据长度
			   printf("\r\n您发送的消息为:\r\n\r\n");
			
			if(USART2_RX_BUFy[0]==0x2d)   ////////////////获取Y轴坐标
		{    switch(len2)
			{case 2: aimy=((USART2_RX_BUFy[1]-48)*(-1)); break;
			 case 3: aimy=((USART2_RX_BUFy[1]-48)*10+(USART2_RX_BUFy[2]-48))*(-1); break;
			 case 4: aimy=((USART2_RX_BUFy[1]-48)*100+(USART2_RX_BUFy[2]-48)*10+(USART2_RX_BUFy[3]-48))*(-1);
				
		     }	
		}	
			else 
		{    switch(len2)
			{case 1: aimy=((USART2_RX_BUFy[0]-48)); break;
			 case 2: aimy=((USART2_RX_BUFy[0]-48)*10+(USART2_RX_BUFy[1]-48)); break;
			 case 3: aimy=((USART2_RX_BUFy[0]-48)*100+(USART2_RX_BUFy[1]-48)*10+(USART2_RX_BUFy[2]-48));
				
		     }	
		}	
		      printf("aimy:%Lf \r  ",aimy);
			printf("\r\n\r\n");//插入换行
			USART2_RX_STAy=0;

			   len3=USART2_RX_STAz&0x3fff;//得到此次接收到的数据长度
			   printf("\r\n您发送的消息为:\r\n\r\n");
			
			if(USART2_RX_BUFz[0]==0x2d)    ////////////////获取Z轴坐标
		{    switch(len3)
			{case 2: aimz=((USART2_RX_BUFz[1]-48)); break;
			 case 3: aimz=((USART2_RX_BUFz[1]-48)*10+(USART2_RX_BUFz[2]-48)); break;
			 case 4: aimz=((USART2_RX_BUFz[1]-48)*100+(USART2_RX_BUFz[2]-48)*10+(USART2_RX_BUFz[3]-48));
				
		      }	
		}	
			else 
		{    switch(len3)
			{case 1: aimz=((USART2_RX_BUFz[0]-48))*(-1); break;
			 case 2: aimz=((USART2_RX_BUFz[0]-48)*10+(USART2_RX_BUFz[1]-48))*(-1); break;
			 case 3: aimz=((USART2_RX_BUFz[0]-48)*100+(USART2_RX_BUFz[1]-48)*10+(USART2_RX_BUFz[2]-48))*(-1);
				
		     }	
		}	
		      printf("aimz:%Lf \r  ",aimz);
			printf("\r\n\r\n");//插入换行
			USART2_RX_STAz=0;
		aimz=aimz-27.6;//静平面下部与动平面上部间的距离
}
	

