/* get_max127()
*
* address - I2C bus address 
* channel - Der Kanal, von 0 bis 7
* mode - 0 = 0-5V messung, 1 = 0-10V messung
* 2 = +-5V messung, 3 = +-10V messung
*
*/ 
unsigned short get_max127(unsigned char address, unsigned char channel,unsigned char mode) {
    unsigned char high, low, ret, config_byte;
    unsigned short value;
    if(channel > 7) return 0;

     ret = i2c_start(address);                                      // start communication
    if(ret == 0) {                                                // chip found
        if(mode == 3) config_byte = (0x8c | (channel<<4));        // configuration byte, for information see datasheet
        else if(mode == 2) config_byte = (0x84 | (channel<<4));
        else if(mode == 1) config_byte = (0x88 | (channel<<4)); 
        else config_byte = (0x80 | (channel<<4));
         i2c_write(config_byte);
        i2c_stop();

        i2c_start(address+1);
        high = i2c_readAck();
        low = i2c_readNak();
        i2c_stop();
        value = ((high<<8)|low);
        value >>= 4;
    } else {
        return 0;
    }
    return value;
}
