#include <stdio.h>
#include <string.h>
#include <errno .h>

#include <wiringPi.h>
#include <wiringSerial.h>

int main () {
    int serial_port;
    int counter = 0;

    if ((serial_port = serialOpen ("/ dev / ttyAMA0 ", 9600) ) < 0) {
        fprintf(stderr , " Unable to open serial device : %s\n", strerror(errno));
        return 1;
    }

    if (wiringPiSetup () == -1) {
        fprintf (stdout, " Unable to start WiringPi : %s", strerror(errno ));
        return 1;
    }

    while (counter < 11) {
        serialPutchar ( serial_port , counter );
        delay (5000) ;
        counter ++;
    }
    return 0; 
}
