// Lab4 zad 1
#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>

#include "LCDI2C.h"

#ifndef _BV
#define _BV(bit)        (1<<(bit))
#endif
#ifndef sbi
#define sbi(reg,bit)    reg |= (_BV(bit))
#endif

#ifndef cbi
#define cbi(reg,bit)    reg &= ~(_BV(bit))
#endif

#ifndef tbi
#define tbi(reg,bit)    reg ^= (_BV(bit))
#endif


int main() {
  //0x27 - adres urzadzenia na I2C
  LCD_I2C Lcd = LCD_I2C(0x27);
  _delay_ms(100);
  Lcd.backLightOn();

  // Ustawianie przyciskow
  DDRD = 0x00;  
  PORTD = 0xff;
  
  int number = 0;
  char text[20];
  sprintf(text, "LCD-czas: %d", number);
  Lcd.writeText(text);
  while (1) {
    if(bit_is_clear(PIND,PD2) && number > -100)
    {
      while(bit_is_clear(PIND,PD2)){};
      --number;
      Lcd.clear();
      sprintf(text, "LCD-czas: %d", number);
      Lcd.writeText(text);
      
    }
    if(bit_is_clear(PIND,PD3) && number < 100)
    {
      while(bit_is_clear(PIND,PD3)){};
      ++number;
      Lcd.clear();
      sprintf(text, "LCD-czas: %d", number);
      Lcd.writeText(text);
    }
  }
}
