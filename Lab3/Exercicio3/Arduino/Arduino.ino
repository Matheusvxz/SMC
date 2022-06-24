const int OUTPUT_LED = 13;
int inBuffer;



void setup () {
    // put your setup code here , to run once :
    pinMode(OUTPUT_LED , OUTPUT);
    Serial.begin(9600) ;
}

void loop () {
    // put your main code here , to run repeatedly :
    if (Serial.available ()) {
        inBuffer = Serial.read();

        show7Seg()
    }

}


void show7Seg(int num) {
    switch (num)
    {
    case 0:
        digitalWrite(OUTPUT_LED, LOW);
        pin
        break;
    
    default:
        break;
    }
}
