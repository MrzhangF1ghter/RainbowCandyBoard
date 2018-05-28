/********************************************************************************* 
  *Copyright(C),MrzhangF1ghter studio
  *FileName:rgb.c
  *Author:MrzhangF1ghter 
  *Version:1.0 
  *Date:2018/5/5 
  *Description:树莓派彩虹IO扩展板RGB代码 wiringPi 多线程方法实现。
  *Others:Learn more from：https://github.com/MrzhangF1ghter/RainbowCandyBoard
  												 http://www.airspayce.com/mikem/bcm2835/group__gpio.html
  *Function List:
  *History:
  *compile:gcc -o key_event key_event.c -lbcm2835
**********************************************************************************/ 
#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>

#define uchar unsigned char

#define LedPinRed    28
#define LedPinGreen  27
#define LedPinBlue   29

void ledInit(void)
{
	softPwmCreate(LedPinRed,  0, 100);
	softPwmCreate(LedPinGreen,0, 100);
	softPwmCreate(LedPinBlue, 0, 100);
}

void ledColorSet(uchar r_val, uchar g_val, uchar b_val)
{
	softPwmWrite(LedPinRed,   r_val);
	softPwmWrite(LedPinGreen, g_val);
	softPwmWrite(LedPinBlue,  b_val);
}

int main(void)
{
	int i;

	if(wiringPiSetup() == -1){      //when initialize wiring failed,print message to screen
		printf("setup wiringPi failed !");
		return 1; 
	}

	ledInit();

	while(1){
		ledColorSet(0xff,0x00,0x00);   //red	
		delay(500);
		ledColorSet(0x00,0xff,0x00);   //green
		delay(500);
		ledColorSet(0x00,0x00,0xff);   //blue
		delay(500);

		ledColorSet(0xff,0xff,0x00);   //yellow
		delay(500);
		ledColorSet(0xff,0x00,0xff);   //pick
		delay(500);
		ledColorSet(0xc0,0xff,0x3e);
		delay(500);

		ledColorSet(0x94,0x00,0xd3);
		delay(500);
		ledColorSet(0x76,0xee,0x00);
		delay(500);
		ledColorSet(0x00,0xc5,0xcd);	
		delay(500);

	}

	return 0;
}
