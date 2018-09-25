# MrzhangF1ghterStudio 彩虹扩展板RainbowCandyBoard系列
# 红外收发教程
##功能说明
1.  红外线接收功能
工作频率：38K HZ
接收距离：18-20m
接收角度：+/-45度
2.  红外线发射功能
    双管发射，多方位覆盖
波长：940nm
发射距离：7-8m *2
## 玩转模块
> ### 在我们的彩虹扩展板上 共有两个红外发射管，分别向不同方向发射，一个红外接收管，用来接收红外信号。硬件连接如下：
> 红外收发| GPIO | wPi |排针号|
> |----|-----|-----|-----|
> |红外发射管|BCM17|pin0|11|
> |红外接收管|BCM7|pin11|26|

### 原理图如下:
[RainbowCandyBoard.pdf](https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/schematic/RainbowCandyBoardRev2.0.pdf)<br>
<div align=center>
  <img src="https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/ir/schematic/ir.png" width=50% height=50%/>
</div>

 ### 硬件实物图如下：
<div align=center>
  <img src="https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/ir/schematic/IRPic.jpg" width=50% height=50%/>
</div>
<div align=center>
  <img src="https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/ir/schematic/IRJumper.jpg" width=50% height=50%/>
</div>

> 我们采用的是跳帽来连接红外收发口，你可以在彩虹板的右下角看到有两个跳帽，分别写着IR_TX,IR_RX,那红外收发管与IO连接的端口，拔掉即断开与红外收发口的连接。<br>
> 当我们想接自己io的时候，可以将跳帽拔开，那么板上的外设就和io口断开了，然后插上你想接的外设即可。<br>

## 配置
在Linux下，我们采用LIRC (Linux Infrared remote control)这个开源的软件包，该软件包能让Linux接收及发送红外信号，下面讲解如何使用
### 1.安装
> `apt-get install lirc`
### 2.配置Config.txt
> 网上的大多数教程已经过时，在0.9.4c版本中，我们只需要配置该文件即可
> 编辑`/boot/config.txt`,加入下列代码,功能是声明引脚，在扩展板中 发射管对应的是GPIO17，接收管对应的是GPIO7<br>
> `dtoverlay=lirc-rpi,gpio_out_pin=17,gpio_in_pin=7,gpio_in_pull=up`
### 3.修改默认驱动
> 编辑`/etc/lirc/lirc_options.conf`
```
driver  = devinput
device  = auto
```
修改为:<br>
```
driver  = default
device  = /dev/lirc0
```
### 4.重启树莓派，并检查lircd是否正常运行,若无误，运行结果如图
#### lircd status
```
/etc/init.d/lircd status
[ ok ] lircd is running.
```
#### lsmod
```
lsmod | grep lirc
lirc_rpi                9032  0
lirc_dev               10583  1 lirc_rpi
rc_core                24377  1 lirc_dev
```
## 测试
> 首先我们测试红外接收功能,这个能直观的判断红外接收管是否正常工作。<br>
> 停止LIRC:`sudo /etc/init.d/lircd stop`
> 执行命令`mode2 -d /dev/lirc0`
> 使用任意一个红外遥控器，对着扩展板的红外接收头按下任意按键，若每次按下按键都有打印类似以下的内容，则说明红外接收功能正常<br>
```

```
## 玩
> 当我们修改了代码后想运行时，必须将其编译成可执行文件，在此我们需要用到gcc工具，树莓派默认已安装好，若无，则百度相关教程安装好<br>
> 编译指令如下 `gcc -o 目标文件名 源文件名` -o的意思为输出可执行文件<br>
> 例:`gcc -o myled led_wiringPi.c -lwiringPi` <br>
> 若无错误，则将会生成目标文件名的可执行文件，如有错误，请根据编译器提示排错。<br>
> 执行验证
> `./目标文件名`
> 例<br>
> `./led`
> 按了回车后，你将会发现彩虹板上的LED以流水的形式闪烁<br>
> 按下`Ctrl+C`结束程序<br>
## 扩展
