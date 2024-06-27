#define LED_RED 11
#define LED_BLUE 10
#define LED_GREEN 9
#include <LiquidCrystal_I2C.h>
 
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(14, INPUT);
  lcd.init();
  lcd.backlight(); 
  lcd.print("Temperatura:");
}

float temp = 0.0;

void loop() {
  temp = analogRead(14) * 0.0049 * 20.0;
  lcd.setCursor(11,1);
  lcd.print(temp);
  delay(200);
  
  // Zielony
  if (temp <= 50.0){
    analogWrite(LED_RED, 255);
    analogWrite(LED_GREEN, 0);
    analogWrite(LED_BLUE, 255);
  }
  // Niebieski
  else if (temp >50 && temp <= 70){
    analogWrite(LED_RED, 255);
    analogWrite(LED_GREEN, 255);
    analogWrite(LED_BLUE, 0);
  }
  // Fioletowy
  else if (temp >70 && temp <= 80){
    analogWrite(LED_RED, 0);
    analogWrite(LED_GREEN, 255);
    analogWrite(LED_BLUE, 128);
  }
  // Żółty
  else if (temp >80 && temp <= 90){
    analogWrite(LED_RED, 0);
    analogWrite(LED_GREEN, 0);
    analogWrite(LED_BLUE, 255);
  }
  // Czerwony
  else{
    analogWrite(LED_RED, 0);
    analogWrite(LED_GREEN, 255);
    analogWrite(LED_BLUE, 255);
  }
  
}
