#include <Servo.h>

#define PIN_POT A0

int pos = 0;
Servo servo_9;

void setup () {
  servo_9.attach (9);
  pinMode(PIN_POT, INPUT);
}

void loop () {  
  int pos = analogRead(PIN_POT);
  pos = map(pos, 0, 1023, 0, 180);
  servo_9.write(pos);
}