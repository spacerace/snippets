int main(void) {
    char buffer[25];
    unsigned char contrast = 0;

    lcd_init(LCD_DISP_ON);
    lcd_clrscr();
    lcd_puts("hello world");

    DDRD |= (1<<PD5)|(1<<PD4);    // OC1A, OC1B for contrast and backlight

    DDRB &= ~((1<<PB0)|(1<<PB1));    // buttons
    PORTB |= (1<<PB0)|(1<<PB1);    // pullups for buttons

    TCCR1A = (1<<WGM10) | (1<<COM1A1) | (1<<COM1B1);
    TCCR1B = (1<<CS10);
    OCR1A = 0xff;
    OCR1B = 0x60;

    for (;;) {
        if(!(PINB&(1<<PB0))) { OCR1A++; _delay_ms(25); }
        if(!(PINB&(1<<PB1))) { OCR1B++;  _delay_ms(25); }
    }
}
