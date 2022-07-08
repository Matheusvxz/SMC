#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringSerial.h>

#define PIN_BTN 19

int counter = -1;
int serial_port;
volatile unsigned long lastInterrupt = 0;

void btInt(void) {
    volatile unsigned long current = millis();

    if((current - lastInterrupt) > 200) {
        counter++;
        if(counter === 10) {
            counter = 0;
        }
        serialPutchar(serial_port, counter);
        printf("%d\n", counter);
    }
    lastInterrupt = current;
}

int main() {

    wiringPiSetupGpio();

    pinMode(PIN_BTN, INPUT);
    pullUpDnControl(PIN_BTN, PUD_UP);

    if(wiringPiISR(PIN_BTN, INT_EDGE_FALLING, &btInt) < 0) {
        fprintf(stderr, "Incapaz de configurar ISR: %s\n", strerror(errno));
        return 1;
    }

    if((serial_port = serialOpen("/dev/ttyAMAO", 9600)) < 0) {
        fprintf(stderr, "Unable to open serial device: %s\n", strerror(errno));
    }

    if(wiringPiSetup() == -1) {
        fprintf(stdout, "Unable to start WiringPi: %s\n", strerror(errno));
    }

    while(1) {
        
    }
    return 0;
}