#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <wiringPi.h>

#define PIN_OUT_LED         19  // GPIO19
#define PIN_INP_BTN         26  //GPIO26

#define DEBOUNCE_INT        200 //200ms
#define INTERVAL_ON         500 //500ms
#define INTERVAL_OFF        500 //500ms

// Variables

volatile bool pushed = false;
volatile unsigned long lastInterrupt = 0;

void configureIO(void);
void loop(void);

void btnInterrupt(void) {
    unsigned long currentInterrupt = millis();

    if((currentInterrupt - lastInterrupt) > DEBOUNCE_INT) {
        pushed = !pushed;
    }
    lastInterrupt = currentInterrupt;
}

int main(int argc, char const *argv[]) {
    wiringPiSetupGpio();
    configureIO();

    if(wiringPiISR(PIN_INP_BTN1, INT_EDGE_FALLING, &btnInterrupt) < 0) {
        fprintf(stderr, "Incapaz de configurar ISR: %s\n", strerror(errno));
        return 1;
    }

    while(true) {
        loop();
    }
    return 0;
}

void loop(void) {
    if(pushed) {
        digitalWrite(PIN_OUT_LED, HIGH);
        delay(INTERVAL_ON);
        digitalWrite(PIN_OUT_LED, LOW);
        delay(INTERVAL_OFF);
    } else {
        digitalWrite(PIN_OUT_LED, LOW);
        // delay(1000);
    }
}

void configureIO() {
    pinMode(PIN_OUT_LED, OUTPUT);
    pinMode(PIN_INP_BTN1, INPUT);
    pullUpDnControl(PIN_INP_BTN1, PUD_UP);
}