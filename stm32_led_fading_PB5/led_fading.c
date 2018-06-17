#include "systick.h"
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include <stdint.h>

void set_pwm_pb5(int val);
void init_pwm_pb5(void);

static uint16_t pwmtable[64] = {
    0, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 4, 4, 5, 5, 6, 6, 7, 8, 9, 10,
    11, 12, 13, 15, 17, 19, 21, 23, 26, 29, 32, 36, 40, 44, 49, 55,
    61, 68, 76, 85, 94, 105, 117, 131, 146, 162, 181, 202, 225, 250,
    279, 311, 346, 386, 430, 479, 534, 595, 663, 739, 824, 918, 1023
};

static uint16_t pwmtable16[256] = {
    0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3,
    3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 7,
    7, 7, 8, 8, 8, 9, 9, 10, 10, 10, 11, 11, 12, 12, 13, 13, 14, 15,
    15, 16, 17, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
    31, 32, 33, 35, 36, 38, 40, 41, 43, 45, 47, 49, 52, 54, 56, 59,
    61, 64, 67, 70, 73, 76, 79, 83, 87, 91, 95, 99, 103, 108, 112,
    117, 123, 128, 134, 140, 146, 152, 159, 166, 173, 181, 189, 197,
    206, 215, 225, 235, 245, 256, 267, 279, 292, 304, 318, 332, 347,
    362, 378, 395, 412, 431, 450, 470, 490, 512, 535, 558, 583, 609,
    636, 664, 693, 724, 756, 790, 825, 861, 899, 939, 981, 1024, 1069,
    1117, 1166, 1218, 1272, 1328, 1387, 1448, 1512, 1579, 1649, 1722,
    1798, 1878, 1961, 2048, 2139, 2233, 2332, 2435, 2543, 2656, 2773,
    2896, 3025, 3158, 3298, 3444, 3597, 3756, 3922, 4096, 4277, 4467,
    4664, 4871, 5087, 5312, 5547, 5793, 6049, 6317, 6596, 6889, 7194,
    7512, 7845, 8192, 8555, 8933, 9329, 9742, 10173, 10624, 11094,
    11585, 12098, 12634, 13193, 13777, 14387, 15024, 15689, 16384,
    17109, 17867, 18658, 19484, 20346, 21247, 22188, 23170, 24196,
    25267, 26386, 27554, 28774, 30048, 31378, 32768, 34218, 35733,
    37315, 38967, 40693, 42494, 44376, 46340, 48392, 50534, 52772,
    55108, 57548, 60096, 62757, 65535
};


void fading(void) {
	int i;
	
	init_pwm_pb5();
	
	for(;;) {
			for(i = 0; i < 64; i++) {
				set_pwm_pb5(pwmtable[i]);
				systick_delay(20);
			}
			for(i = 63; i >= 0; i--) {
				set_pwm_pb5(pwmtable[i]);
				systick_delay(20);
			}
	}
	
}

void set_pwm_pb5(int val) {
	TIM_OCInitTypeDef oc_bl;
	
	oc_bl.TIM_OCMode = TIM_OCMode_PWM1;
	oc_bl.TIM_OutputState = TIM_OutputState_Enable;
	oc_bl.TIM_Pulse = (val & 0x3FF);
	oc_bl.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC2Init(TIM3, &oc_bl);	
}

void init_pwm_pb5(void) {
	GPIO_InitTypeDef GPIO_InitData;
	TIM_TimeBaseInitTypeDef TimeBase_InitData;
	
	const uint16_t period = (uint16_t) (SystemCoreClock / 1000000) - 1;

	/* enable clock for GPIO, PWM pin and TIM3 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	/* configure PWM pin */
	GPIO_InitData.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitData.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitData.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitData);
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);
	
	/* setup PWM */
	TimeBase_InitData.TIM_ClockDivision = 0;
	TimeBase_InitData.TIM_CounterMode = TIM_CounterMode_Up;
	TimeBase_InitData.TIM_RepetitionCounter = 0;
	TimeBase_InitData.TIM_Prescaler = period;
	TimeBase_InitData.TIM_Period = 999;
	TIM_TimeBaseInit(TIM3, &TimeBase_InitData);
	
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM3, ENABLE);
	TIM_Cmd(TIM3, ENABLE);	
}
