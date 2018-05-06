# MrzhangF1ghterStudio 彩虹RainbowHAT系列
# LED教程 （Python版本）

## 玩转代码
> ### 在我们的彩虹扩展板上 4盏LED分别对应着一下GPIO引脚
> 灯   | GPIO | wPi |排针号|
> |----|-----|-----|-----|
> |LED1|BCM17|pin0 | 11 |    
> |LED2|BCM27|pin2 |13  |
> |LED3|BCM22|pin3 |15  |
> |LED4|BCM5 |pin21|29  |

### 原理图如下:
[RainbowCandyBoard.pdf](https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/schematic/RainbowCandyBoard.pdf)<br>
<img src="https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/led/schematic/LED.png" width=50% height=50%/><br>
<img src="https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/led/schematic/led_pin.png" width=50% height=50%/><br>
> 我们采用的是跳帽来连接IO口，你可以在彩虹板上看到有一排彩虹色的跳帽，找到LED1、LED2、LED3、LED4，那就是与IO连接的端口，具体端口号请看原理图。
> 当我们想接自己io的时候，可以将跳帽拔开，那么板上的外设就和io口断开了，然后插上你想接的外设即可。

> Python版本中，我们将led看做一个模块，当我们要使用led的时候导入这个模块使用。`led.py`就是我们的模块，`led_test.py`就是我们的测试程序
> 首先先用gedit、puma、vim等文本编辑工具打开该文件夹下的`led.py`,如下，我们可以看看注释进行理解。
> ### led模块 led.py 
```Python
# -- coding: utf-8 --
#导入模块
import RPi.GPIO as GPIO
import time
#定义一个存放led引脚号的列表
leds_pin = [17,27,22,5];

def led_init():
#设置引脚模式为BCM引脚号模式
    GPIO.setmode(GPIO.BCM);
#循环遍历存放引脚的数组
    for x in leds_pin:
        GPIO.setup(x,GPIO.OUT);
        pass
#定义点亮led的函数on(i),参数为led号，编号范围为1~4,低电平点亮
def on(i):
    if(i>=1 and i<=4):
        GPIO.output(leds_pin[i-1],GPIO.LOW);
#定义熄灭led的函数on(i),参数为led号，编号范围为1~4
def off(i):
    if(i>=1 and i<=4):
        GPIO.output(leds_pin[i-1],GPIO.HIGH);
#定义流水灯函数flow(time),time为流水速度，单位为秒
def flow(delay):
    for i in range(len(leds_pin)):
        GPIO.output(leds_pin[i],GPIO.LOW);
        print('LED',i+1,'is on');
        time.sleep(delay);
        GPIO.output(leds_pin[i],GPIO.HIGH);
        print('LED',i+1,'is off');
        time.sleep(delay);
#GPIO清理函数，调用后释放GPIO
def clean():
    GPIO.cleanup();
```

> ### led测试程序 led_test.py 
```Python
# -- coding: utf-8 --
#导入模块
import led

var = 1;
#初始化led引脚
led.led_init();
#初始化后进入一个死循环执行流水灯，通过修改flow(time)，time参数来改变速度（单位秒）
while var == 1:
	led.flow(0.5);
led.clean();
```
## 玩
> 当我们修改了Python版本代码后想运行时，保存后即可运行<br>
> 执行验证
> `python 程序名`
> 例:`python led_test.py`
> 按了回车后，你将会发现彩虹板上的LED随着你的要求而亮灭<br>
> 按下`Ctrl+C`结束程序<br>
