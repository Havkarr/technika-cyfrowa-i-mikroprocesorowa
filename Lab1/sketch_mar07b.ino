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
  PORTD |= (1<<PD0|1<<PD1|1<<PD2|1<<PD3|1<<PD4|1<<PD5|1<<PD6|1<<PD7);
  _delay_ms(500);
  PORTD=0x00;
  _delay_ms(500);
}
}
