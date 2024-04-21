#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
 
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


void timerInit() {
  //Wybranie trybu pracy CTC z TOP OCR1A
  // strony 132-134 dokumentacja
  sbi(TCCR1B, WGM12);
  cbi(TCCR1B, WGM13);
  cbi(TCCR1A, WGM11);
  cbi(TCCR1A, WGM10);

  // Przerwanie zewnetrzne
  sbi(EICRA, ISC01);
  cbi(EICRA, ISC00);
  sbi(EIMSK, INT0);
 
  //Wybranie dzielnika czestotliwosci - częstotliwość Atmega328: 16 MHz
  sbi(TCCR1B, CS12);
  cbi(TCCR1B, CS11);
  cbi(TCCR1B, CS10);
 
  //Zapisanie do OCR1A wartosci odpowiadajacej 0,5s
  OCR1A = 31250;
 
  //Uruchomienie przerwania OCIE1A
  sbi(TIMSK1, OCIE1A);

}


//volatile -informacja dla kompilatora aby nie optymalizował zmiennej, 
//zmienna bezpieczna do wykorzystania w przerwaniach
volatile int zmienna=0; 



int main() {
  timerInit();
  sei(); //Uruchamia przerwania globalne
  sbi(DDRD,PD0);
  sbi(DDRD,PD1); 
  sbi(DDRD,PD5);
  cbi(DDRD,PD2);
  sbi(PORTD,PD2);

  while (1) {
    tbi(PORTD, PD0);

    _delay_ms(500);
  }
}

ISR(TIMER1_COMPA_vect) {
  //kod programu przełączajacy diodę LED na pinie PD1
  tbi(PORTD, PD1);
}

ISR(INT0_vect)
{
  tbi(PORTD, PD5);
}
