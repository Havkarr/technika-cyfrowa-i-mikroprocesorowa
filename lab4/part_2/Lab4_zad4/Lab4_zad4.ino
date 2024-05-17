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

void ADC_init()
{
  // Wybranie napiecia AVCC
  sbi(ADMUX, REFS0);
  cbi(ADMUX, REFS1);

  // Wybranie podzielnika częstotliwości na 128
  sbi(ADCSRA, ADPS0);
  sbi(ADCSRA, ADPS1);
  sbi(ADCSRA, ADPS2);

  // Uruchomienie przetwornika ADC
  sbi(ADCSRA, ADEN);
}

// Kanał 1 - potencjometr
uint16_t adcChannel1()
{
  // Ustawienie przetwornika ADC na pin PC0
  cbi(ADMUX, MUX0);
  cbi(ADMUX, MUX1);
  cbi(ADMUX, MUX2);
  cbi(ADMUX, MUX3);

  // Start pomiaru
  sbi(ADCSRA, ADSC);

  while(bit_is_set(ADCSRA, ADSC))
  {}

  return ADC;
}

// Kanał 2 - fotorezystor
uint16_t adcChannel2()
{
  // Ustawienie przetwornika ADC na pin PC1
  sbi(ADMUX, MUX0);
  cbi(ADMUX, MUX1);
  cbi(ADMUX, MUX2);
  cbi(ADMUX, MUX3);  

  // Start pomiaru
  sbi(ADCSRA, ADSC);

  while(bit_is_set(ADCSRA, ADSC))
  {}

  return ADC;
}

const float VREF = 0.00488; 
float calc;
uint16_t val_p = 0, val_f=0;
//0x27 - adres urzadzenia na I2C
LCD_I2C Lcd = LCD_I2C(0x27);
char text[20];
bool is_dark = false;
int dig1,dig2,dig3;
int temp = 0;

int main() {
  ADC_init();
  _delay_ms(100);
  Lcd.backLightOn();
  DDRD = 0x01;
  
  while(1)
  {
    val_p = adcChannel1();
    calc = VREF * val_p;
    
    dig1 = calc;
    dig2 = (calc*10);
    dig3 = (calc*100);

    Lcd.clear();
    sprintf(text, "P:%d.%d%dV", dig1,dig2%10,dig3%10);
    Lcd.writeText(text);
    Lcd.goTo(9,0);

    val_f = adcChannel2();
    calc = VREF * val_f;
    
    dig1 = calc;
    dig2 = (calc*10);
    dig3 = (calc*100);

    sprintf(text, "F:%d.%d%dV", dig1,dig2%10,dig3%10);
    Lcd.writeText(text);

    if(val_f >= val_p )
    {
      sbi(PORTD, PD0);
      is_dark = true;
    }
    temp = val_p - 50;
    
    if(temp < 0 ){
      temp = 0;
    }
    
    if(val_f  < temp )
    {
      cbi(PORTD, PD0);
      is_dark = false;
    }
    
    if(is_dark)
    {
      Lcd.goTo(0,1);
      sprintf(text, "Ciemno");
      Lcd.writeText(text);
    }
    else
    {
      Lcd.goTo(0,1);
      sprintf(text, "Jasno");
      Lcd.writeText(text);
    }
    
    _delay_ms(500);
  }
}
