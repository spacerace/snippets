void setup_debug_pins() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

GPIO_ResetBits(GPIOE, GPIO_Pin_0);	GPIO_SetBits(GPIOE, GPIO_Pin_0);