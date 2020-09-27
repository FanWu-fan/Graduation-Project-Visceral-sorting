#include "stm32f10x.h"
#include "xy_angle.h"
#include "coder.h"
#include "pwm.h"
#include "step_motor.h"
#include "usart.h"
#include "faststop.h"
#include "manipulator.h"
/*�������ã��������x y z����Ϊ(0,0,-300),�����Ƕȷֱ�Ϊ74.941444�ȡ��˶���ΧΪ469.13-173.13*/
extern u32 nowcoder1,nowcoder2,nowcoder3,s;
extern long double      nowx,nowy,nowz;   //��ֹ�׶�ʱ�ı�����ֵ
extern long double      aimx,aimy,aimz;               
extern u16              running1,running2,running3;
extern u8 len1,len2,len3;
extern u32 f,q;
extern u8 USART1_RX_BUF[200]; 
u8 t=5,y=0;
u32 w1,w2,w3;
 int main(void)
 {	
	 
 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	 delay_init();
	 uart1_init(115200);
	 uart2_init(9600);
	 uart3_init(9600);	 
	 coder_init();   //��������ʼ��
      motordir_Init();//�������IO��ʼ��
      FASTSTOP_Init(); //��ͣ���ܳ�ʼ����KEY2
	KEY_Init();
      Initial_PWM_Motor1();//����ʱ����ʼ��
      Initial_PWM_Motor2();
      Initial_PWM_Motor3();
	 
	 nowx=0.0;
	 nowy=0.0;
	 nowz=-300;
	 
nowcoder1=coder1();
nowcoder2=coder2();
nowcoder3=coder3();
	 

//xy2angle(50,80,-300);	 
//motortoangle(0,50,-200);
//motor1running(0,30);
//motor1running(0,90);
//motor3running(1,0.5);
//motor3running(1,30);//���3����ָ���Ƕ�
movetocoordinate(0,0,-227.6,1);
//movetocoordinate(50,50,-257.6,1);
//movetocoordinate(0,0,-177.6,1);
//motorto_aimangle(30,30,30);

			while(1)
			{
	       if((USART2_RX_STAx&0x8000)&&(USART2_RX_STAy&0x8000)&&(USART2_RX_STAz&0x8000))//��ȡ��ʾ�����������
		   {   
		readusart();
          printf("aimz:%Lf \r  ",aimz);			   
		movetocoordinate(aimx,aimy,aimz,1);		   
		   }	
if(USART1_RX_STA&0x8000)//��ȡ��λ�����������		   
{aimx=(USART1_RX_BUF[0]-48)*10+USART1_RX_BUF[1]-48;
 aimy=(USART1_RX_BUF[2]-48)*10+USART1_RX_BUF[3]-48;
 aimz=-327.6;
 USART1_RX_STA=0;
movetocoordinate(aimx,aimy,aimz,1);
          printf("aimx:%Lf \r  ",aimx);
	    printf("aimy:%Lf \r  ",aimy);
	    printf("aimz:%Lf \r  ",aimz);
	 
}

			delay_ms(5000); 
              GPIO_ResetBits(GPIOG,GPIO_Pin_5);
                   mani1=!mani1;
			printf("coder1:%d \r  ",coder1());
			printf("coder2:%d \r  ",coder2());
			printf("coder3:%d \r\n  ",coder3());
                  w1=coder1();
                  w2=coder2();
                  w3=coder3();
		if(f==3)//��ȡ�������ź�
		{//USART_SendData(USART1,0X23);
//             while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)!= SET);
			
			
             USART_SendData(USART3,0X23);//��֪��Ƭ��2�˶���ʼ
             while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)!= SET);
			f=0;
			printf("OK \r\n");			
		}			
  
	      if(USART3_RX_STA==1)
		   {               
	    movetocoordinate(0,0,-343.6,1);          //ƽ̨�½�
             USART_SendData(USART3,0X24);
             while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)!= SET);			   
	    USART3_RX_STA=0;
		   }
	      if(USART3_RX_STA==2)
		   {               
	    movetocoordinate(0,0,-227.6,1);           //ƽ̨����
             USART_SendData(USART3,0X25);
             while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)!= SET);			   
	    USART3_RX_STA=0;
		   }
	      if(USART3_RX_STA==3)                      //����ƽ̨
		   {               
		 movetocoordinate(-35,-25,-227.6,1);
             USART_SendData(USART3,0X26);
             while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)!= SET); 
	    USART3_RX_STA=0;
		   }		   
	      if(USART3_RX_STA==4)
		   {               
		 movetocoordinate(35,25,-227.6,1);                  //����ƽ̨
             USART_SendData(USART3,0X27);
             while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)!= SET); 
	    USART3_RX_STA=0;
		   }	
	      if(USART3_RX_STA==5)
		   {               
		 movetocoordinate(0,0,-227.6,1);									//�ƶ���ԭλ��
             USART_SendData(USART3,0X28);
             while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)!= SET); 
	    USART3_RX_STA=0;
		   }			   
			}


	 
	 
	 
 }
