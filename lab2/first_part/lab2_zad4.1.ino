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


 
int main() {
  DDRD=0xff;
  DDRC=0xff;
  PORTC = 0x0f;

  while(1){
    // 1 liczba
    sbi(PORTC, PC0);
    PORTD = digits[2];
    _delay_ms(1);
    cbi(PORTC, PC0);

    // 2 liczba
    sbi(PORTC, PC1);
    PORTD = digits[1];
    _delay_ms(1);
    cbi(PORTC, PC1);

    // 3 liczba
    sbi(PORTC, PC2);
    PORTD = digits[1];
    _delay_ms(1);
    cbi(PORTC, PC2);

    // 4 liczba
    sbi(PORTC, PC3);
    PORTD = digits[5];
    _delay_ms(1);
    cbi(PORTC, PC3);
  }
}
