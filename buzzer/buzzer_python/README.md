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

### 蜂鸣器模块 buzzzer.py 
```Python
# -- coding: utf-8 --
#导入模块
import RPi.GPIO as GPIO
import time
#定义一个存放led引脚号的列表
buzzer_pin = 12;

def buzzer_init():
#设置引脚模式为BCM引脚号模式
    GPIO.setmode(GPIO.BCM);
#循环遍历存放引脚的数组
    GPIO.setup(buzzer_pin,GPIO.OUT);
#定义蜂鸣器开启函数
def on():
    GPIO.output(buzzer_pin,GPIO.LOW);
#定义蜂鸣器开启函数
def off():
    GPIO.output(buzzer_pin,GPIO.HIGH);
#定义报警鸣叫函数beep(gap_time,on_time),on_time为鸣叫时长，gap_time为鸣叫间隔 单位为秒
def beep(on_time,gap_time):
        GPIO.output(buzzer_pin,GPIO.HIGH);
        print('BUZZER is On');
        time.sleep(on_time);
        GPIO.output(buzzer_pin,GPIO.LOW);
        print('BUZZER is Off');
        time.sleep(gap_time); 
def clean():
	GPIO.output(buzzer_pin,GPIO.HIGH);
	GPIO.cleanup();
```

### 蜂鸣器测试程序 buzzer_test.py 
```Python
# -- coding: utf-8 --
#导入模块
import buzzer

var = 1;
#初始化led引脚
buzzer.buzzer_init();
#初始化后进入一个死循环执行流水灯，通过修改flow(time)，time参数来改变速度（单位秒）
while var == 1:
    buzzer.beep(0.2,1);
```
## 4.玩
> 当我们修改了Python版本代码后想运行时，保存后即可运行<br>
> 执行验证
> `./python 程序名`
>例:`./buzzer_test.py`
>按了回车后，你将会听到蜂鸣器每隔一秒响一次<br>
