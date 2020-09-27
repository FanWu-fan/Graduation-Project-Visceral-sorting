#include "coder.h"
#include "sys.h"

	 

void coder_init()
{
	
 GPIO_InitTypeDef GPIO_InitStructure;

RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOF,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode= GPIO_Mode_Out_PP;               //clk1  PC10
	GPIO_InitStructure.GPIO_Pin=clk1_pin;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(clk1_x,&GPIO_InitStructure);
	GPIO_SetBits(clk1_x,clk1_pin);	
	
      GPIO_InitStructure.GPIO_Mode= GPIO_Mode_Out_PP;               //cs1  PC12
	GPIO_InitStructure.GPIO_Pin=cs1_pin;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(cs1_x,&GPIO_InitStructure);
      GPIO_SetBits(cs1_x,cs1_pin);
	
	GPIO_InitStructure.GPIO_Mode= GPIO_Mode_IN_FLOATING;               //Do1  PC11
	GPIO_InitStructure.GPIO_Pin=Do1_pin;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(Do1_x,&GPIO_InitStructure);



	GPIO_InitStructure.GPIO_Mode= GPIO_Mode_Out_PP;               //clk2 PE0
	GPIO_InitStructure.GPIO_Pin=clk2_pin;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(clk2_x,&GPIO_InitStructure);
	GPIO_SetBits(clk2_x,clk2_pin);
	
      GPIO_InitStructure.GPIO_Mode= GPIO_Mode_Out_PP;               //cs2 PF3
	GPIO_InitStructure.GPIO_Pin=cs2_pin;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(cs2_x,&GPIO_InitStructure);
      GPIO_SetBits(cs2_x,cs2_pin);
	
	GPIO_InitStructure.GPIO_Mode= GPIO_Mode_IN_FLOATING;               //Do2 PE1
	GPIO_InitStructure.GPIO_Pin=Do2_pin;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(Do2_x,&GPIO_InitStructure);



	GPIO_InitStructure.GPIO_Mode= GPIO_Mode_Out_PP;               //clk3 PE3
	GPIO_InitStructure.GPIO_Pin=clk3_pin;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(clk3_x,&GPIO_InitStructure);
	GPIO_SetBits(clk3_x,clk3_pin);
	
      GPIO_InitStructure.GPIO_Mode= GPIO_Mode_Out_PP;               //cs3 PE6
	GPIO_InitStructure.GPIO_Pin=cs3_pin;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(cs3_x,&GPIO_InitStructure);
      GPIO_SetBits(cs3_x,cs3_pin);
	
	GPIO_InitStructure.GPIO_Mode= GPIO_Mode_IN_FLOATING;               //Do3 PE4
	GPIO_InitStructure.GPIO_Pin=Do3_pin;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(Do3_x,&GPIO_InitStructure);
	


}

void Delay_SSI(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}





 int coder1(void)//获得编码器位置
 {
	 int i=0;
	 u32	wdata1=0;
		cs1_H;
	      clk1_H;
	  Delay_SSI(0xF);//1530ns
	
	  cs1_L;
	 for(i=0; i<12; i++)          //循环12次
	{
		clk1_L;
		Delay_SSI(0xF);
		clk1_H;
		Delay_SSI(0xF);
		wdata1|=Do1;
            wdata1<<=1;
	}
	wdata1>>=1;
	
 return wdata1;
}
 
 int coder2(void)//获得编码器位置
 {
	 int i=0;
	 u32	wdata2=0;
		cs2_H;
	 clk2_H;
	  Delay_SSI(0xF);//1530ns
	
	  cs2_L;
	  Delay_SSI(0xF);
	 for(i=0; i<12; i++)          //循环12次
	{
		
		clk2_L;
		Delay_SSI(0xF);
		clk2_H;
		Delay_SSI(0xF);
		wdata2|=Do2;//按位或
    wdata2<<=1;//左移一位，最后一位补0
	}
	wdata2>>=1;//右移一位，最后一位补0
	cs2_H;
	Delay_SSI(0xF);
	cs2_L;
	clk2_H;

 return wdata2;
}
 
  int coder3(void)//获得编码器位置
 {
	 int i=0;
	 u32	wdata3=0;
		cs3_H;
	 clk3_H;
	  Delay_SSI(0xF);//1530ns
	
	  cs3_L;
	  Delay_SSI(0xF);
	 for(i=0; i<12; i++)          //循环12次
	{
		
		clk3_L;
		Delay_SSI(0xF);
		clk3_H;
		Delay_SSI(0xF);
		wdata3|=Do3;//按位或
    wdata3<<=1;//左移一位，最后一位补0
	}
	wdata3>>=1;//右移一位，最后一位补0
	cs3_H;
	Delay_SSI(0xF);
	cs3_L;
	clk3_H;

 return wdata3;
}
 
 
 
 
 
