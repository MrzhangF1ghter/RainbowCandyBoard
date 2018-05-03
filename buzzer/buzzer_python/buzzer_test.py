#导入模块
import buzzer

var = 1;
#初始化led引脚
buzzer.buzzer_init();
#初始化后进入一个死循环执行流水灯，通过修改flow(time)，time参数来改变速度（单位秒）
while var == 1
    buzzer.beep(0.2,1);
  
