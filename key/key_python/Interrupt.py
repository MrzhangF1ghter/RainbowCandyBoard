#!/usr/bin/python
# -*- coding:utf-8 -*-
import RPi.GPIO as GPIO
import time

KEY = 20

def MyInterrupt(KEY):
	print("KEY PRESS")
GPIO.setmode(GPIO.BCM)
GPIO.setup(KEY,GPIO.IN,GPIO.PUD_UP)
GPIO.add_event_detect(KEY,GPIO.FALLING,MyInterrupt,200)

while True:
	time.sleep(1)
