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
 
  //Wybranie dzielnika czestotliwosci - częstotliwość Atmega328: 16 MHz
  sbi(TCCR1B, CS12);
  cbi(TCCR1B, CS11);
  cbi(TCCR1B, CS10);
 
  //Zapisanie do OCR1A wartosci odpowiadajacej 5ms
  OCR1A = 312;
 
  //Uruchomienie przerwania OCIE1A
  sbi(TIMSK1, OCIE1A);

}

// Kodowanie szesnastkowe gfedcba.
// Tablica digits zawiera wartosci dzieki ktorym ustawiamy liczby na 
// wyswietlaczu 7-segmentowym.
int digits[11] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x80};
// Zmienna sec reprezentuje sekunde
int ti = 0, sec = 0;
bool count = false;

//volatile -informacja dla kompilatora aby nie optymalizował zmiennej, 
//zmienna bezpieczna do wykorzystania w przerwaniach
volatile int zmienna=0; 



int main() {
  timerInit();
  sei(); //Uruchamia przerwania globalne
  // Ustawiamy jako wyjscie do ustawiania poszczególnych cyfr
  DDRD=0xff;
  // Ustawiamy jako wyjscie do segmentów i buzzera
  DDRC=0xff;

  while(1){
      _delay_ms(1000);
      if(ti < 250){
        ++ti;
      }
    }

}

// Kod multipleksowania wyswietlacza w przerwaniu
ISR(TIMER1_COMPA_vect) {
  
  static int helper = 0;
  // Zgas poprzedni segment
  cbi(PORTC, helper);
  helper++;
  
  if(helper > 3)
  {
    helper = 0;
  }
  
  int temp = ti/pow(10,(3-helper));
  PORTD = digits[temp%10];
  // Zapal obecny segment
  sbi(PORTC, helper);
}
