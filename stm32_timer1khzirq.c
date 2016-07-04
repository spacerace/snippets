void TIM2_IRQHandler(void)
{  
  //if interrupt happens the do this
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
  {
    //clear interrupt and start counting again to get precise freq
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    //toggle led
    GPIOE->ODR ^= GPIO_Pin_0;
    
    lcd_print_image_fast(&max, 0, 0);
  }

}

void setup_timirq() {
	TIM_TimeBaseInitTypeDef TIM_TimeBase_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	uint16_t psc;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	// 36mhz? 
	
	psc = (uint16_t) 36000 - 1;
	
	TIM_TimeBase_InitStructure.TIM_Prescaler = psc;
	TIM_TimeBase_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;	// nach psc = 1khz
	TIM_TimeBase_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBase_InitStructure.TIM_Period = 50;	/// 1000 = 1hz,	20=50hz
	
	TIM_TimeBaseInit(TIM2, &TIM_TimeBase_InitStructure);
	
	TIM_PrescalerConfig(TIM2, psc, TIM_PSCReloadMode_Immediate);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	
 // Enable and set TIM1 Interrupt to the lowest priority
  // Enable the TIM1 global Interrupt
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  TIM_Cmd(TIM2, ENABLE);
  TIM_ClearITPendingBit(TIM2,TIM_IT_Update);	
	
}