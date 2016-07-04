#include "stm32f10x.h"

#define outPort GPIOA
#define serialOUT GPIO_Pin_0
#define clk GPIO_Pin_1


/* PE0 = Button
 * PE1 = CLK
 * PE2 = DATA 
 * PE3 = OE
 * PE4 = STROBE 
 */

void Delay(uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}

void strobeCLK(void);

void init_4094(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	GPIO_InitStructure.GPIO_Pin   = ( GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 ); 
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(outPort, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOE, GPIO_Pin_2 | GPIO_Pin_1);	// DATA | CLOCK
	
	GPIO_SetBits(GPIOE, GPIO_Pin_3 | GPIO_Pin_4);	// OE | STROBE
	
// 	dataOUT(0x0);
}

void write_4094(uint8_t d) {
	uint8_t i;
	Delay(0xff);
	for(i=0x80;i>=1;i/=2) {
		if(d & i)
			GPIO_SetBits(GPIOE, GPIO_Pin_2);
		else
			GPIO_ResetBits(GPIOE, GPIO_Pin_2);
		strobeCLK();
	}
}

void strobeCLK(void) {
	Delay(0xf);
	GPIO_SetBits(outPort, clk);
	Delay(0xf);
	GPIO_ResetBits(outPort, clk);
}