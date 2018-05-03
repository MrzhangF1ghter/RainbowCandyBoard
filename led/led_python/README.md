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
> ### 在我们的彩虹扩展板上 4盏LED分别对应着一下GPIO引脚
> 灯   | GPIO | wPi |排针号|
> |----|-----|-----|-----|
> |LED1|BCM17|pin0 | 11 |    
> |LED2|BCM27|pin2 |13  |
> |LED3|BCM22|pin3 |15  |
> |LED4|BCM5 |pin21|29  |

### 原理图如下:
[RainbowCandyBoard.pdf](https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/%E5%8E%9F%E7%90%86%E5%9B%BE/RainbowCandyBoard.pdf)
![image](https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/LED/%E5%8E%9F%E7%90%86%E5%9B%BE/switch.png)
> 我们采用的是跳帽来连接IO口，你可以在彩虹板上看到有一排彩虹色的跳帽，找到LED1、LED2、LED3、LED4，那就是与IO连接的端口，具体端口号请看原理图。
> 当我们想接自己io的时候，可以将跳帽拔开，那么板上的外设就和io口断开了，然后插上你想接的外设即可。

> Python版本中，我们将led看做一个模块，当我们要使用led的时候导入这个模块使用。`led.py`就是我们的模块，`led_test.py`就是我们的测试程序
首先先用gedit、puma、vim等文本编辑工具打开该文件夹下的`led.py`,如下，我们可以看看注释进行理解。
### led模块 led.py 
```Python
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
    if(i>=1&&i<=4)
        GPIO.output(leds_pin[i-1],GPIO.LOW);
#定义熄灭led的函数on(i),参数为led号，编号范围为1~4
def off(i):
    if(i>=1&&i<=4)
        GPIO.output(leds_pin[i-1],GPIO.HIGH);
#定义流水灯函数flow(time),time为流水速度，单位为秒
def flow(time):
    for i in leds_pin
        GPIO.output(leds_pin[i],GPIO.LOW);
        print('LED',i+1,'is on');
        time.sleep(time);
        GPIO.output(leds_pin[i],GPIO.HIGH);
        print('LED',i+1,'is off');
        time.sleep(time);
def clean():
    GPIO.cleanup();
```

### led测试程序 led_test.py 
```Python
#导入模块
import led
var = 1;
#初始化led引脚
led.led_init();
#初始化后进入一个死循环执行流水灯，通过修改flow(time)，time参数来改变速度（单位秒）
while var == 1
    led.flow(1);
```

## 4.玩
> 当我们修改了Python版本代码后想运行时，保存后即可运行<br>
> 执行验证
> `./python 程序名`
>例:`./led_test.py`
>按了回车后，你将会发现彩虹板上的LED随着你的要求而亮灭<br>
