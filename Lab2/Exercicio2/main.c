#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <wiringPi.h>

#define PIN_OUT_LED         19      // GPIO19
#define PIN_INP_BTN1        26      // GPIO26
#define PIN_INP_BTN2        21      // GPIO21

#define DEBOUNCE_INT        200     // 200ms
#define MAX_LED_INTERVAL    3000    // 3s
#define INTERVAL_INC        500     // 500ms

// Variables
volatile int ledInterval = 500;
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

void changeInterval(void) {
    unsigned long currentInterrupt = millis();

    if((currentInterrupt - lastInterrupt) > DEBOUNCE_INT) {
        ledInterval += INTERVAL_INC;

        if(ledInterval > MAX_LED_INTERVAL) {
            ledInterval = 500;
        }
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
    if(wiringPiISR(PIN_INP_BTN2, INT_EDGE_FALLING, &changeInterval) < 0) {
        fprintf(stderr, "Incapaz de configurar ISR: %s\n", strerror(errno));
        return 1;
    }

    while(1) {
        loop();
    }
    return 0;
}

void loop(void) {
    if(pushed) {
        digitalWrite(PIN_OUT_LED, HIGH);
        delay(ledInterval);
        digitalWrite(PIN_OUT_LED, LOW);
        delay(ledInterval);
    } else {
        digitalWrite(PIN_OUT_LED, LOW);
    }
}

void configureIO() {
    pinMode(PIN_OUT_LED, OUTPUT);

    // Button 1
    pinMode(PIN_INP_BTN1, INPUT);
    pullUpDnControl(PIN_INP_BTN1, PUD_UP);

    // Button 2
    pinMode(PIN_INP_BTN2, INPUT);
    pullUpDnControl(PIN_INP_BTN2, PUD_UP);
    
}