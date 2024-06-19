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

char text[80];
char buf;
int birthdate;
int counter = 0;
bool error = false;

int main() {
  uartInit();
  
  while(1)
  {
    char year[4]={0};
    counter = 0;
    error = false;
    sprintf(text, "Podaj rok swojegu urodzenia, a ja powiem ci ile masz lat (rocznikowo):\n");
    writeText(text);

    for(int i = 0; i < 4; ++i)
    {
     counter++;
     year[i] = USART_Recive();
     if (year[i] < '0' || year[i]> '9'){
      error = true;
     }
    }

    while(buf = USART_Recive() != '\n'){
      counter++;
    }
    
    if(counter != 4){
      error = true;
    }
    
    birthdate = atoi(year);
    if ( birthdate < 1924 || birthdate > 2024 || error == true){
      sprintf(text, "Podano nieprawidlowe dane wejsciowe.\n");
      writeText(text);
    }
    else{
      sprintf(text, "Twój wiek to: %d\n", 2024-birthdate);
      writeText(text);
    }
    
  }
}
