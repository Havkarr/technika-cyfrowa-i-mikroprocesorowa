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

void ADC_init()
{
  // Wybranie napiecia AVCC
  sbi(ADMUX, REFS0);
  cbi(ADMUX, REFS1);

  // Wybranie podzielnika częstotliwości na 128
  sbi(ADCSRA, ADPS0);
  sbi(ADCSRA, ADPS1);
  sbi(ADCSRA, ADPS2);

  // Uruchomienie przetwornika ADC
  sbi(ADCSRA, ADEN);
}

// Kanał 1 - potencjometr
uint16_t adcChannel1()
{
  // Ustawienie przetwornika ADC na pin PC0
  cbi(ADMUX, MUX0);
  cbi(ADMUX, MUX1);
  cbi(ADMUX, MUX2);
  cbi(ADMUX, MUX3);

  // Start pomiaru
  sbi(ADCSRA, ADSC);

  while(bit_is_set(ADCSRA, ADSC))
  {}

  return ADC;
}

// Kanał 2 - fotorezystor
uint16_t adcChannel2()
{
  // Ustawienie przetwornika ADC na pin PC1
  sbi(ADMUX, MUX0);
  cbi(ADMUX, MUX1);
  cbi(ADMUX, MUX2);
  cbi(ADMUX, MUX3);  

  // Start pomiaru
  sbi(ADCSRA, ADSC);

  while(bit_is_set(ADCSRA, ADSC))
  {}

  return ADC;
}

int counter = 1;
char text[25];

void USART_Transmit(unsigned char data)
{
  while(!(UCSR0A & (1<<UDRE0)));
  UDR0 = data;
}

void writeText(char * text) {
  while (*text)
    USART_Transmit(*text++);
}

const float VREF = 0.00488; 
float calc;
uint16_t val_p = 0, val_f=0;
char text1[20];
char text2[20];
char text3[20];
bool is_dark = false;
int dig1,dig2,dig3;
int temp = 0;
int valON = 800;
int valOFF = 600;

int main() {
  ADC_init();
  uartInit();
  _delay_ms(100);
  DDRD = 0x01;
  
  while(1)
  {
    val_p = adcChannel1();
    calc = VREF * val_p;
    
    dig1 = calc;
    dig2 = (calc*10);
    dig3 = (calc*100);

    sprintf(text1, "Potencjometr %d\t", val_p);
    writeText(text1);

    val_f = adcChannel2();
    calc = VREF * val_f;
    
    dig1 = calc;
    dig2 = (calc*10);
    dig3 = (calc*100);

    sprintf(text1, "Czujnik %d\t", val_f);
    writeText(text1);
   
    if(val_f >= val_p )
    {
      sbi(PORTD, PD0);
      is_dark = true;
    }
    temp = val_p - 50;
    
    if(temp < 0 ){
      temp = 0;
    }

    if(val_f  < temp )
    {
      cbi(PORTD, PD0);
      is_dark = false;
    }

    if(is_dark == true)
    {
      sprintf(text1, "ON/OFF %d\n", valON);
      writeText(text1);
    }
    else
    {
      sprintf(text1, "ON/OFF %d\n", valOFF);
      writeText(text1);
    }
    
    _delay_ms(500);
  }
}
