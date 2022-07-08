const int OUTPUT_LED = 13;
int inBuffer;

// Pins of 7 segments display [A, B, C, D, E, F, G]
const int pins[] = {2,3,4,5,6,7,8};

void setup () {
    pinMode(OUTPUT_LED , OUTPUT);
    Serial.begin(9600) ;
}

void loop () {

    // put your main code here , to run repeatedly :
    if (Serial.available ()) {
        inBuffer = Serial.read();
        
        show7Seg(inBuffer);
    }

}

void show7Seg(int num) {
    Serial.println(num);
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
