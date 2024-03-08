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
  for(int i = 0; i<8; i++){
    sbi(PORTD,i);
    _delay_ms(500);
    cbi(PORTD,i);
  }
 
}
}
