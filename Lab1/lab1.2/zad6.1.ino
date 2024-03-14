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

  sbi(PORTB,PB0);
  sbi(PORTB,PB1);
  sbi(PORTB,PB2);
  sbi(PORTB,PB3);
  

while (1) {
  // Wyłączanie wszystkich diód (shut down)
  if(bit_is_clear(PINB,PB2)){
    while(bit_is_clear(PINB,PB2)){}
    off();
    _delay_ms(50);
    
    }
  // Włączanie wszystkich diód
  if(bit_is_clear(PINB,PB3)){
    while(bit_is_clear(PINB,PB3)){}
    on();
    _delay_ms(50);
    
    }
  // Zwiększanie liczby świecących diód
  if(bit_is_clear(PINB,PB1)){
    while(bit_is_clear(PINB,PB1)){}
    if(PORTD == 0){
      PORTD = PORTD + 1;
    }
    else{
      PORTD = PORTD << 1;
      PORTD = PORTD + 1;
    }
    _delay_ms(50);
    
    }

  // zmniejszanie liczby świecących diód
  if(bit_is_clear(PINB,PB0)){
    while(bit_is_clear(PINB,PB0)){}
    PORTD = PORTD >> 1;
    _delay_ms(50);
    
    }
    
  }
}
