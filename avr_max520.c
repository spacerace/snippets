#define DAC_CH0 0x00
#define DAC_CH1 0x01
#define DAC_CH2 0x02
#define DAC_CH3 0x03

#define DAC_ADDRESS 0x5e

void set_max520(unsigned char address, unsigned char channel, unsigned char value) {
    if(channel > 0x03) return;
    i2c_start(address);
    i2c_write(channel);
    i2c_write(value);
    i2c_stop();
    return;
}

/* setzen des DAC Ausgangs 0 auf den Wert 127 */
set_max520(0x5e, DAC_CH0, 127);
