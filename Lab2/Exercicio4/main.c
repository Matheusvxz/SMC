#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <wiringPi.h>
#include <string.h>
#include <stdlib.h>

#define PIN_OUT_LED_1       19      // GPIO19
#define PIN_OUT_LED_2       13      // GPIO13
#define PIN_OUT_LED_3       6       // GPIO6
#define PIN_OUT_LED_4       5       // GPIO5
#define PIN_INP_BTN         26      // GPIO26

#define DEBOUNCE_INT        200     // 200ms


// Variables

volatile int counter = 0;
volatile unsigned long lastInterrupt = 0;

void configureIO(void);
void loop(void);

void btnInterrupt(void) {
    unsigned long currentInterrupt = millis();

    if((currentInterrupt - lastInterrupt) > DEBOUNCE_INT) {
        counter += 1;
        if(counter == 5) {
            counter = 0;
        }

        switch (counter) {
            case 0:
                digitalWrite(PIN_OUT_LED_1, LOW);
                digitalWrite(PIN_OUT_LED_2, LOW);
                digitalWrite(PIN_OUT_LED_3, LOW);
                digitalWrite(PIN_OUT_LED_4, LOW);
                break;
            case 1:     // Light up LED 1
                digitalWrite(PIN_OUT_LED_1, HIGH);
                break;
            case 2:     // Light up LED 2
                digitalWrite(PIN_OUT_LED_2, HIGH);
                break;
            case 3:     // Light up LED 3
                digitalWrite(PIN_OUT_LED_3, HIGH);
                break;
            case 4:     // Light up LED 4
                digitalWrite(PIN_OUT_LED_4, HIGH);
                break;
        }

    }
    lastInterrupt = currentInterrupt;
}

int main(int argc, char const *argv[]) {
    wiringPiSetupGpio();
    configureIO();

    if(wiringPiISR(PIN_INP_BTN, INT_EDGE_FALLING, &btnInterrupt) < 0) {
        fprintf(stderr, "Incapaz de configurar ISR: %s\n", strerror(errno));
        return 1;
    }

    while(1) {
        loop();
    }
    return 0;
}

void loop(void) {

}

void configureIO() {

    // Led 1
    pinMode(PIN_OUT_LED_1, OUTPUT);
    
    // Led 2
    pinMode(PIN_OUT_LED_2, OUTPUT);
    
    // Led 3
    pinMode(PIN_OUT_LED_3, OUTPUT);
    
    // Led 4
    pinMode(PIN_OUT_LED_4, OUTPUT);

    // Button
    pinMode(PIN_INP_BTN, INPUT);
    pullUpDnControl(PIN_INP_BTN, PUD_UP);
    
}
