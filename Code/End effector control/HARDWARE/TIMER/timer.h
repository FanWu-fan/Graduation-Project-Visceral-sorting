#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"



#define Steer1_Pmb   1085    //���12Ǧ��λ��
#define Steer2_Pmb   1640

#define Steer1_Cath   1450   //���12ץȡλ��
#define Steer2_Cath  1900
#define Steer3_Cath   950

#define Steer1_Depart 870   //���12����
#define Steer2_Depart  1400
#define Steer3_Depart   2050



void TIM3_PWM_Init_ch1_3(u16 arr,u16 psc);  // ���1�� PA6 ���2��   PA7 ���3��   PB0


 




#endif
