/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * mcurses-config.h - configuration file for mcurses lib
 *
 * Copyright (c) 2011-2015 Frank Meyer - frank(at)fli4l.de
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */

#define MCURSES_BAUD                19200L          // UART baudrate, use 115200 on STM32Fxx
#define MCURSES_UART_NUMBER         0               // UART number on STM32Fxxx (1-6), else ignored

#define MCURSES_LINES               24              // 24 lines
#define MCURSES_COLS                80              // 80 columns
