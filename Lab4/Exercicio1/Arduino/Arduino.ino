
#define PIN_BTN 2
#define BOUNCE 200

volatile unsigned long lastInterruption = 0;
const int pins[] = {3,4,5,6,7,8,9};
int counter = -1;

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_BTN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_BTN), buttonPressed, FALLING);

  for(int i = 0; i < 7; i++) {
    pinMode(pins[i], OUTPUT);
  }
  
  Serial.begin(9600);
  delay(2000);
  Serial.println("Sistema iniciado");
}

void loop() {
  // put your main cod  e here, to run repeatedly:
}

void buttonPressed() {
  volatile unsigned long current = millis();

  if((current - lastInterruption) > BOUNCE) {
    counter++;
    if(counter > 9) {
      counter = 0;
    }

    show7Seg(counter);
    Serial.print(counter);
    
  }
  lastInterruption = current;
  
}


void show7Seg(int num) {
//    Serial.println(num);
    switch (num)
    {
    case 0:
        digitalWrite(pins[0], HIGH);
        digitalWrite(pins[1], HIGH);
        digitalWrite(pins[2], HIGH);
        digitalWrite(pins[3], HIGH);
        digitalWrite(pins[4], HIGH);
        digitalWrite(pins[5], HIGH);
        digitalWrite(pins[6], LOW);
        break;
    case 1:
        digitalWrite(pins[0], LOW);
        digitalWrite(pins[1], HIGH);
        digitalWrite(pins[2], HIGH);
        digitalWrite(pins[3], LOW);
        digitalWrite(pins[4], LOW);
        digitalWrite(pins[5], LOW);
        digitalWrite(pins[6], LOW);
        break;
    case 2:
        digitalWrite(pins[0], HIGH);
        digitalWrite(pins[1], HIGH);
        digitalWrite(pins[2], LOW);
        digitalWrite(pins[3], HIGH);
        digitalWrite(pins[4], HIGH);
        digitalWrite(pins[5], LOW);
        digitalWrite(pins[6], HIGH);
        break;
    case 3:
        digitalWrite(pins[0], HIGH);    // a
        digitalWrite(pins[1], HIGH);    // b
        digitalWrite(pins[2], HIGH);    // c
        digitalWrite(pins[3], HIGH);    // d
        digitalWrite(pins[4], LOW);    // e
        digitalWrite(pins[5], LOW);     // f
        digitalWrite(pins[6], HIGH);    // g
        break;
    case 4:
        digitalWrite(pins[0], LOW);    // a
        digitalWrite(pins[1], HIGH);    // b
        digitalWrite(pins[2], HIGH);    // c
        digitalWrite(pins[3], LOW);    // d
        digitalWrite(pins[4], LOW);    // e
        digitalWrite(pins[5], HIGH);     // f
        digitalWrite(pins[6], HIGH);    // g
        break;
    case 5:
        digitalWrite(pins[0], HIGH);    // a
        digitalWrite(pins[1], LOW);    // b
        digitalWrite(pins[2], HIGH);    // c
        digitalWrite(pins[3], HIGH);    // d
        digitalWrite(pins[4], LOW);    // e
        digitalWrite(pins[5], HIGH);     // f
        digitalWrite(pins[6], HIGH);    // g
        break;
    case 6:
        digitalWrite(pins[0], HIGH);    // a
        digitalWrite(pins[1], LOW);     // b
        digitalWrite(pins[2], HIGH);    // c
        digitalWrite(pins[3], HIGH);    // d
        digitalWrite(pins[4], HIGH);    // e
        digitalWrite(pins[5], HIGH);    // f
        digitalWrite(pins[6], HIGH);    // g
        break;
    case 7:
        digitalWrite(pins[0], HIGH);    // a
        digitalWrite(pins[1], HIGH);    // b
        digitalWrite(pins[2], HIGH);    // c
        digitalWrite(pins[3], LOW);     // d
        digitalWrite(pins[4], LOW);     // e
        digitalWrite(pins[5], LOW);     // f
        digitalWrite(pins[6], LOW);     // g
        break;
    case 8:
        digitalWrite(pins[0], HIGH);    // a
        digitalWrite(pins[1], HIGH);    // b
        digitalWrite(pins[2], HIGH);    // c
        digitalWrite(pins[3], HIGH);    // d
        digitalWrite(pins[4], HIGH);    // e
        digitalWrite(pins[5], HIGH);    // f
        digitalWrite(pins[6], HIGH);    // g
        break;
    case 9:
        digitalWrite(pins[0], HIGH);    // a
        digitalWrite(pins[1], HIGH);    // b
        digitalWrite(pins[2], HIGH);    // c
        digitalWrite(pins[3], HIGH);    // d
        digitalWrite(pins[4], LOW);     // e
        digitalWrite(pins[5], HIGH);    // f
        digitalWrite(pins[6], HIGH);    // g
        break;
    default:
        digitalWrite(pins[0], LOW);     // a
        digitalWrite(pins[1], LOW);     // b
        digitalWrite(pins[2], LOW);     // c
        digitalWrite(pins[3], LOW);     // d
        digitalWrite(pins[4], LOW);     // e
        digitalWrite(pins[5], LOW);     // f
        digitalWrite(pins[6], LOW);     // g
        break;
    }
}
