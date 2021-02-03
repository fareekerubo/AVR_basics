#include <avr/io.h>
#define LED_OUTPUT  PORTB
#define PIR_input   PINC



int main(void){

DDRC = 0x00;  //setting PIR port as an input port
DDRB = 0Xff;  //setting LED port as an output port
 
while(1){

  LED_OUTPUT = PIR_input;
}



}