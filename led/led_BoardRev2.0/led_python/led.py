# -- coding: utf-8 --
#导入模块
import RPi.GPIO as GPIO
import time
#定义一个存放led引脚号的列表
leds_pin = [23,27,22,5];

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

