
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo servo_9;
Servo servo_10;
Servo servo_11;

LiquidCrystal_I2C lcd(0x20,20,4);

int incomingBytes = 0;
int pos[2] = {0, 0};
int eixo = 0;

bool can_move = false;

void move(int pos, int motor);

void setup()
{
  Serial.begin(9600);
  servo_9.attach (9);
  servo_10.attach (10);
  servo_11.attach (11);
  
  lcd.init();
  
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("CONTROLE SERVO");
}

void loop()
{
  if (Serial.available() > 0) {
    switch (eixo) {
      case 0:
      	pos[0] = Serial.parseInt();
      	if (pos[0] > 180 || pos[0] < 0) {
      		pos[2] = 0;
          	lcd.setCursor(1,1);
          	lcd.print("Eixo X invalido!");
          	delay(1000);
        } else {
            lcd.clear();
            lcd.setCursor(1,0);
            lcd.print("Eixo X: ");
            lcd.print(pos[0]);
        }
      	eixo += 1;
      	break;
      case 1:
      	pos[1] = Serial.parseInt();
      	if (pos[1] > 180 || pos[1] < 0) {
      		pos[1] = 0;
         	lcd.clear();
          	lcd.setCursor(1,1);
          	lcd.print("Eixo Y invalido!");
          	delay(1000);
        }
        else {
          lcd.clear();
          lcd.setCursor(1,0);
          lcd.print("Eixo Y: ");
          lcd.print(pos[1]);
        }
      	eixo += 1;
      	break;
      case 2:
      	pos[2] = Serial.parseInt();
      	if (pos[2] > 180 || pos[2] < 0) {
      		pos[2] = 0;
          	lcd.clear();
          	lcd.setCursor(1,1);
          	lcd.print("Eixo Z invalido!");
          	delay(1000);
        } else {
        	lcd.clear();
      		lcd.setCursor(1,0);
    		lcd.print("Eixo Z: ");
     		lcd.print(pos[2]);
      		can_move = true;
        }
      	break;
    }
    exit(0);
  }
    
  if (can_move == true) {
    for (int i = 0; i < 3; i++) {
      move(pos[i], i);
      delay(2000);
    }
    can_move = false;
    eixo = 0;
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Configurado com,");
    lcd.setCursor(1,1);
    lcd.print("Sucesso!");
  }
  
}
void move(int pos, int motor) {
  switch (motor) {
    
    case 0: 
  		servo_9.write(pos);
    	lcd.clear();
      	lcd.setCursor(1,0);
	  	lcd.print("Eixo X: ");
    	lcd.print(pos);
    	break;
    case 1:
    	servo_10.write(pos);
    	lcd.clear();
      	lcd.setCursor(1,0);
	  	lcd.print("Eixo Y: ");
    	lcd.print(pos);
    	break;
    case 2:
    	servo_11.write(pos);
    	lcd.clear();
      	lcd.setCursor(1,0);
	  	lcd.print("Eixo Z: ");
    	lcd.print(pos);
    	break;
    
  }
}