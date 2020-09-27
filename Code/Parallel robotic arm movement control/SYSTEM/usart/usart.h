#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 

#define USART2_REC_LEN  			200  	//定义最大接收字节数 200

extern u16 USART1_RX_STA;         		//接收状态标记
extern u16 USART3_RX_STA;         		//接收状态标记

extern u8 USART2_RX_BUFx[USART2_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART2_RX_STAx;         		//接收状态标记	
extern u8 USART2_RX_BUFy[USART2_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART2_RX_STAy;         		//接收状态标记
extern u8 USART2_RX_BUFz[USART2_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART2_RX_STAz;         		//接收状态标记


void uart2_init(u32 bound);
void uart1_init(u32 bound);
void uart3_init(u32 bound);
void readusart(void);
#endif


