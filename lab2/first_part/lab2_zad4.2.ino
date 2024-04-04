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
int time = 0;
bool count = false;

int main() {
  DDRD=0xff;
  DDRC=0xff;
  DDRB=0x00;
  PORTB=0x0f;
  PORTC = 0x1f;

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

    if(count)
    {
      --time;
      if(time == 0)
      {
        count = false;
      }
    }
  }
}
