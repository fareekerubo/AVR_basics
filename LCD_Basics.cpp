//LCD
/*LCD 16x2 is a 16 PIN device which has 8 data pins (D0-D7) and 3 control pins(RS,RW,EN)
The remaining 5 pins are for supply and backlight for the LCD. The control pins helps us
 configure the LCD in command mode or write mode and also when to read and write.

 LCD 16x2 can be used in 4-bit mode or 8-bit mode depending on the requirement of the 
 application.In order to use it we neeed to send certain commands to the LCD in command 
 mode and once the LCD is configured according to our need, we can send the required data 
 in data mode.



 Hardware connections 
 LCD 16X2 Pins           ATMEGA32PINS
 Data pins d0-d7            PORTB
 RS                         PORTC.0
 RW                         PORTC.1
 E                          PORTC.2

 */


 #include <avr/io.h>
 #include <util/delay.h>

 #define LCD_Data_Dir       DDRB    // Data pins on portb
 #define LCD_Command_Dir    DDRC    //DEFINING CD COMMAND PORT DIRECTION REGISTER
 #define LCD_Data_Port      PORTB   //define LCD data 
 #define LCD_Command_Port   PORTC   //  define Lcd data port
 #define RS                 PC0     //DEFINE REGISTER SELECT PIN
 #define RW                 PC1     //define READ/WRITE SIGNAL PIN
 #define EN                 PC2     //define enable signal pin




 //Intializing LCD
 /*Steps to be followed to intialize an LCD 16X2

1.  Power ON the LCD
2.  Wait for 15 ms (‘Power ON’ initialization time for LCD16x2)
3.  Send 0x38 command to initialize 2 lines, 5x8 matrix, 8-bit mode LCD16x2
4.  Send any ‘Display ON’ command (0x0E, 0x0C) to LCD16x2
5.  Send 0x06 command (increment cursor) to LCD16x2

*/

void LCD_Init(void){




    DDRC |= 1<<PINC0;   //Setting lcd command port direction as output
    DDRB |= 1<<PINB0;   //setting lcd data port direction as output

    _delay_ms(20);      //LCD POWER ON delay always>15ms
    LCD_Command(0x38);  //intialization of 16x2 LCD in 8bit mode
    LCD_Command(0x0C);  //Display ON Cursor OFF
    LCD_Command(0x06);  //Autoincrement cursor
    LCD_Command(0x01);  //clear display
    LCD_Command(0x80); //cursor at home position

    
}

/* Now that we have intialized the LCD, it is ready to accept data for displaying.
we now write a Command Write Function in the following steps


1.Send the command value to the LCD 16X2 data port
2.Make RS pin low, RS=0(COMMANG REG)
3.Make RW pin low, RW=0(WRITE OPERATION)
4.Give high to low pulse at the Enable(E) pin of minimum delay of 450ns.


When we give an enable pulse, the LCD latches the data present at D0 to D7,
 and execute as command since RS is command reg

*/

void LCD_Command(unsigned char cmnd )
{
    LCD_Data_Port = cmnd;
    LCD_Command_Port &= ~(1<<RS); // RS=0 command reg
    LCD_Command_Port &= ~(1<<RW); //RW=0 WRITE OPERATION
    LCD_Command_Port |= (1<<EN);  //Enable pulse
    _delay_us(1);
    LCD_Command_Port |= (1<<EN);
     _delay_us(3);



}


/*Data Write Function

1.  Send command to the data port
2.  Make the RS pin HIGH, RS = 1(Data reg)
3.  Make the RW pin Low,RW=0(Write operation)
4.  Give HIGH to LOW pulse at the Enable(E) pin.

When we give an enable pulse the LCD latches the data present (on the pins D0 to D7)
 and displays it on a 5x8 matrix, as RS is a data register

 */

 void LCD_Char(unsigned char char_data)
 {
     LCD_Data_Port = char_data;
     LCD_Command_Port |= (1<<RS);  //RS=1 Data reg
     LCD_Command_Port  &= ~(1<<RW); //RW=0 WRITE OPERATION
     LCD_Command_Port  |= (1<<EN);
     _delay_us(1);
     LCD_Command_Port &= ~(1<<EN);
     _delay_ms(1)
 }

 /*Display String function

    This function takes a string (an array of characters) and sends one character
    time to the LCD data function till the end of the string. A ‘for loop’ is used for 
    sending a character in each iteration. A NULL character indicates end of the string.

    */

void LCD_String (char *str)		
{
	int i;
	for(i=0;str[i]!=0;i++)  /* send each char of string till the NULL */
	{
		LCD_Char (str[i]);  /* call LCD data write */
	}
}


/*Note:

LCD Power-on delay: After the LCD16x2 powers ON, we cannot send commands immediately to 
it since it needs a self-initialization time of 15-ms. Therefore, while programming, 
we need to take care of providing sufficient power ON delay (> 15 ms), and then send a command to the LCD.
After proving commands, LCD16x2 takes time (in microseconds) to execute it. 
But for the 0x01 command (i.e. clear display), it takes 1.64-ms to execute. 
Therefore, after sending the 0x01 command sufficient delay (> 1.63milliseconds) needs to be provided.

*/