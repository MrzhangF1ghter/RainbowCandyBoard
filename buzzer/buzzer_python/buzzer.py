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
#定义报警鸣叫函数beep(on_time,time),on_time为鸣叫时长，time为鸣叫间隔 单位为秒
def beep(time):
        GPIO.output(buzzer_pin,GPIO.LOW);
        print('BUZZER is On);
        time.sleep(on_time);
        GPIO.output(buzzer_pin,GPIO.HIGH);
        time.sleep(time); 
def clean():
    GPIO.cleanup();

