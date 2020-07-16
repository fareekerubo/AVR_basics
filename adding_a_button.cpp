#include <avr/io.h>
#include <util/delay.h>
int main (void){

    DDRB |= 1 <<PINB0; // data direction register sets pinBO as the output
    DDRB &= ~(1 <<PINB1);//data direction register sets pinB1 as the input
    PORTB |= 1<<PINB1;// PINB1 should have a high reading(5v) prior to the button being pressed.

    while(1)
    {
        PORTB ^= 1<< PINB0;// XOR operation to toggle pin0 on PINB
         
         //if statement to control what happens when the button is pressed
         //if(button is pressed){
             //code for what happens in our case blink led faster
         //}
         //else
         //{
             //code for what happens if condition has not been meet i.e blink the led relativey slow
         //}
         if(bit_is_clear(PINB,1)){
             _delay_ms(10);//led blink faster
         }
         else{
             _delay_ms(100);//ed blink slowly

         }


    }

}

