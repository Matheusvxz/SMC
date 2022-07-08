#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringSerial.h>

int main() {
    int serial_port;
    char c;

    if((serial_port = serialOpen("/dev/ttyAMAO", 9600)) < 0) {
        fprintf(stderr, "Unable to open serial device: %s\n", strerror(errno));
    }

    if(wiringPiSetup() == -1) {
        fprintf(stdout, "Unable to start WiringPi: %s\n", strerror(errno));
    }

    while(1) {
        scanf("%c", &c);
        serialPutchar(serial_port, c);
    }
}