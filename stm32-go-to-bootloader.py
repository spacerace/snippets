#!/usr/bin/python

import serial

ser = serial.Serial('/dev/ttyUSB0', 115200)
print ser.name
ser.write('G')
ser.write('B')
ser.write('L')
ser.write('\r')
ser.close