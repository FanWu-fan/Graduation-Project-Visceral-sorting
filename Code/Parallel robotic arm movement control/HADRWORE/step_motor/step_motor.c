#include "step_motor.h"
#include "coder.h"
#include "xy_angle.h"
#include "sys.h" 
#include "usart.h"
#include "stm32f10x.h"
#include "math.h"

extern long double targetangle1,targetangle2,targetangle3;
long  double nowx,nowy,nowz;  //每次运动到的角度
u16 running1,running2,running3;
u32 nowcoder1,nowcoder2,nowcoder3;   //静止阶段时的编码器值


void  motordir_Init(void)// 
{
     
	GPIO_InitTypeDef GPIO_InitStructure;
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOG, ENABLE);  //使能GPIOF
      

      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化PF0 motor1dir
      GPIO_SetBits(GPIOF,GPIO_Pin_0);
	
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	
	GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化PF1 motor2dir
      GPIO_SetBits(GPIOF,GPIO_Pin_1);	
	
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	
	GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化PF2 motor3dir
      GPIO_SetBits(GPIOF,GPIO_Pin_2);
	

      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	
	GPIO_Init(GPIOG, &GPIO_InitStructure);//初始化PG2 motor1enable
      GPIO_ResetBits(GPIOG,GPIO_Pin_2);	
	
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	
	GPIO_Init(GPIOG, &GPIO_InitStructure);//初始化PG3 motor2enable
      GPIO_ResetBits(GPIOG,GPIO_Pin_3);	

      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;	
	GPIO_Init(GPIOG, &GPIO_InitStructure);//初始化PG4 motor3enable
      GPIO_ResetBits(GPIOG,GPIO_Pin_4);
}




void motor1running(int dir1,long double Changeangle1)//电机1运行指定角度  PA8
{ 
	u16 pulse1;
    if(dir1==1) PFout(0)=0;//方向控制
    else PFout(0)=1;
    
    pulse1=Changeangle1*M1DIV/1.8;//细分后所需脉冲
    printf("\r\n PULSE1:%d \r\n  ",pulse1);
if(pulse1>1.5|pulse1==1.5)	
	
{   TIM4->ARR=pulse1-1;//从定时器重装值等于所需脉冲数
    TIM4->CNT=0;
    TIM_Cmd(TIM1, ENABLE);
    TIM_Cmd(TIM4, ENABLE); 
	running1=1;
}

	
}

void motor2running(int dir2,long double Changeangle2)//电机2运行指定角度 PA0
{ 
	u16 pulse2;
    if(dir2==1) PFout(1)=1;//方向控制
    else PFout(1)=0;
    
    pulse2=Changeangle2*M2DIV/1.8;//细分后所需脉冲
if(pulse2>1.5|pulse2==1.5)//ARR值需要大于等于1	
{
	TIM8->ARR=pulse2-1;//从定时器重装值等于所需脉冲数
    TIM8->CNT=0;
    TIM_Cmd(TIM2, ENABLE);
    TIM_Cmd(TIM8, ENABLE); 
	running2=1;
}
	
}

void motor3running(int dir3,long double Changeangle3)//电机3运行指定角度 PA6
{ 
	u16 pulse3;
    if(dir3==1) PFout(2)=1;//方向控制
	
    else PFout(2)=0;
    
    pulse3=Changeangle3*M3DIV/1.8;//细分后所需脉冲

if(pulse3>1.5|pulse3==1.5)	
{   TIM5->ARR=pulse3-1;//从定时器重装值等于所需脉冲数
    TIM5->CNT=0;
    TIM_Cmd(TIM3, ENABLE);
    TIM_Cmd(TIM5, ENABLE); 
	running3=1;}
	
}

void motorto_aimangle(long double aimangle1,long double aimangle2,long double aimangle3)//电机运行到指定度数
{
	
      long double currentcoder1,currentcoder2,currentcoder3;
	long double currentangle1,currentangle2,currentangle3,movagle1,movagle2,movagle3;//现在的角度值
	long double coordinatetransform1,coordinatetransform2,coordinatetransform3;//主动臂与铅锤的夹角的范围为-pi到pi
u8 dir1=1,dir2=1,dir3=1,i=1,finish1=0,finish2=0,finish3=0;//各从动臂是否到达预定位置标志	
u16 debug1=1,debug2=1,debug3=1;		
	do{
	for(;i<2;i++)	
	{currentcoder1=coder1();
	 currentcoder2=coder2();    
	 currentcoder3=coder3();   //取得目前的编码器值
		
	coordinatetransform1=currentcoder1-plumb1;
	if(coordinatetransform1<0)     coordinatetransform1=coordinatetransform1+4096;//此时铅锤右边为0，左边4095
	if(coordinatetransform1>2048)	 coordinatetransform1=coordinatetransform1-4096;//此时铅锤反向右边为2048，左边-2047
		
	coordinatetransform2=currentcoder2-plumb2;
	if(coordinatetransform2<0)     coordinatetransform2=coordinatetransform2+4096;//此时铅锤右边为0，左边4095
	if(coordinatetransform2>2048)	 coordinatetransform2=coordinatetransform2-4096;//此时铅锤反向右边为2048，左边-2047
		
	coordinatetransform3=currentcoder3-plumb3;
	if(coordinatetransform3<0)     coordinatetransform3=coordinatetransform3+4096;//此时铅锤右边为0，左边4095
	if(coordinatetransform3>2048)	 coordinatetransform3=coordinatetransform3-4096;//此时铅锤反向右边为2048，左边-2047
		
	currentangle1=(coordinatetransform1)/k_coder;//计算得到目前的角度值
	currentangle2=(coordinatetransform2)/k_coder;
	currentangle3=(coordinatetransform3)/k_coder;
	}
	printf("CURRENTANGLE:%Lf \r\n  ",currentangle1);
	
	movagle1=aimangle1-currentangle1;  //计算得到电机需要运行的角度值
	movagle2=aimangle2-currentangle2;
	movagle3=aimangle3-currentangle3;
		
	if(movagle1<0) dir1=0,movagle1=-movagle1;		//判定方向
		else dir1=1;
	if(movagle2<0) dir2=0,movagle2=-movagle2;
		else dir2=1;
	if(movagle3<0) dir3=0,movagle3=-movagle3;
		else dir3=1;
	
	printf("\r\ndir1:%d    angle1:%Lf    ",dir1,movagle1);
	printf("dir2:%d    angle2:%Lf    ",dir2,movagle2);
	printf("dir3:%d    angle3:%Lf\r\n",dir3,movagle3);

 
     if(finish1==0)  motor1running(dir1,movagle1);
     if(finish2==0)  motor2running(dir2,movagle2);
     if(finish3==0)  motor3running(dir3,movagle3);

	while( running1==1|| running2==1 || running3==1) //只有电机全部运行完以后才能退出
	{
	 debug1=coder1();
	 debug2=coder2();    
	 debug3=coder3();   //取得目前的编码器值
	 if((debug1<2958&&debug1>1478)|(debug2<2135&&debug2>655)|debug3>2745||debug3<180)	
	 {
	        TIM_Cmd(TIM1, DISABLE);
              TIM_Cmd(TIM2, DISABLE);	
              TIM_Cmd(TIM3, DISABLE);
              TIM_Cmd(TIM4, DISABLE);
              TIM_Cmd(TIM8, DISABLE);
              TIM_Cmd(TIM5, DISABLE); 
	 }
//	{		printf("coder1:%d \r  ",coder1());
//			printf("coder2:%d \r  ",coder2());
//		      printf("coder3:%d \r\n  ",coder3());
//	}	 
	}	
	currentcoder1=coder1();
	currentcoder2=coder2();    
	currentcoder3=coder3();   //取得目前的编码器值
		
	coordinatetransform1=currentcoder1-plumb1;
	if(coordinatetransform1<0)     coordinatetransform1=coordinatetransform1+4096;//此时铅锤右边为0，左边4095
	if(coordinatetransform1>2048)	 coordinatetransform1=coordinatetransform1-4096;//此时铅锤反向右边为2048，左边-2047
		
	coordinatetransform2=currentcoder2-plumb2;
	if(coordinatetransform2<0)     coordinatetransform2=coordinatetransform2+4096;//此时铅锤右边为0，左边4095
	if(coordinatetransform2>2048)	 coordinatetransform2=coordinatetransform2-4096;//此时铅锤反向右边为2048，左边-2047
		
	coordinatetransform3=currentcoder3-plumb3;
	if(coordinatetransform3<0)     coordinatetransform3=coordinatetransform3+4096;//此时铅锤右边为0，左边4095
	if(coordinatetransform3>2048)	 coordinatetransform3=coordinatetransform3-4096;//此时铅锤反向右边为2048，左边-2047
	
	currentangle1=(coordinatetransform1)/k_coder;//计算得到目前的角度值
	currentangle2=(coordinatetransform2)/k_coder;
	currentangle3=(coordinatetransform3)/k_coder;

       printf("%Lf     %Lf   %Lf      ",aimangle1-currentangle1,aimangle2-currentangle2,aimangle3-currentangle3);  

       if(fabs(aimangle1-currentangle1)<=0.5)  finish1=1;
       if(fabs(aimangle2-currentangle2)<=0.5)  finish2=1;
	 if(fabs(aimangle3-currentangle3)<=0.5)  finish3=1;



	}
	
	while(( finish1==0 )|| (finish2==0) || (finish3==0));   //只要角度差值超过0.1则继续调整

}



void movetocoordinate(long double aimx,long double aimy,long double aimz,int mode)        //电机运行到指定 的 XYZ坐标点
{
long double  d_stance,n_stance,x_2,y_2,z_2,i,n;
d_stance=sqrtf((aimx-nowx)*(aimx-nowx)+(aimy-nowy)*(aimy-nowy)+(aimz-nowz)*(aimz-nowz));  //计算运动距离
	
	//printf("d_stance:%lf\n",d_stance);
//	printf("nowx:%lf,nowy:%lf,nowz:%lf\n",nowx,nowy,nowz);

if(mode==0)	
{if(d_stance>=200) n_stance=4.5;
	else if(d_stance>=100&&d_stance<200) n_stance=3;
	else n_stance=1.5;          //计算得出运行次数
	 n =(int)d_stance/n_stance;
	
for(i=0;i<=n;i++)
	{
	
	x_2=(aimx-nowx)*(i/n)+nowx;
	y_2=(aimy-nowy)*(i/n)+nowy;
	z_2=(aimz-nowz)*(i/n)+nowz;
		printf("nowx:%Lf,nowy:%Lf,nowz:%Lf,i:%Lf,n:%Lf\r\n",nowx,nowy,nowz,i,n);
		
	printf("x_2:%Lf,y_2:%Lf,z_2:%Lf\r\n",x_2,y_2,z_2);		
		
	xy2angle(x_2,y_2,z_2);
    if(targetangle1<200&&targetangle1>-200&&targetangle2<200&&targetangle2>-200&&targetangle3<200&&targetangle3>-200)
    motorto_aimangle(targetangle1,targetangle2,targetangle3);
	//printf("targetangle1:%Lf,targetangle2:%Lf,targetangle3:%Lf\r\n\r\n",targetangle1,targetangle2,targetangle3);	
	}
}
if(mode==1)
{
  	xy2angle(aimx,aimy,aimz);
     if(targetangle1<200&&targetangle1>-200&&targetangle2<200&&targetangle2>-200&&targetangle3<200&&targetangle3>-200)
     motorto_aimangle(targetangle1,targetangle2,targetangle3);
	
}
	nowx=aimx;
	nowy=aimy;
	nowz=aimz;    //将当前的坐标值给新值
}

void TIM4_IRQHandler(void)//motor1
{

     TIM4->SR = (u16)~TIM_FLAG_Update;  //清除中断
     TIM_Cmd(TIM1, DISABLE);   
     TIM_Cmd(TIM4, DISABLE);	
	running1=0;
}

void TIM8_UP_IRQHandler(void)//motor2
{

     TIM8->SR = (u16)~TIM_FLAG_Update;  //清除中断
     TIM_Cmd(TIM2, DISABLE);   
     TIM_Cmd(TIM8, DISABLE);
     running2=0;
}

void TIM5_IRQHandler(void)//motor3
{

     TIM5->SR = (u16)~TIM_FLAG_Update;  //清除中断
     TIM_Cmd(TIM3, DISABLE);   
     TIM_Cmd(TIM5, DISABLE);
     running3=0;
	
}

//void TIM1_UP_IRQHandler(void)
//{ 
//	//清除中断
//	TIM1->SR = (u16)~TIM_FLAG_Update; 
//	PBout(5)=!PBout(5);


//}


