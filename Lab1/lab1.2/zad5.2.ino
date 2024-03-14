#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>
 
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

void on(){
  PORTD=0xff;
}

void off() {
  PORTD=0x00;
}
 
int main() {
 
  DDRB=0x00;
  DDRD=0xff;
  bool is_on = false;

  // Przycisk monostabilny
  sbi(PORTB,PB0);
  // Przycisk bistabilny
  sbi(PORTB,PB1);
  

while (1) {
//  if(bit_is_clear(PINB,PB1)){
//    for(uint8_t i = 0; i < 8; ++i){
//      tbi(PORTD,i);
//    }
  if(bit_is_clear(PINB,PB1) && is_on == false){
    on();
    is_on = true;
    _delay_ms(250);
  } 
  else if(bit_is_clear(PINB,PB1) && is_on == true){
    off();
    is_on = false;
    _delay_ms(250);
  }
  }
}
