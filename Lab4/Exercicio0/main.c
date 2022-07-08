#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringSerial.h>
#include <lcd.h>

#define LCD_RS  17               //Register select pin
#define LCD_E   5               //Enable Pin

#define LCD_D4  6               //Data pin D4
#define LCD_D5  13               //Data pin D5
#define LCD_D6  19               //Data pin D6
#define LCD_D7  26               //Data pin D7

int main() {

    if(wiringPiSetup() == -1) {
        fprintf(stdout, "Unable to start WiringPi: %s\n", strerror(errno));
    }

    int lcd = lcdInit(2, 16, 4, LCD_RS, LCD_E,LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0 ,0);

    lcdClear(lcd);
    lcdPosition(lcd,  0,0);
    lcdPuts(lcd,"TESTANDO LCD");
    lcdPosition(lcd,0,1);
    lcdPuts(lcd,"dale dale dale");
    lcdPosition(lcd,9,1);
    lcdPutchar(lcd, '0');
    
    return 0;
}