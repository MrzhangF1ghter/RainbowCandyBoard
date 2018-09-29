# MrzhangF1ghterStudio 彩虹RainbowHAT系列
# 1-Wire DS18B20温度传感器教程

> ### 在我们的彩虹扩展板上 ds18b20接在1-wire接口上，请注意不要接反，圆边向外!
> 1-Wire| GPIO | wPi |排针号|
> |----|-----|-----|-----|
> |DS18B20|BCM4|pin7| 4  |    
### 原理图如下:
[RainbowCandyBoard.pdf](https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/schematic/RainbowCandyBoard_Rev2.0.pdf)<br>
<img src="https://img.alicdn.com/imgextra/i2/1887229091/O1CN012H1j61lkVzAaTxe_!!1887229091.png" width=50% height=50%/><br>
<img src="https://img.alicdn.com/imgextra/i2/1887229091/O1CN012H1j5zNKVW8O3TU_!!1887229091.png" width=50% height=50%/><br>
# 准备工作

### 修改配置文件:
> root权限打开树莓派配置文件<br>
> `sudo vi /boot/config.txt`<br>
> 在文件末尾加入：`dtoverlay=w1-gpio-pull`<br>
<img src="https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/ds18b20/schematic/config.png" width=50% height=50%/><br>
> 保存退出重启<br>
> `sudo reboot`<br>
### 检查模块是否加载
> `lsmod`找到w1_therm、w1_gpio代表加载成功<br>
> <img src="https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/ds18b20/schematic/lsmod.png" width=50% height=50%/><br>
> 若无或二缺一，请手动加载模块:
> `sudo modprobe w1_gpio`<br>
> `sudo modprobe w1_therm`<br>
> 如果没有问题，将会在/sys/bus/w1/devices/中发现28-xxxx开头的文件夹，此为DS18B20的ROM，通过读取里面的w1-slave文件则返回当前温度值，如图:<br>
> <img src="https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/ds18b20/schematic/cat.png" width=50% height=50%/><br>
> 返回数据中 第一行的YES表示CRC校验成功 数据有效，第二行的t=xxxx则为当前温度<br>
### 代码 请打开先关文件夹查看教程和代码
