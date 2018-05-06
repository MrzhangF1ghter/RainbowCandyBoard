#!/usr/bin/python
# -*- coding:utf-8 -*-
#此版本为扫描法判断按键是否按下，耗费cpu资源，建议使用中断法实现
import RPi.GPIO as GPIO
import time
i=0;
#定义一个存放按键引脚号的列表
keys_pin = [6,13,19,26];

print("Key Test Program");
GPIO.setmode(GPIO.BCM);#设置为BCM引脚模式
for x in keys_pin:
	GPIO.setup(x,GPIO.IN,GPIO.PUD_UP);#设置为输入 上拉模式
	pass
	
while True:
	i=i+1;
	time.sleep(0.05)#休眠5毫秒扫描一次按键是否按下
	if GPIO.input(keys_pin[i]) == 0:
		print("KEY %d PRESS" %(i+1));
		while GPIO.input(keys_pin[i]) == 0:#消抖
			time.sleep(0.01);
	if(i==3):
		i=-1;
