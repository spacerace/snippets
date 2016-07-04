#ifndef __ENCODER_H__
#define __ENCODER_H__

void init_encoder();
#define get_encoder0()	TIM_GetCounter(TIM5)
#define get_encoder1()	TIM_GetCounter(TIM8)

#endif // __ENCODER_H__