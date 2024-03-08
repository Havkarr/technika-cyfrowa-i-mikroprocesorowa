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
  

while (1) {
  sbi(PORTD,PB0);
  sbi(PORTD,PB1);
  sbi(PORTD,PB2);
  sbi(PORTD,PB3);
  sbi(PORTD,PB4);
  sbi(PORTD,PB5);
  sbi(PORTD,PB6);
  sbi(PORTD,PB7);
  _delay_ms(500);
  cbi(PORTD,PB0);
  cbi(PORTD,PB1);
  cbi(PORTD,PB2);
  cbi(PORTD,PB3);
  cbi(PORTD,PB4);
  cbi(PORTD,PB5);
  cbi(PORTD,PB6);
  cbi(PORTD,PB7);
  _delay_ms(500);
}
}
