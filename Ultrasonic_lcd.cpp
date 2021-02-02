#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include "lcdibrary.h"   //incuding lcd header file


#define Trigger_pin  PD0 //Trigger pin

int TimerOverflow = 0;


ISR(TIMER1_OVF_vect)
{
  TimerOverflow++;    //increment timer overflow count
}

int main (void){

  char string[10];
  long count;
  double distance;

  DDRD |= 0xFF; // make the trigger pin an output
  PORTD = 0XFF;// make the pull up to a high


  LCD_Init(); // intialize the lcd
  LCD_String_xy(1,0, ((char *)"Ultrasonic"));


  sei(); //Enable global interrupt
  TIMSK0 = (1 << TOIE1);  //Enable Timer1 overflow interrupts
  TCCR1A = 0; //Set all bit to zero Normal operation

  while(1)
  {
    // Toggle trigger pulse on trig pin to HC-SR04
    PORTD |= (1<<PD0);
    _delay_us(10);
    PORTD &= (~(1 << PD0));


    TCNT1 = 0 ; //Clear Timer Counter
    TCCR1B = 0X41; //Capture on rising scale, No prescaler
    TIFR0 = 1<<ICF1; // Clear ICP flag(Input Capture Flag)
    TIFR0 = 0X01; //Clear Timer Overflow flag


    //Calculate width of echo by input Capture(ICP)
    while ((TIFR0 &(1 << ICF1))  == 0 ); //Wait for rising edge
    TCNT1 = 0; //Clear Timer Counter
    TCCR1B = 0X01; // Capture on falling edge, No prescaler
    TIFR0 = 1 << ICF1; //Clear ICP flag(Input Capture Flag)
    TIFR0 = 0X01; //Clear Timer Overflow flag
    TimerOverflow = 0; // Clear Timer Overflow count

    while ((  TIFR0 & (1 << ICF1)) == 0); //wait for falling edge
    count = ICR1 + (65535 * TimerOverflow); //Take count

    //8mHZ Timer frequency, sound speed = 343m/s
    distance = (double)count / 466.47;

    dtostrf(distance, 2, 2, string); //distance to string
    strcat(string, "cm"); //concat unit i.e cm
   // LCD_String_xy(2, 0,(char(*)"Dist= ");
     LCD_String_xy(2,0,((char *)"Ultrasonic"));
    LCD_String_xy(2, 7, string); // Print distance
    _delay_ms(200);




  }
}
