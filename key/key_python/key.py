#!/usr/bin/python
# -*- coding:utf-8 -*-
import RPi.GPIO as GPIO
import time

KEY = 20

GPIO.setmode(GPIO.BCM)
GPIO.setup(KEY,GPIO.IN,GPIO.PUD_UP)
print("Key Test Program")
while True:
	time.sleep(0.05)
	if GPIO.input(KEY) == 0:
		print("KEY PRESS")
		while GPIO.input(KEY) == 0:
			time.sleep(0.01)
