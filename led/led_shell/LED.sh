#! /bin/bash
#sudo ./LED.sh pin value
echo Exporting pin $1.
echo $1 > /sys/class/gpio/export
echo Setting direction to out.
echo out > /sys/class/gpio/gpio$1/direction
echo Setting pin $2
echo $2 > /sys/class/gpio/gpio$1/value

