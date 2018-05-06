# MrzhangF1ghterStudio 彩虹RainbowHAT系列
# OLED教程 （BCM2835 C库版本）

## 玩转代码
> ### 在我们的彩虹扩展板上 OLED是挂在原生SPI0接口上的，具体引脚如下:
> |引脚|GPIO| wPi |排针号|
> |----|--- |-----|-----|
> |CS  |BCM8 |pin10| 16 |    
> |DC  |BCM24|pin5 | 18 |
> |RST |BCM25|pin6 | 20 |
> |SDA |BCM10|pin12| 22 |
> |SCLK|BCM11|pin14| 24 |

### 原理图如下:
[RainbowCandyBoard.pdf](https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/schematic/RainbowCandyBoard.pdf)<br>
<img src="https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/oled/schematic/oled.png" width=50% height=50%/><br>
<img src="https://github.com/MrzhangF1ghter/RainbowCandyBoard/blob/master/oled/schematic/oled_pin.png" width=50% height=50%/><br>
> 用户可自行更换OLED显示屏，为7pin spi接口的 0.96寸128x64分辨率。
> 由于代码庞大，只展现主文件，oled具体实现可自行阅读理解，也可以学习arduino、stm32相关教程，触类旁通。
首先先用gedit、pluma、vim等文本编辑工具打开该文件夹下的led.c,如下，我们可以看看注释进行理解。
```C
#include <bcm2835.h>
#include <stdio.h>
#include <time.h>
#include "SSD1306.h"

char value[10]={'0','1','2','3','4','5','6','7','8','9'};
int main(int argc,char **argv)
{
	time_t now;
	struct tm *timenow;
	if(!bcm2835_init())return 1;
	printf("OLED Test Program !!!\n");

	SSD1306_begin();
	SSD1306_bitmap(0,0,RainbowHat,128,64);
	SSD1306_display();
	bcm2835_delay(2000);
	SSD1306_clear();
	while(1)
	{
		time(&now);
		timenow = localtime(&now);
		SSD1306_char3216(0,16, value[timenow->tm_hour/10]);
		SSD1306_char3216(16,16, value[timenow->tm_hour%10]);
		SSD1306_char3216(32,16, ':');
		SSD1306_char3216(48,16, value[timenow->tm_min/10]);
		SSD1306_char3216(64,16, value[timenow->tm_min%10]);
		SSD1306_char3216(80,16, ':');
		SSD1306_char3216(96,16, value[timenow->tm_sec/10]);
		SD1306_char3216(112,16, value[timenow->tm_sec%10]);
		SSD1306_display();
    	}
	bcm2835_spi_end();
	bcm2835_close();
	return 0;
}

```
## 玩
> 当我们修改了代码后想运行时，必须将其编译成可执行文件，在此我们需要用到gcc工具，树莓派默认已安装好，若无，则百度相关教程安装好<br>
> 此版本提供了Makefile文件，Makefile文件描述了整个工程的编译、链接等规则，用户只需要运行make即可按照程序员所写好的规则编译程序。
> 此Makefile文件内容如下
```C
oled:oled.o SSD1306.o
	gcc -Wall -o oled oled.o SSD1306.o -lbcm2835
SSD1306.o:SSD1306.c SSD1306.h
	gcc -Wall -c SSD1306.c -lbcm2835
oled.o:oled.c SSD1306.h 
	gcc -Wall -c oled.c -lbcm2835
clean:
	rm SSD1306.o oled.o oled
```
> 执行`make`<br>
> 若无错误，则将会生成目标文件名的可执行文件，如有错误，请根据编译器提示排错。<br>
> 执行验证<br>
> `sudo ./oled`<br>
> 按了回车后，将会显示两秒钟彩虹板logo，然后显示当前时间<br>
> 按下`Ctrl+C`结束程序<br>
> 若想后台运行:<br>
> `sudo ./oled &`<br>
> 注意：由于BCM2835是操作底层寄存器，比较底层，若运行BCM2835版本后的例程再运行Python等其他版本,OLED屏将无响应，重启运行其他版本即可.<br>
