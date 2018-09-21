# MrzhangF1ghterStudio 彩虹扩展板RainbowCandyBoard系列
# 红外收发教程
## 玩转代码
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
> 我们采用的是跳帽来连接红外收发口，你可以在彩虹板的右下角看到有两个跳帽，分别写着IR_TX,IR_RX,那红外收发管与IO连接的端口，拔掉即断开与红外收发口的连接。<br>
  <div align=center>
<img src="https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/ir/schematic/IRJumper.jpg" width=50% height=50%/>
  </div>
> 当我们想接自己io的时候，可以将跳帽拔开，那么板上的外设就和io口断开了，然后插上你想接的外设即可。
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
> 用户可以扩展使用自己的的LED进行亮灭，只需把对应跳帽拔掉，接上排线即可。请注意使用同一个电源（共地）
> <img src="https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/led_BoardRev2.0/schematic/led_jumper.png" width=50% height=50%/><br>
