#include <avr/io.h>


int main (void){

  DDRB |= 1<<0;// LED AS AN OUTPUT
  DDRC &= ~(1<<0);//PIR AS AN INPUT

  while(1){
    DDRB = DDRB; // EQUATE PIRINPUT TO LEDOUTPUT
  }
}