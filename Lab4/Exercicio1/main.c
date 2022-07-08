#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringSerial.h>
#include <lcd.h>

#define LCD_RS  26               //Register select pin
#define LCD_E   19              //Enable Pin

#define LCD_D4  13               //Data pin D4
#define LCD_D5  6               //Data pin D5
#define LCD_D6  5               //Data pin D6
#define LCD_D7  11               //Data pin D7

int serial_port;
char c;

int main() {

    wiringPiSetupGpio();


    if((serial_port = serialOpen("/dev/ttyAMA0", 9600)) < 0) {
        fprintf(stderr, "Unable to open serial device: %s\n", strerror(errno));
    }

    if(wiringPiSetup() == -1) {
        fprintf(stdout, "Unable to start WiringPi: %s\n", strerror(errno));
    }

    int lcd = lcdInit(2, 16, 4, LCD_RS, LCD_E,LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0 ,0);

    lcdClear(lcd);
    lcdPosition(lcd,0,0);
    lcdPuts(lcd,"SMC MUITO LEGAL");
    lcdPosition(lcd,0,1);
    lcdPuts(lcd,"Counter:");
    lcdPosition(lcd,9,1);
    lcdPutchar(lcd, '0');
    printf("Tem alguma coisa na serial");

    while(1) {
        if(serialDataAvail(serial_port) > 0) {
            printf("Tem alguma coisa na serial");
            c = serialGetchar(serial_port);
            printf("%c", c);
            lcdPosition(lcd,9,1);
            lcdPutchar(lcd, c);
            serialFlush(serial_port);
        }
    }
    return 0;
}