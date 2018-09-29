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

