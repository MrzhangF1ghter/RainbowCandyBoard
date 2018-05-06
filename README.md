# MrzhangF1ghterStudio 彩虹RainbowHAT系列
### 此仓库为彩虹系列扩展板源码与教程
<img src="https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/pic/function.jpg" width=50% height=50% /><br>
### 教程使用方法：
### 新手引导:
> https://github.com/MrzhangF1ghter/RainbowCandyBoard/wiki
### 代码以及教程：
> 请浏览外设对应名称的文件夹及版本，里面包含源码和教程文件，教程为.md后缀，也就是Markdown格式。<br>
### 源码文件结构
```
.
├── buzzer
│   ├── buzzer_bcm2835
│   ├── buzzer_fs
│   ├── buzzer_python
│   ├── buzzer_shell
│   ├── buzzer_wriringPi
│   └── schematic
├── ds18b20
│   ├── fs
│   ├── python
│   └── schematic
├── key
│   ├── key_bcm2835
│   ├── key_python
│   ├── key_wriringPi
│   └── schematic
├── led
│   ├── led_bcm2835
│   ├── led_fs
│   ├── led_python
│   ├── led_shell
│   ├── led_wiringPi
│   └── schematic
├── LICENSE
├── oled
│   ├── bcm2835
│   ├── python
│   ├── schematic
│   └── wiringPi
├── pic
│   ├── function.jpg
│   ├── getcode.png
│   ├── getupdate.png
│   └── gpio.png
├── README.md
├── rgb
│   ├── rgb
│   ├── rgb.c
│   └── schematic
└── schematic
    └── RainbowCandyBoard.pdf
```
### 该仓库包含了以下外设的代码：
|外设|wiringPi|Python|BCM2835 C|sysfs|Kernel|
| ----|-----|-----|-----|-----|-----|
|LED灯|yes|yes|yes|yes|wait|
|蜂鸣器|yes|yes|yes|yes|wait|
|按键|yes|yes|yes|yes|wait|
|RGB灯|yes|no|no|no|no|
|ds18b20|yes|yes|no|yes|no|
|OLED|yes|yes|yes|no|no|
#### wait代表暂未更新 但后期将会更新。请密切关注
