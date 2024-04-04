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




 
int main() {
  DDRD=0xff;
  DDRB=0xff;

  // Zapal diode co 1 sekunde, odliczaj do 8.
  for(int i = 0; i<8; i++){
    sbi(PORTD,i);
    sbi(PORTB,PB5);
    _delay_ms(10);
    cbi(PORTB,PB5);
    _delay_ms(1000);
  }

  // Po 8 sekundach migają wszystkie diody przez 5 sekund.
  for(int i = 0; i<5; i++){
    PORTD = 0x00;
    _delay_ms(500);
    PORTD = 0xff;
    _delay_ms(500);
  }
}
