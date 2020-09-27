#ifndef __STEP_MOTOR_H
#define __STEP_MOTOR_H


#define M1DIV               321.903  				//������1��ϸ����
#define M2DIV               321.195  				//������2��ϸ����
#define M3DIV               320.728  				//������3��ϸ����

 
#define plumb1    794               //����Ǧ��ʱ�������Ķ���//  ��ߵ�1280
#define plumb2   3734                                //        ��ߵ�457
#define plumb3    1205                                 //        ��ߵ�2547

#define k_coder 11.3777778         //����������һ�ȵ�ֵ


void  motordir_Init(void);
void motor1running(int dir1,long double Changeangle1);
void motor2running(int dir2,long double Changeangle2);
void motor3running(int dir3,long double Changeangle3);

void motorto_aimangle(long double aimangle1,long double aimangle2,long double aimangle3);//������е�ָ������

void movetocoordinate(long double aimx,long double aimy,long double aimz,int mode) ;

#endif
