# MrzhangF1ghterStudio 彩虹RainbowHAT系列
# 蜂鸣器BUZZER教程 （shell版本）

## 玩转代码
> ### 在我们的彩虹扩展板上 4盏LED分别对应着一下GPIO引脚
> 蜂鸣器| GPIO | wPi |排针号|
> |----|-----|-----|-----|
> |BUZZER|BCM12|pin26 | 32 |    
### 原理图如下:
[RainbowCandyBoard.pdf](https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/schematic/RainbowCandyBoard.pdf)<br>
<img src="https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/buzzer/schematic/buzzer.png" width=50% height=50%/><br>
<img src="https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/buzzer/schematic/buzzer_pin.png" width=50% height=50%/><br>
> 我们采用的是跳帽来连接IO口，你可以在彩虹板上看到有一排彩虹色的跳帽，找到BUZZER，那就是蜂鸣器与IO连接的端口，具体端口号请看原理图。
> 蜂鸣器处于大电流外设，需要用三极管驱动，该驱动电路为高电平导通。
> 当我们想接自己io的时候，可以将跳帽拔开，那么板上的外设就和io口断开了，然后插上你想接的外设即可。

> 代码如下：
> ### buzzer脚本 buzzer.sh 
```C
#! /bin/bash
#sudo ./led.sh pin value
echo Exporting pin $1.
echo $1 > /sys/class/gpio/export
echo Setting direction to out.
#把传入的pin给了gpio
echo out > /sys/class/gpio/gpio$1/direction
#设置该gpio的值
echo Setting pin $2
echo $2 > /sys/class/gpio/gpio$1/value
```
## 玩
> 编辑完脚本后我们就可以运行测试了<br>
> 比如我们要蜂鸣器鸣叫（对应BCM引脚12），高电平响
> `./buzzer.sh 12 0`
> 若无法执行，提示command not found，请修改buzzer.sh权限为可执行文件,如下:
> `chmod 777 buzzer.sh`
