#include <avr/io.h>
#include <util/delay.h>

int main (void){
    // intiliazation of the ports
    //leds
    DDRB |= 1<<PINB0; 
    PORTB &= ~(1<<PINB0);

    //counter intialization
    TCCR1B |= 1<<CS10; //no prescalling

    //introuduce a variable to hold the repeatcount
    int repeatCount = 0 ;



    while(1){
        //count and turn an LED on and off
        if(TCNT1 > 100000)
        { 
            repeatCount ++;
            TCNT1 = 0; //make sure the internal oscillator does not overflow by taking it to zero when it gets to 1000
            if(repeatCount >100){
            
            repeatCount = 0;
            PORTB ^= 1<<PINB0;// toggle the Led on and off
             }   //
        }

    }
}