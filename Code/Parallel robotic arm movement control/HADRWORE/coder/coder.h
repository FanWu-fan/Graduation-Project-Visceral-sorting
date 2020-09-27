#ifndef __CODER_H
#define __CODER_H


#include "sys.h"
#include "delay.h"


 /*编码器型号BRT38-S0M4096   SSI通讯模式     */
#define clk1_x   GPIOC        //Pc10
#define clk1_pin     GPIO_Pin_10
#define clk1 			PCout(10)
#define clk1_H     GPIO_SetBits(clk1_x,clk1_pin)
#define clk1_L     GPIO_ResetBits(clk1_x,clk1_pin)


#define Do1_x		GPIOC          //Pc11
#define Do1_pin			GPIO_Pin_11
#define Do1 				PCin(11)
 
#define cs1_x		GPIOC         //Pc12
#define cs1_pin			GPIO_Pin_12
#define cs1 				PCout(12)
 #define cs1_H     GPIO_SetBits(cs1_x,cs1_pin)
#define cs1_L     GPIO_ResetBits(cs1_x,cs1_pin)


////////////////////////////////////////////////////////////////
#define clk2_x   GPIOE        //PE0
#define clk2_pin     GPIO_Pin_0
#define clk2 			PEout(0)
#define clk2_H     GPIO_SetBits(clk2_x,clk2_pin)
#define clk2_L     GPIO_ResetBits(clk2_x,clk2_pin)


#define Do2_x		GPIOE          //PE1
#define Do2_pin			GPIO_Pin_1
#define Do2 				PEin(1)
 
#define cs2_x		GPIOF         //PF3
#define cs2_pin			GPIO_Pin_3
#define cs2 				PFout(3)
 #define cs2_H     GPIO_SetBits(cs2_x,cs2_pin)
#define cs2_L     GPIO_ResetBits(cs2_x,cs2_pin)

///////////////////////////////////////////////////////
#define clk3_x   GPIOE        //PE3
#define clk3_pin     GPIO_Pin_3
#define clk3 			PEout(3)
#define clk3_H     GPIO_SetBits(clk3_x,clk3_pin)
#define clk3_L     GPIO_ResetBits(clk3_x,clk3_pin)


#define Do3_x		GPIOE          //PE4
#define Do3_pin			GPIO_Pin_4
#define Do3 				PEin(4)
 
#define cs3_x		GPIOE         //PE6
#define cs3_pin			GPIO_Pin_6
#define cs3 				PEout(6)
 #define cs3_H     GPIO_SetBits(cs3_x,cs3_pin)
#define cs3_L     GPIO_ResetBits(cs3_x,cs3_pin)

	 
	 
void coder_init(void);
int coder1(void);
int coder2(void);
int coder3(void);
void Delay_SSI(u32 nCount);













#endif 
