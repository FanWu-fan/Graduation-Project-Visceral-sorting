#include "xy_angle.h"
#include "sys.h"
#include "usart.h"

#define La 216.5            //从动杆216.4        220
#define Lb 145.2          //主动杆145.2       138.5
#define La2 46872.25                     //        48400
#define Lb2 21083.04             //            19182.25
#define R 92.5 
#define r 22
#define s3 1.732051        //根号3
#define pi 3.1415926
#define t1 70.5
#define t2 4970.25
//t1=R-r;
//t2=t1*t1;



long double targetangle1,targetangle2,targetangle3; 
void xy2angle(long double x,long double y,long double z)    //z最高低限制为：
{

	
long double x2,y2,z2,k1,k2,k3,u1,u2,u3,v1,v2,v3,m1,m2,m3;
	
x2=x*x;
y2=y*y;
z2=z*z;

k1=(La2-Lb2-x2-y2-z2-t2+t1*(s3*x+y))/Lb+2*z;
u1=-2*(2*t1-s3*x-y);
v1=(La2-Lb2-x2-y2-z2-t2+t1*(s3*x+y))/Lb-2*z;

k2=(La2-Lb2-x2-y2-z2-t2-t1*(s3*x-y))/Lb+2*z;
u2=-2*(2*t1+s3*x-y);
v2=(La2-Lb2-x2-y2-z2-t2-t1*(s3*x-y))/Lb-2*z;

k3=(La2-Lb2-x2-y2-z2-t2-t1*y*2)/(2*Lb)+z;
u3=-2*(R-r+y);
v3=(La2-Lb2-x2-y2-z2-t2-t1*y*2)/(2*Lb)-z;

/////////////////取较大的电机角度
if(k1>0)
        m1=(-u1+sqrtf(u1*u1-4*k1*v1))/(2*k1);
else
	  m1=(-u1-sqrtf(u1*u1-4*k1*v1))/(2*k1);
targetangle1=2*atanf(m1)*180/pi;


if(k2>0)
        m2=(-u2+sqrtf(u2*u2-4*k2*v2))/(2*k2);
else
	  m2=(-u2-sqrtf(u2*u2-4*k2*v2))/(2*k2);
targetangle2=2*atanf(m2)*180/pi;


if(k3>0)
        m3=(-u3+sqrtf(u3*u3-4*k3*v3))/(2*k3);
else
	  m3=(-u3-sqrtf(u3*u3-4*k3*v3))/(2*k3);
targetangle3=2*atanf(m3)*180/pi;

if(!(targetangle1<200&&targetangle1>-200&&targetangle2<200&&targetangle2>-200&&targetangle3<200&&targetangle3>-200))
{
  USART_SendData(USART2,'p');
  while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)!= SET);  
  USART_SendData(USART2,'a');
  while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)!= SET); 
  USART_SendData(USART2,'g');
  while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)!= SET); 
  USART_SendData(USART2,'e');
  while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)!= SET); 
  USART_SendData(USART2,' ');
  while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)!= SET); 
  USART_SendData(USART2,'b');
  while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)!= SET); 
  USART_SendData(USART2,'o');
  while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)!= SET); 
  USART_SendData(USART2,'x');
  while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)!= SET); 
  USART_SendData(USART2,0XFF);
  while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)!= SET); 	
  USART_SendData(USART2,0XFF);
  while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)!= SET); 
  USART_SendData(USART2,0XFF);
  while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)!= SET); 	
}
printf("角度:%Lf     %Lf      %Lf\r\n",targetangle1,targetangle2,targetangle3);
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
