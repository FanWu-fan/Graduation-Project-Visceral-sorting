#ifndef __PWM_H
#define __PWM_H
#include "stm32f10x.h"
#include "sys.h"
#include "pwm.h"
#include  "string.h"


/*定义各个电机使用的定时器抢占优先级和子优先级*/
#define PWM1_PreemptionPriority 1            
#define PWM1_SubPriority 0					
#define PWM2_PreemptionPriority 1  
#define PWM2_SubPriority 1					
#define PWM3_PreemptionPriority 2  
#define PWM3_SubPriority 0					
	






void Initial_Motor1_SlaveTimer(void);
void Initial_Motor2_SlaveTimer(void);
void Initial_Motor3_SlaveTimer(void);
void Initial_PWM_Motor1(void);
void Initial_PWM_Motor2(void);
void Initial_PWM_Motor3(void);





#endif
