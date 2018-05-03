oled:oled.o SSD1306.o
	gcc -Wall -o oled oled.o SSD1306.o -lwiringPi
SSD1306.o:SSD1306.c SSD1306.h
	gcc -Wall -c SSD1306.c -lwiringPi
oled.o:oled.c SSD1306.h 
	gcc -Wall -c oled.c -lwiringPi
clean:
	rm SSD1306.o oled.o oled
