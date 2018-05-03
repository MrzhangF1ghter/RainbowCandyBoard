# MrzhangF1ghterStudio 彩虹RainbowHAT系列
# LED教程 （Python版本）
## 1.首先先下载源码，源码下载步骤如下(若已下载，则可跳过)
> 1.1 首先我们要安装git工具，若无则在终端中输入:<br>
> `sudo apt-get install git-core`<br>
> 如果在过程中出现错误，尝试更新软件源,然后再重试：<br>
> `sudo apt-get update`<br>
> 1.2 定位到你想下载源代码文件夹的位置,比如我想放到用户目录下
> `cd ~\` ~代表当前用户的home目录<br>
> 1.3 通过 git 在线获得我提供的最新源代码，输入命令：<br>
> `git clone git:github.com/MrzhangF1ghter/RainbowCandyBoard.git`<br>
> 等待完成done
> 1.4 进入源码库所在的文件夹，该文件夹在前面无操作的话，就在你的家目录下<br>
> `cd ~/RainbowCandyBoard/LED/led_python/`<br>
> 1.5 执行`ls`指令，你将会看到有两个文件，一个是`led.py`，一个是`led_test.py`<br>
> 你可以输入`./python led_test.py`来测试效果,若Python开发环境安装无误的话，你将会看到彩虹扩展板上的4盏灯在轮流闪动，也就是流水灯效果<br>
> 1.6 若需要更新彩虹板的源码库，输入以下命令：<br>
> `cd ~`<br>(cd到你之前放源码的地方)
> `git pull origin`<br>

## 2.安装Python
> ### 下面是安装Python开发环境的教程，若安装好了则跳过。
> 2.1 首先我们要安装python-dev工具，在终端中输入:<br>
> `sudo apt-get install python-dev`<br>
> 如果在过程中出现错误，尝试更新软件源,然后再重试：<br>
> `sudo apt-get update`<br>
> 2.2 安装RPi.GPIO和spidev<br>
> 先下载安装包（RPi.GPIO安装包和spidev安装包，参见：https://pypi.python.org/pypi/RPi.GPIOhttps://pypi.python.org/pypi/spidev ），然后通过ftp等方式把下载好的文件解压到树莓派上。<br>
> 2.3 接着进入对应的文件夹内，进行安装<br>
> `sudo python setup.py install`(输入指令时为RPI.GPIO所在的文件夹)<br>
> `sudo python setup.py install`(输入指令时为spidev-x.x所在的文件夹)<br>
> 2.4 安装smbus库，I2C接口库函数<br>
> `sudo apt-get install python-smbus`<br>
> 2.5 安装serial库，UART接口库函数<br>
> `sudo apt-get install python-serial`<br>
> 到此，Python开发环境安装完成<br>
## 3.玩转代码
> ### 在我们的彩虹扩展板上 蜂鸣器对应着一下接口<br>
> 蜂鸣器| GPIO | wPi |排针号|
> |----|-----|-----|-----|
> |BUZZER|BCM12|pin26|32|    

### 原理图如下:
[RainbowCandyBoard.pdf](https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/%E5%8E%9F%E7%90%86%E5%9B%BE/RainbowCandyBoard.pdf)
![image](https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/BUZZER/%E5%8E%9F%E7%90%86%E5%9B%BE/jumper.png)
> 我们采用的是跳帽来连接IO口，你可以在彩虹板上看到有一排彩虹色的跳帽，找到BUZZER，那就是蜂鸣器外设与IO连接的端口，具体端口号请看原理图。
> 当我们想接自己io的时候，可以将跳帽拔开，那么板上的外设就和io口断开了，然后插上你想接的外设即可。

> Python版本中，我们将蜂鸣器看做一个模块，当我们要使用蜂鸣器的时候导入这个模块使用。`buzzer.py`就是我们的模块，`buzzer_test.py`就是我们的测试程序
首先先用gedit、puma、vim等文本编辑工具打开该文件夹下的`buzzer.py`,如下，我们可以看看注释进行理解。
### 蜂鸣器模块 buzzzer.py 
```Python
#导入模块
import RPi.GPIO as GPIO
import time
#定义一个存放蜂鸣器引脚号的列表
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
```

### 蜂鸣器测试程序 buzzer_test.py 
```Python
#导入模块
import buzzer
var = 1;
#初始化led引脚
buzzer.buzzer_init();
#初始化后进入一个死循环执行流水灯，通过修改flow(time)，time参数来改变速度（单位秒）
while var == 1
    buzzer.beep(0.2,1);
```
## 4.玩
> 当我们修改了Python版本代码后想运行时，保存后即可运行<br>
> 执行验证
> `./python 程序名`
>例:`./buzzer_test.py`
>按了回车后，你将会听到蜂鸣器每隔一秒响一次<br>
