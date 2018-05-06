# MrzhangF1ghterStudio 彩虹RainbowHAT系列
# LED教程 （Python版本）

## 玩转代码
> ### 在我们的彩虹扩展板上 4个按键分别对应着一下GPIO引脚
> |按键 | GPIO | wPi |排针号|
> |----|-----|-----|-----|
> |KEY1|BCM6 |pin22| 34  |    
> |KEY2|BCM13|pin23| 36  |
> |KEY3|BCM19|pin24| 38  |
> |KEY4|BCM26|pin21| 40  |

### 原理图如下:
[RainbowCandyBoard.pdf](https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/schematic/RainbowCandyBoard.pdf)<br>
<img src="https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/key/schematic/key.png" width=50% height=50%/><br>
<img src="https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/key/schematic/key_pin.png" width=50% height=50%/><br>
> 我们采用的是跳帽来连接IO口，你可以在彩虹板上看到有一排彩虹色的跳帽，找到KEY1、KEY2、KEY3、KEY4，那就是与IO连接的端口，具体端口号请看原理图。
> 当我们想接自己io的时候，可以将跳帽拔开，那么板上的外设就和io口断开了，然后插上你想接的外设即可。

### 扫描版本 keyScan.py
```Python
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
```
### 中断版本 keyInterrupt.py
> 首先先用gedit、pluma、vim等文本编辑工具打开该文件夹下的`keyInterrupt.py`,如下，我们可以看看注释进行理解。
```Python
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
	time.sleep(1)#不占用cpu资源，当按键按下进入中断处理
```
## 玩
> 当我们修改了Python版本代码后想运行时，保存后即可运行<br>
> 执行验证
> `./python 程序名`
> 例:`python keyInterrupt.py`
> `python keyScan.py`
> 按了回车后，按下按键将会打印对应按键<br>
> 按下`Ctrl+C`结束程序<br>
