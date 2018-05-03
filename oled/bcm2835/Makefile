oled:oled.o SSD1306.o
	gcc -Wall -o oled oled.o SSD1306.o -lbcm2835
SSD1306.o:SSD1306.c SSD1306.h
	gcc -Wall -c SSD1306.c -lbcm2835
oled.o:oled.c SSD1306.h 
	gcc -Wall -c oled.c -lbcm2835
clean:
	rm SSD1306.o oled.o oled
