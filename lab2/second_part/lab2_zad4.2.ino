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
int time = 0, sec = 0;
bool count = false;

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
     if(bit_is_clear(PINB,PB0) && time != 0 && count == false){
      while(bit_is_clear(PINB,PB0)){}
      --time;
    }

    // Zwikszenie czasu
    if(bit_is_clear(PINB,PB1) && count == false){
      while(bit_is_clear(PINB,PB1)){}
      ++time;
    }

    // Kasuj to z internetu
    if(bit_is_clear(PINB,PB2)){
      while(bit_is_clear(PINB,PB2)){}
      time = 0;
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

    // 1 liczba
    sbi(PORTC, PC0);
    PORTD = digits[(time/1000)%10];
    _delay_ms(1);
    cbi(PORTC, PC0);

    // 2 liczba
    sbi(PORTC, PC1);
    PORTD = digits[(time/100)%10];
    _delay_ms(1);
    cbi(PORTC, PC1);

    // 3 liczba
    sbi(PORTC, PC2);
    PORTD = digits[(time/10)%10];
    _delay_ms(1);
    cbi(PORTC, PC2);

    // 4 liczba
    sbi(PORTC, PC3);
    PORTD = digits[time%10];
    _delay_ms(1);
    cbi(PORTC, PC3);

    // Jezeli minela sekunda to zmniejsz czas 
    if(count && sec == 0)
    {
      sec = 1000;
      --time;
      // Daj glos
      if(time == 0)
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
      _delay_ms(1);
      sec = sec - 5;
    }
  }
}
