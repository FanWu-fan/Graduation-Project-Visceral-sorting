#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 

#define USART2_REC_LEN  			200  	//�����������ֽ��� 200

extern u16 USART1_RX_STA;         		//����״̬���
extern u16 USART3_RX_STA;         		//����״̬���

extern u8 USART2_RX_BUFx[USART2_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART2_RX_STAx;         		//����״̬���	
extern u8 USART2_RX_BUFy[USART2_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART2_RX_STAy;         		//����״̬���
extern u8 USART2_RX_BUFz[USART2_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART2_RX_STAz;         		//����״̬���


void uart2_init(u32 bound);
void uart1_init(u32 bound);
void uart3_init(u32 bound);
void readusart(void);
#endif


