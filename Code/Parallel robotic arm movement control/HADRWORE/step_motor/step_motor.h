#ifndef __STEP_MOTOR_H
#define __STEP_MOTOR_H


#define M1DIV               321.903  				//定义电机1的细分数
#define M2DIV               321.195  				//定义电机2的细分数
#define M3DIV               320.728  				//定义电机3的细分数

 
#define plumb1    794               //定义铅锤时编码器的读数//  最高点1280
#define plumb2   3734                                //        最高点457
#define plumb3    1205                                 //        最高点2547

#define k_coder 11.3777778         //编码器精度一度的值


void  motordir_Init(void);
void motor1running(int dir1,long double Changeangle1);
void motor2running(int dir2,long double Changeangle2);
void motor3running(int dir3,long double Changeangle3);

void motorto_aimangle(long double aimangle1,long double aimangle2,long double aimangle3);//电机运行到指定度数

void movetocoordinate(long double aimx,long double aimy,long double aimz,int mode) ;

#endif
