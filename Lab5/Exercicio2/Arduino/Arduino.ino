#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define PIN_POT A0

int pos = 0;
float posDisplay = 0.0;
char buffer[20];
char floatNum[5];

Servo servo_9;

LiquidCrystal_I2C lcd(0x20,20,4);

float mapFloat(float analog, float fromMin, float fromMax, float toMin, float toMax);

void setup () {
  servo_9.attach (9);
  pinMode(PIN_POT, INPUT);
  
  lcd.init();
  
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("CONTROLE SERVO");
}

void loop () {  
  pos = analogRead(PIN_POT);
  posDisplay = mapFloat(pos, 0, 1023, -90, 90);
  pos = map(pos, 0, 1023, 0, 180);
  servo_9.write(pos);
  
  dtostrf(posDisplay, 2, 1, floatNum);
  sprintf(buffer, "POS: %s%c       ", floatNum, 0xB0);
  lcd.setCursor(0,1);
  lcd.print(buffer);
}

float mapFloat(float analog, float fromMin, float fromMax, float toMin, float toMax) {
  return ((float)analog - (float)fromMin) * ((float)toMax - (float)toMin) / ((float)fromMax - (float)fromMin) + (float)toMin;
}