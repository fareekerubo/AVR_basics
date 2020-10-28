#include <avr/io.h>
#include <avr/interrupt.h>

int main (void){



    //intialiaze interrupts
    sei();

    DDRB |= 1<<0;

    //timer control registers
    TCCR1B |= 1<<CS10 | 1 <<CS11 | 1 <<WGM12;

    //TIMER MASK
    TIMSK1 |= 1<<OCIE1A;
    OCR1A = 15624; //TO COMPARE WITH TCNT



    while(1)
    {

    }
}

//introduce our interrupt service routine
ISR(TIMER1_COMPA_vect)
{
  //BLINK THE ED ON PORT B

  PORTB ^= 1<<0;
}
