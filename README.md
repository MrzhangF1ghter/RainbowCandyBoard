# MrzhangF1ghterStudio 彩虹RainbowCandyHAT系列
### 此仓库为彩虹系列扩展板源码与教程
## 新版本加入了：
1. 双红外发送
2. 红外接收
3. 温控风扇（独家设计风道,PWM调速）
## 新版本修改了：
1. 串口芯片更改为CH340C
2. 更为牢固的MicroUSB接口
3. 大部分采用smt工艺

# <img src="https://img.alicdn.com/imgextra/i4/1887229091/O1CN012H1j5qj9inQPsWT_!!1887229091.jpg" /><br>
# <img src="https://img.alicdn.com/imgextra/i4/1887229091/TB2MaoWb3HqK1RjSZFPXXcwapXa_!!1887229091.jpg"/><br>
# <img src="https://img.alicdn.com/imgextra/i2/1887229091/TB2e20kcmzqK1RjSZFjXXblCFXa_!!1887229091.jpg" /><br>

### 教程使用方法：
### 新手引导:
> https://github.com/MrzhangF1ghter/RainbowCandyBoard/wiki
### 代码以及教程：
> 请浏览外设对应名称的文件夹及版本，里面包含源码和教程文件，教程为.md后缀，也就是Markdown格式。<br>
### 源码文件结构
```
.
RainbowCandyBoard/
|-- buzzer
|   |-- buzzer_bcm2835
|   |-- buzzer_fs
|   |-- buzzer_python
|   |-- buzzer_shell
|   `-- buzzer_wiringPi
|-- ds18b20
|   |-- python
|   |-- README.md
|   `-- sysfs
|-- fan
|   |-- fan_wiringPi
|   `-- README.md
|-- ir
|   `-- README.md
|-- key
|   |-- key_bcm2835
|   |-- key_python
|   `-- key_wiringPi
|-- led
|   |-- led_BoardRev1.0
|   `-- led_BoardRev2.0
|-- LICENSE
|-- oled
|   |-- bcm2835
|   |-- python
|   |-- readme
|   `-- wiringPi
|-- README.md
|-- rgb
|   |-- README.md
|   |-- rgb
|   `-- rgb.c
|-- schematic
|   |-- RainbowCandyBoard_Rev1.0.pdf
|   `-- RainbowCandyBoard_Rev2.0.pdf
`-- uart
    |-- RaspberryPi2
    |-- RaspberryPi3
    `-- Readme.md
```
### 该仓库包含了以下外设的代码：
|外设|wiringPi|Python|BCM2835 C|sysfs|Kernel|
| ----|-----|-----|-----|-----|-----|
|LED灯|yes|yes|yes|yes|wait|
|蜂鸣器|yes|yes|yes|yes|wait|
|按键|yes|yes|yes|yes|wait|
|RGB灯|yes|no|no|no|no|
|温控风扇|yes|wait|wait|wait|no|
|ds18b20|yes|yes|no|yes|no|
|OLED|yes|yes|yes|no|no|
|红外接收|lirc|
|红外发送|lirc|

#### wait代表暂未更新 但后期将会更新。请密切关注
