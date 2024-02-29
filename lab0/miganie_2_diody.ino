#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
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

int main() {

  DDRB = 0xff;
  _delay_ms(500);

  while (1) {
    // Włączyć diode LED 1
    sbi(PORTB,PB5);

    // Poczekać
    _delay_ms(500);
    
    // Wyłączyć diode LED 1
    cbi(PORTB,PB5);

    // Włączyc Diode LED 2
    sbi(PORTB,PB4);

    // Poczekać
    _delay_ms(500);

    // Włączyc Diode LED 2
    cbi(PORTB,PB4);

  }
}
