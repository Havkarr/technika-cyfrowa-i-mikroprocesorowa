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

void uartInit(){
   sbi(UCSR0B, RXEN0);
   sbi(UCSR0B, TXEN0);
   UBRR0 = 51;
}

void timerInit(){
  //Wybranie trybu pracy CTC z TOP OCR1A
  // strony 132-134 dokumentacja
  sbi(TCCR1B, WGM12);
  cbi(TCCR1B, WGM13);
  cbi(TCCR1A, WGM11);
  cbi(TCCR1A, WGM10);

  // Przerwanie zewnetrzne
  sbi(EICRA, ISC01);
  cbi(EICRA, ISC00);
  sbi(EIMSK, INT0);
 
  //Wybranie dzielnika czestotliwosci - częstotliwość Atmega328: 16 MHz
  sbi(TCCR1B, CS12);
  cbi(TCCR1B, CS11);
  cbi(TCCR1B, CS10);
 
  //Zapisanie do OCR1A wartosci odpowiadajacej 0,5s
  OCR1A = 62500;
 
  //Uruchomienie przerwania OCIE1A
  sbi(TIMSK1, OCIE1A);
}

void USART_Transmit(unsigned char data){
  while(!(UCSR0A & (1<<UDRE0)));
  UDR0 = data;
}

void writeText(char * text) {
  while (*text)
    USART_Transmit(*text++);
}

char USART_Recive(){
  while(!(UCSR0A & (1<<RXC0)));

  return UDR0;
}

int counter = 0;
char text[30];
char input;

int main() {
  uartInit();
  timerInit();
  sei();

  sbi(DDRC,0);
  cbi(DDRC,1);
  sbi(PORTC,1);
  
  while(1)
  {
    input = USART_Recive();
    
    if(input == 'a'){
      // Wlacz diode
      sbi(PORTC, 0);
      sprintf(text, "LED1 ON\n");
      writeText(text);
    }
    else if (input == 's'){
      // Wylacz diode
      cbi(PORTC, 0);
      sprintf(text, "LED1 OFF\n");
      writeText(text);
    }
    else if (input == 'd'){
      // Sprawdzanie statusu przycisku
      if (bit_is_clear(PINC,1)){
        sprintf(text, "BUTTON 1 PRESSED\n");
        writeText(text);
      }
      else{
        sprintf(text, "BUTTON 1 NOT PRESSED\n");
        writeText(text);
      }
    }
    else if(input == 'f'){
        // Ile czasu minelo od startu programu
        sprintf(text, "%d SECOONDS HAS PASSED\n",counter);
        writeText(text);
    }
    
  }
}

// Obliczanie ilości sekund od uruchomienia programu
ISR(TIMER1_COMPA_vect) {
  ++counter;
}
