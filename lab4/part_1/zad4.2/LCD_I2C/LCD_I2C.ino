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

void timerInit()
{
  //Wybranie trybu pracy CTC z TOP OCR1A
  // strony 132-134 dokumentacja
  sbi(TCCR1B, WGM12);
  cbi(TCCR1B, WGM13);
  cbi(TCCR1A, WGM11);
  cbi(TCCR1A, WGM10);
 
  //Wybranie dzielnika czestotliwosci - częstotliwość Atmega328: 16 MHz
  sbi(TCCR1B, CS12);
  cbi(TCCR1B, CS11);
  cbi(TCCR1B, CS10);
 
  //Zapisanie do OCR1A wartosci odpowiadajacej 1s
  OCR1A = 62500;
 
  //Uruchomienie przerwania OCIE1A
  sbi(TIMSK1, OCIE1A);
}

volatile uint8_t number = 60, numberSet = 0;
//0x27 - adres urzadzenia na I2C
LCD_I2C Lcd = LCD_I2C(0x27);
int hour = 0, hourSet = 0;
int minutes = 0, minutesSet = 0;
int seconds = 0;
char text[20];

int main() {
  timerInit();
  sei();
  DDRD = 0x00;
  PORTD = 0xff;
  DDRC = 0x01;
  
  _delay_ms(100);
  Lcd.backLightOn();
  
  while (1) {
    // Zmniejszanie czasu budzika
    if(bit_is_clear(PIND, PD2) && numberSet > 0)
    {
      while(bit_is_clear(PIND, PD2)){}
      --numberSet; 
    }
    
    // Zwiekszanie czasu budzika
    if(bit_is_clear(PIND, PD3))
    {
      while(bit_is_clear(PIND, PD3)){}
      ++numberSet; 
    }

    // Aktywacja buzzera
    if(number == (numberSet*60))
    {
      sbi(PORTC, PC0);
      // Dopoki nie wylaczymy buzzera za pomoca sw_3
      while(bit_is_set(PIND, PD4)){}
      cbi(PORTC, PC0);
    }
  }
}

ISR(TIMER1_COMPA_vect) {
  ++number;
  hour = (number / 3600)%24;
  minutes = (number / 60)%60;
  seconds = number % 60;
  minutesSet = numberSet%60;
  hourSet = (numberSet/60)%24;
  
  Lcd.clear();
  sprintf(text, "Czas:   %d:%d:%d", hour, minutes, seconds);
  Lcd.writeText(text);
  Lcd.goTo(0,1);
  sprintf(text, "Budzik: %d:%d", hourSet, minutesSet);
  Lcd.writeText(text);
}
