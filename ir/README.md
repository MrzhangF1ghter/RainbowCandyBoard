# MrzhangF1ghterStudio 彩虹扩展板RainbowCandyBoard系列
# 红外收发教程
## 功能说明
#### 红外线接收功能
- 工作频率：38K HZ
- 接收距离：18-20m
- 接收角度：+/-45度
#### 红外线发射功能
- 双管发射，多方位覆盖
- 波长：940nm
- 发射距离：7-8m *2    

## 玩转模块
  通过红外收发模块，我们可以轻松实现树莓派控制家电等等功能。  
  在我们的彩虹扩展板上 共有两个红外发射管，分别向不同方向发射，一个红外接收管，用来接收红外信号。硬件连接如下：    

  红外收发| GPIO | wPi |排针号|
  |----|-----|-----|-----|
  |红外发射管|BCM17|pin0|11|
  |红外接收管|BCM7|pin11|26|

#### 原理图如下:
[RainbowCandyBoard.pdf](https://github.com/MrzhangF1ghter/RainbowCandyBoard/tree/master/schematic/RainbowCandyBoardRev2.0.pdf)  
<div align=center>
  <img src="https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/ir/schematic/ir.png" width=50% height=50%/>
</div>  

#### 硬件实物图如下：
<div align=center>
  <img src="https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/ir/schematic/IRPic.jpg" width=50% height=50%/>
</div>  
<div align=center>
  <img src="https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/ir/schematic/IRJumper.jpg" width=50% height=50%/>
</div>

    我们采用的是跳帽来连接红外收发口，你可以在彩虹板的右下角看到有两个跳帽，分别写着IR_TX,IR_RX,
    那红外收发管与IO连接的端口，拔掉即断开与红外收发口的连接。
    当我们想接自己io的时候，可以将跳帽拔开，那么板上的外设就和io口断开了，然后插上你想接的外设即可。  
### 配置
在Linux下，我们采用LIRC (Linux Infrared remote control)这个开源的软件包，该软件包能让Linux接收及发送红外信号，下面讲解如何使用   
#### 1.安装
    `apt-get install lirc`
#### 2.配置Config.txt
    网上的大多数教程已经过时，在0.9.4c版本中，我们只需要配置该文件即可   
    编辑`/boot/config.txt`,加入下列代码,功能是声明引脚，在扩展板中 发射管对应的是GPIO17，接收管对应的是GPIO7     
    `dtoverlay=lirc-rpi,gpio_out_pin=17,gpio_in_pin=7,gpio_in_pull=up`
#### 3.修改默认驱动
    编辑`/etc/lirc/lirc_options.conf`
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
> 首先我们测试红外接收功能,这个能直观的判断红外接收管是否正常工作。  
> 停止LIRC:`sudo /etc/init.d/lircd stop`
> 执行命令`mode2 -d /dev/lirc0`
> 使用任意一个红外遥控器，对着扩展板的红外接收头按下任意按键，若每次按下按键都有打印类似以下的内容，则说明红外接收功能正常  
```
space 1638
pulse 644
space 535
pulse 644
space 1632
```
## 录制红外数据
首选停止LIRC:`sudo /etc/init.d/lircd stop`  
然后执行命令`irrecord –list-namespace`查询可用的按键名称，之后我们就用这些名称来录制自己的内容(请注意 list前面是两个-)  
执行红外录制指令`irrecord -d /dev/lirc0 ~/remote1.conf ` 我们这里的遥控器名称为remote1（这个自定义）  
1.输入上面的指令后我们会看到提示按下回车继续，那我们按下回车  
<div align=center><img src="https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/ir/schematic/1.png" width=50% height=50%/></div>    
2.按下之后会提示先不要看下任何按键，因为这个步骤是检查环境光是否有红外干扰，当检查完毕后，会提示输入我们遥控器文件的名称，这里以remote1为例    
<div align=center><img src="https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/ir/schematic/2.png" width=50% height=50%/></div>   
3.按下回车后，我们任意按下遥控器上的按键，注意这时每次按下的时间大概在1秒左右，然后松开然后继续按其他按键，同一个按键不能按超过十个点，每按下一次都会打印一个点出来，直到两行点填满以后，将会进入验证阶段    
<div align=center><img src="https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/ir/schematic/3.png" width=50% height=50%/></div>  
4.此时重复以上步骤直到验证成功（点数不一定确定）  
<div align=center><img src="https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/ir/schematic/4.png" width=50% height=50%/></div>  
5.上面操作完成后，正式进入录制按键阶段，程序提示我们输入按键名称（这个名称要在前面所列明的名字中选），我们输入btn_1,然后按下按键，注意，此时的按键不要长按，按下松开即可，录制成功后会提示录制下一个按键，直到你想要录制的按键全部录完为止，录完后按回车，然后提示验证bit mask，按下按键即可  
<div align=center><img src="https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/ir/schematic/5.png" width=50% height=50%/></div>  

    验证成功后，我们的录制就完成了  
<div align=center><img src="https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/ir/schematic/6.png" width=50% height=50%/></div>  

    将我们录制好的配置文件拷贝到`sudo cp ./remote1.lircd.conf /etc/lirc/lircd.conf.d`中即可  
    
    我们可以通过执行`irsend list remote1 ""`来查询我们刚才录制的红外信号内容。 remote1是我们刚才所设定的文件名称， ""代表全部显示  
    
    接下来我们就可以发送了，比如我们发送按键1 则输入`irsend SEND_ONCE remote1 btn_1`即可  
    
### 注意，不同遥控器有不同的编码方式，有些并不支持上面的录制方法 而是要用raw格式来录制，详情请查阅百度
