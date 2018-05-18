#!/usr/bin/python
# -*- coding:utf-8 -*-
import serial

ser = serial.Serial("/dev/ttyAMA0",115200)
#ser = serial.Serial("/dev/ttyS0",115200)

print('serial test start ...')
ser.write("Hello Wrold !!!\n")
try:
	while True:
		ser.write(ser.read())
except KeyboardInterrupt:
	if ser != None:
		ser.close()
