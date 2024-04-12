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

// Kodowanie szesnastkowe gfedcba.
// Tablica digits zawiera wartosci dzieki ktorym ustawiamy liczby na 
// wyswietlaczu 7-segmentowym.
int digits[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
// Zmienna sec reprezentuje sekunde
int ti = 0, sec = 0;
bool count = false;

void digit()
{
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
int main() {
  // Ustawiamy jako wyjscie do ustawiania poszczególnych cyfr
  DDRD=0xff;
  // Ustawiamy jako wyjscie do segmentów i buzzera
  DDRC=0xff;
  // Ustawiamy jako wejscie przyciskow
  DDRB=0x00;
  PORTB=0x0f;
  PORTC = 0x0f;

  while(1){
    // Zmniejszanie czasu
     if(bit_is_clear(PINB,PB0) && ti != 0 && count == false){
      while(bit_is_clear(PINB,PB0)){}
      --ti;
    }

    // Zwikszenie czasu
    if(bit_is_clear(PINB,PB1) && count == false){
      while(bit_is_clear(PINB,PB1)){}
      ++ti;
    }

    // Kasuj to z internetu
    if(bit_is_clear(PINB,PB2)){
      while(bit_is_clear(PINB,PB2)){}
      ti = 0;
      if (count)
      {
        count = false;
      }
    }

    // Start timer
    if(bit_is_clear(PINB,PB3) && count == false){
      while(bit_is_clear(PINB,PB3)){}
      count = true;
    }

    // Wyswietlanie liczb
    digit();


    // Jezeli minela sekunda to zmniejsz czas 
    if(count && sec == 0)
    {
      sec = 1000;
      --ti;
      // Daj glos
      if(ti == 0)
      {
        count = false;
        sbi(PORTC, PC4);
        _delay_ms(2000);
        cbi(PORTC, PC4);
      }
    }

    // Pojedyncza petla programu trwa 5 ms
    // Przy kazdej iteracji zmniejsz sec o 5
    // az odliczysz 1 sekunde
    if(sec)
    {
      sec = sec - 5;
    }
    _delay_ms(5);
  }
}
