#define CLK PB0
#define DIN PB2
#define CS PB1
#define DOUT PB4
#define PORT_CLK PORTB
#define PORT_DIN PORTB
#define PORT_CS PORTB
#define PORT_DOUT PORTB
#define DDR_CLK DDRB
#define DDR_DIN DDRB
#define DDR_CS DDRB
#define DDR_DOUT DDRB
#define PIN_DOUT PINB
#define SET_CS PORT_CS |=(1<<CS)
#define CLR_CS PORT_CS &=~(1<<CS)
#define SET_CLK PORT_CLK |=(1<<CLK)
#define CLR_CLK PORT_CLK &=~(1<<CLK)
#define SET_DIN PORT_DIN |=(1<<DIN)
#define CLR_DIN PORT_DIN &=~(1<<DIN)
#define GET_DOUT (PIN_DOUT &(1<<DOUT))

DDR_DIN &= ~(1<<DIN);
PORT_DIN |= (1<<DIN);
DDR_DIN  |= (1<<DIN);
DDR_CLK  |= (1<<CLK);
DDR_CS   |= (1<<CS);

get_ads7841(0);

unsigned short get_ads7841(char channel) {
    unsigned char i, control_byte;    
    unsigned short dat = 0;            

    control_byte = 0x97;    // default channel 0
    switch(channel) {        // if a channel between 1 and 3 is given, change the control byte
        case 1: control_byte = 0xD7; break;
        case 2: control_byte = 0xA7; break;
        case 3: control_byte = 0xE7; break;
    }

    CLR_CLK;
    CLR_DIN;
    CLR_CS;

    for(i=0; i<8; i++) {                    // send control byte to ADS7841
        if(control_byte & 0x80) SET_DIN;
        else CLR_DIN;
        CLR_CLK;
        SET_CLK;
        control_byte = control_byte<<1;      /* Shift bit once next time */
    }
    CLR_CLK;
    SET_CLK;

    for(i=0; i<12; i++)    {                    // read data from ADS7841 (12bits)
        CLR_CLK;
        SET_CLK;
        dat = dat<<1;            
        dat = dat | GET_DOUT;     
    }

    for(i=0;i<4;i++) {                         // we have to do four clock transitions, to because we only need 12bits
        CLR_CLK;
        SET_CLK;
    }

    SET_CS; 

    return dat>>4;
}
