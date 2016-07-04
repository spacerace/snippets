void test48k_ram(int quick) {
	uint32_t size = 12288;
	uint32_t data[(49152/4)];
	uint32_t i;
	uint32_t pattern0 = 0xDEADBEEF;
	uint32_t errors = 0;
	char temp[32];

	sprintf(temp, "ram test %lu 4b-words: \n", size);
	lcd_con_puts(temp);


	for(i = 0; i < size; i++) {
		data[i] = pattern0;
		if(pattern0 != data[i]) {
			errors++;
		}
		else {
			if(!quick) {
				sprintf(temp, "%ub ok\r", i*4);
				lcd_con_puts(temp);
			}
		}
	}

	if(quick) {
		sprintf(temp, "%ub ok", i*4);
		lcd_con_puts(temp);
	}
	lcd_con_puts("\n");

	sprintf(temp, "errors: %u", errors);
	lcd_con_puts(temp);

}
