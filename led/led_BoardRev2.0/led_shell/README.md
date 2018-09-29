# MrzhangF1ghterStudio 彩虹RainbowHAT系列
# LED教程 （shell版本）

## 玩转代码
> ### 在我们的彩虹扩展板上 4盏LED分别对应着一下GPIO引脚
> 灯   | GPIO | wPi |排针号|
> |----|-----|-----|-----|
> |LED1|BCM17|pin0 | 11 |    
> |LED2|BCM27|pin2 |13  |
> |LED3|BCM22|pin3 |15  |
> |LED4|BCM5 |pin21|29  |

### 原理图如下:
[RainbowCandyBoard.pdf](https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/schematic/RainbowCandyBoard_Rev2.0.pdf)<br>
<img src="https://img.alicdn.com/imgextra/i4/1887229091/O1CN012H1j62Ne2JJwKdi_!!1887229091.png" width=50% height=50%/><br>
<img src="https://img.alicdn.com/imgextra/i2/1887229091/O1CN012H1j61VWcYfRF8n_!!1887229091.png" width=50% height=50%/><br>
> 我们采用的是跳帽来连接IO口，你可以在彩虹板上看到有一排彩虹色的跳帽，找到LED1、LED2、LED3、LED4，那就是与IO连接的端口，具体端口号请看原理图。
> 当我们想接自己io的时候，可以将跳帽拔开，那么板上的外设就和io口断开了，然后插上你想接的外设即可。
> shell版本中，我们采用脚本进行点亮led操作，对于不熟悉shell的用户，可自行了解相关内容
> 代码如下：
> ### led脚本 led.sh
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
> 比如我们要点亮LED1（对应BCM引脚17），低电平点亮
> `./led.sh 17 0`
> 若无法执行，提示command not found，请修改led.sh权限为可执行文件,如下:
> `chmod 777 led.sh`
