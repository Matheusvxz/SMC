#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringSerial.h>
#include <lcd.h>

#define LCD_RS  25               //Register select pin
#define LCD_E   24               //Enable Pin

#define LCD_D4  23               //Data pin D4
#define LCD_D5  22               //Data pin D5
#define LCD_D6  21               //Data pin D6
#define LCD_D7  14               //Data pin D7

int serial_port;
int char c;

int main() {

    wiringPiSetupGpio();


    if((serial_port = serialOpen("/dev/ttyAMAO", 9600)) < 0) {
        fprintf(stderr, "Unable to open serial device: %s\n", strerror(errno));
    }

    if(wiringPiSetup() == -1) {
        fprintf(stdout, "Unable to start WiringPi: %s\n", strerror(errno));
    }

    int lcd = lcdInit(2, 16, 4, LCD_RS, LCD_E,LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0 ,0);

    lcdClear(lcd);
    lcdPosition(lcd,0,0);
    lcdPuts(lcd,"POTENCIOMETRO");
    lcdPosition(lcd,0,1);
    lcdPuts(lcd,"Valor:");
    lcdPosition(lcd,6,1);
    lcdPutchar(lcd, '0');

    while(1) {
        
        if(serialDataAvail(serial_port) > 0) {
            int lenght = serialDataAvail(serial_port);

            for(int i = 0; i < lenght; i++) {
                c[i] = serialGetchar(serial_port);
            }

            serialFlush(serial_port);

            lcdPosition(lcd,6,1);

            lcdPuts(lcd, c);
        }
    }
    return 0;
}