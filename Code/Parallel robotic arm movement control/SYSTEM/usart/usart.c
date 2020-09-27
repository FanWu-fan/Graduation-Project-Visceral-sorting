#include "sys.h"
#include "usart.h"	  
////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif

 

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

/*ʹ��microLib�ķ���*/
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
 


u8 USART1_RX_BUF[200];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART1_RX_STA=0;       //����״̬���	  
  
void uart1_init(u32 bound){
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//ʹ��USART1ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��GPIOAʱ��
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART1_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10 

  //Usart1	NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1

}
u32 q=0;
void USART1_IRQHandler(void)                	//����1�жϷ������
	{
	u8 Res;

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
		Res =USART_ReceiveData(USART1);	//��ȡ���յ�������
		q=Res;

			
				{	
				if(Res==0x23)USART1_RX_STA|=0x8000;
				else
					{
					USART1_RX_BUF[USART1_RX_STA&0X3FFF]=Res ;
					USART1_RX_STA++;
					if(USART1_RX_STA>(200-1))USART1_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
					}		 
				}
			 		 
     } 

} 




//����2�жϷ������	
u8 USART2_RX_BUFx[USART2_REC_LEN],USART2_RX_BUFy[USART2_REC_LEN],USART2_RX_BUFz[USART2_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART2_RX_STAx=0,USART2_RX_STAy=0,USART2_RX_STAz=0;       //����״̬���	  
  
void uart2_init(u32 bound){
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//ʹ��USART2ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��GPIOAʱ��
	
	//USART2_TX   GPIOA.2
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.2
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.2
   
  //USART2_RX	  GPIOA.3��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.3  

  //Usart2 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART2, &USART_InitStructure); //��ʼ������2
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ���2 

}

u32 s=3,l=0,f=0,m;
void USART2_IRQHandler(void)                	//����2�жϷ������
	{
	u8 Res;

	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
	    
		Res =USART_ReceiveData(USART2);	//��ȡ���յ�������
		if(Res==0x21) 	f++;	
		if(f>0)	
		{if(Res ==0x0d&&f==1) f++;
		if(Res ==0x0a&&f==2) f++;}
		
		  

	       
		
		else{
		if((USART2_RX_STAx&0x8000)==0)//����δ���  ��ȡx������
			{
				
			if(USART2_RX_STAx&0x4000)//���յ���0x0d
				{
				if(Res!=0x0a)USART2_RX_STAx=0;//���մ���,���¿�ʼ
				else USART2_RX_STAx|=0x8000;	//���������
    				return;	
				}
			else //��û�յ�0X0D
				{	
				if(Res==0x0d)USART2_RX_STAx|=0x4000;
				else
					{
					USART2_RX_BUFx[USART2_RX_STAx&0X3FFF]=Res ;
					USART2_RX_STAx++;
					if(USART2_RX_STAx>(USART2_REC_LEN-1))USART2_RX_STAx=0;//�������ݴ���,���¿�ʼ����((USART2_RX_STAy&0x8000)==0)	  
					}		 
				}
			}  

		if(((USART2_RX_STAx&0x8000)==0x8000)&&((USART2_RX_STAy&0x8000)==0))//����δ���  ��ȡy������
			{
			                  s++;
                          				
			if(USART2_RX_STAy&0x4000)//���յ���0x0d
				{
				if(Res!=0x0a)USART2_RX_STAy=0;//���մ���,���¿�ʼ
				else USART2_RX_STAy|=0x8000;	//���������
                        return;					
				}
			else //��û�յ�0X0D
				{	
				if(Res==0x0d)USART2_RX_STAy|=0x4000;
				else
					{
					USART2_RX_BUFy[USART2_RX_STAy&0X3FFF]=Res ;
					USART2_RX_STAy++;
					if(USART2_RX_STAy>(USART2_REC_LEN-1))USART2_RX_STAy=0;//�������ݴ���,���¿�ʼ����((USART2_RX_STAy&0x8000)==0)	  
					}		 
				}
			} 

             if((USART2_RX_STAy&0x8000)==0x8000)//����δ���  ��ȡz������
			{
			if(USART2_RX_STAz&0x4000)//���յ���0x0d
				{
				if(Res!=0x0a)USART2_RX_STAz=0;//���մ���,���¿�ʼ
				else USART2_RX_STAz|=0x8000;	//��������� 
				}
			else //��û�յ�0X0D
				{	
				if(Res==0x0d)USART2_RX_STAz|=0x4000;
				else
					{
					USART2_RX_BUFz[USART2_RX_STAz&0X3FFF]=Res ;
					USART2_RX_STAz++;
					if(USART2_RX_STAz>(USART2_REC_LEN-1))USART2_RX_STAz=0;//�������ݴ���,���¿�ʼ����	  
					}		 
				}
			}  

		}
			
     } 
											 

} 
	


u8 USART3_RX_BUF[200];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART3_RX_STA=0;       //����״̬���	  
  
void uart3_init(u32 bound){
  //GPIO�˿�����
      GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//ʹ��USART3ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//ʹ��GPIOBʱ��
  
	//USART3_TX   GPIOB.10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB.10
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB.10
   
  //USART3_RX	  GPIOB.11��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PB11
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB.11  

  //Usart3 NVIC ����
      NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART3, &USART_InitStructure); //��ʼ������3
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ���3 

}
u32 q2=0;
void USART3_IRQHandler(void)                	//����3�жϷ������
	{
	u8 Res;


	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
		Res =USART_ReceiveData(USART3);	//��ȡ���յ�������
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
//					if(USART3_RX_STA>(200-1))USART3_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
//					}		 
				}
			 		 
     } 
											 

} 
	
	long double      aimx,aimy,aimz;
void readusart(void)
{
	u8               len1,len2,len3;

  len1=USART2_RX_STAx&0x3fff;//�õ��˴ν��յ������ݳ���
			   printf("\r\n�����͵���ϢΪ:\r\n\r\n");
			
			if(USART2_RX_BUFx[0]==0x2d)   ////////////////��ȡX������
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
			printf("\r\n\r\n");//���뻻��
			USART2_RX_STAx=0;
			
			   len2=USART2_RX_STAy&0x3fff;//�õ��˴ν��յ������ݳ���
			   printf("\r\n�����͵���ϢΪ:\r\n\r\n");
			
			if(USART2_RX_BUFy[0]==0x2d)   ////////////////��ȡY������
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
			printf("\r\n\r\n");//���뻻��
			USART2_RX_STAy=0;

			   len3=USART2_RX_STAz&0x3fff;//�õ��˴ν��յ������ݳ���
			   printf("\r\n�����͵���ϢΪ:\r\n\r\n");
			
			if(USART2_RX_BUFz[0]==0x2d)    ////////////////��ȡZ������
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
			printf("\r\n\r\n");//���뻻��
			USART2_RX_STAz=0;
		aimz=aimz-27.6;//��ƽ���²��붯ƽ���ϲ���ľ���
}
	

