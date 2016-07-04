ISR (TIMER0_OVF_vect) {
	// event to be exicuted every 8ms here
	seg_off(active_seg);
	
	active_seg ++;
	if(active_seg == 4) active_seg = 0;
	
	write_hex(seg[active_seg]);
	seg_on(active_seg);	
}


// timer0 8ms @ 8Mhz
void init_timer(void) {
	TIMSK |= (1 << TOIE0);
	TCCR0 |= ((1 << CS02)|(1<<CS00));    // set prescaler to 256 and start the timer
	seg[0] = 0;
	seg[1] = 1;
	seg[2] = 2;
	seg[3] = 3;
	
	active_seg = 0;

}








int main(void)
{
    OCR1A = 15624;

    TCCR1B |= (1 << WGM12);
    // Mode 4, CTC on OCR1A

    TIMSK |= (1 << OCIE1A);
    //Set interrupt on compare match

    TCCR1B |= (1 << CS12) | (1 << CS10);
    // set prescaler to 1024 and start the timer


    sei();
    // enable interrupts


    while (1);
    {
        // we have a working Timer
    }
}

ISR (TIMER1_COMPA_vect)
{
    // action to be done every 1 sec
}