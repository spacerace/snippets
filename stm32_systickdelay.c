volatile uint32_t msTicks;

void SysTick_Handler(void) {
	msTicks++;
}

void Delay (uint32_t delayTicks) {                                              
  uint32_t currentTicks;

  currentTicks = msTicks;
  while ((msTicks - currentTicks) < delayTicks);
}