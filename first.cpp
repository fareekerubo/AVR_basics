
#include <avr/io.h>

int main  (void){

    DDRB = 0b00000001;// Data Direction Register setting pin0 to output and the remaining pins as input
    PORTB = 0b00000001; // Set pin0 to 5 volts
    while (1)
    {
        /* code */
    }
    
}