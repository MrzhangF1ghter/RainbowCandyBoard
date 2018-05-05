#!/usr/bin/python
# -*- coding:utf-8 -*-
#此版本为中断版本，按键按下时会产生中断，我们利用中断处理函数实现我们的功能
import RPi.GPIO as GPIO
import time

#定义一个存放按键引脚号的列表
keys_pin = [6,13,19,26];

def key_Interrupt(key):
			print("KEY %d PRESS" %(keys_pin.index(key)+1));
	
print("Key Test Program,Interrupt version.");			
GPIO.setmode(GPIO.BCM);#设置为BCM引脚模式
for i in keys_pin:
	GPIO.setup(i,GPIO.IN,GPIO.PUD_UP);#设置为输入 上拉模式
	pass		
#添加事件处理 下降沿触发调用keyx_Interrupt()函数，延时200
for i in range(len(keys_pin)):
	GPIO.add_event_detect(keys_pin[i],GPIO.FALLING,key_Interrupt,200)
	pass
while True:
	time.sleep(1)
