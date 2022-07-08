
#define PIN_ANALOG A0

volatile int prevValue = 0;
int value = 0;
char buf[40];

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_ANALOG, INPUT);
  
  Serial.begin(9600);
}

void loop() {
  
  value = analogRead(PIN_ANALOG);
  if(abs(value - prevValue) > 50) {
    prevValue = value;
    int percent = map(value, 0, 1023, 0, 100);
    sprintf(buf, "%d%%", percent);
    Serial.print(buf);
  }
}
