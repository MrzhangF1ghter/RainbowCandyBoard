# -- coding: utf-8 --
#导入模块
import led

var = 1;
#初始化led引脚
led.led_init();
#初始化后进入一个死循环执行流水灯，通过修改flow(time)，time参数来改变速度（单位秒）
while var == 1:
	led.flow(0.5);
led.clean();
  
