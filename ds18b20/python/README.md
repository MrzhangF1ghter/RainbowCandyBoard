# MrzhangF1ghterStudio 彩虹RainbowHAT系列
# 蜂鸣器BUZZER教程 （Python版本）

## 玩转代码
> ### 在我们的彩虹扩展板上 蜂鸣器对应着一下接口<br>
> 蜂鸣器| GPIO | wPi |排针号|
> |----|-----|-----|-----|
> |BUZZER|BCM12|pin26|32|   

### 原理图如下:
[RainbowCandyBoard.pdf](https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/schematic/RainbowCandyBoard.pdf)<br>
<img src="https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/led/schematic/LED.png" width=50% height=50%/><br>
<img src="https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/led/schematic/led_pin.png" width=50% height=50%/><br>
> 我们采用的是跳帽来连接IO口，你可以在彩虹板上看到有一排彩虹色的跳帽，找到LED1、LED2、LED3、LED4，那就是与IO连接的端口，具体端口号请看原理图。
> 当我们想接自己io的时候，可以将跳帽拔开，那么板上的外设就和io口断开了，然后插上你想接的外设即可。

> Python版本中，我们将led看做一个模块，当我们要使用led的时候导入这个模块使用。`led.py`就是我们的模块，`led_test.py`就是我们的测试程序
> 首先先用gedit、puma、vim等文本编辑工具打开该文件夹下的`led.py`,如下，我们可以看看注释进行理解。

### ds18b20.py 
```Python
#!/usr/bin/python
# -*- coding:utf-8 -*-
import os
import glob
import time

os.system('modprobe w1-gpio')
os.system('modprobe w1-therm')

base_dir = '/sys/bus/w1/devices/'
device_folder = glob.glob(base_dir + '28*')[0]
device_file = device_folder + '/w1_slave'
def read_rom():
	name_file=device_folder+'/name'
	f = open(name_file,'r')
	return f.readline()

def read_temp_raw():
	f = open(device_file, 'r')
	lines = f.readlines()
	f.close()
	return lines

def read_temp():
	lines = read_temp_raw()
	while lines[0].strip()[-3:] != 'YES':
		time.sleep(0.2)
		lines = read_temp_raw()
	equals_pos = lines[1].find('t=')
	if equals_pos != -1:
		temp_string = lines[1][equals_pos+2:]
		temp_c = float(temp_string) / 1000.0
		temp_f = temp_c * 9.0 / 5.0 + 32.0
		return temp_c, temp_f

print(' rom: '+ read_rom())
while True:
	print(' C=%3.3f  F=%3.3f'% read_temp())
	time.sleep(1)
```
## 4.玩
> 当我们修改了Python版本代码后想运行时，保存后即可运行<br>
> 执行验证
> `python 程序名`
>例:`python ds18b20.py`
>按了回车后，终端将会循环打印当前温度<br>
