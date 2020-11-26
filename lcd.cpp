#include <avr/io.h>
#include <util/delay.h>

#define LCD_Data_Dir        DDRD      /*Define LCD data port direction*/
#define LCD_Command_Dir     DDRB    //Define LCD command port direction register
#define LCD_Data_Port       PORTD     //Define LCD data port
#define LCD_Command_Port    PORTB  //Define LCD data port
#define RS                  PB0    //Define Register Select 
#define RW                  PB1     //Define Read/Write signal pin
#define EN                  PB2     //Define Enable Signal pin

void LCD_Command(unsigned char cmnd);
void LCD_Char (unsigned char char_data) ;/* LCD data write function */
void LCD_Init (void);
void LCD_String (char *str);
void LCD_String_xy(char row, char pos, char *str);
void LCD_Clear();

int main()
{

  LCD_Init();     /* Initialize LCD */
   while(1)
   {
  LCD_String("ElectronicWINGS");  /* write string on 1st line of LCD*/
  LCD_Command(0xC0);    /* Go to 2nd line*/
  LCD_String("Hello World");  /* Write string on 2nd line*/
   }
}
//Command Write Function

void LCD_Command(unsigned char cmnd)
{
  
  LCD_Command_Port &= ~(1<<RS); /* RS=0 command reg. */
  LCD_Command_Port &= ~(1<<RW); /* RW=0 Write operation */
  LCD_Data_Port= cmnd;
  LCD_Command_Port |= (1<<EN);  /* Enable pulse */
  _delay_us(1);
  LCD_Command_Port &= ~(1<<EN);
  _delay_ms(3);
}

//Data write function

void LCD_Char (unsigned char char_data) /* LCD data write function */
{

  LCD_Command_Port |= (1<<RS);  /* RS=1 Data reg. */
  LCD_Command_Port &= ~(1<<RW); /* RW=0 write operation */
    LCD_Data_Port= char_data;
  LCD_Command_Port |= (1<<EN);  /* Enable Pulse */
  _delay_us(1);
  LCD_Command_Port &= ~(1<<EN);
  _delay_ms(1);
}

//LCD intialize function

void LCD_Init (void)      /* LCD Initialize function */
{
  LCD_Command_Dir = 0xFF;   /* Make LCD command port direction as o/p */
  LCD_Data_Dir = 0xFF;    /* Make LCD data port direction as o/p */
  _delay_ms(20);      /* LCD Power ON delay always >15ms */
  
  LCD_Command (0x38);   /* Initialization of 16X2 LCD in 8bit mode */
  LCD_Command (0x0C);   /* Display ON Cursor OFF */
  LCD_Command (0x06);   /* Auto Increment cursor */
  LCD_Command (0x01);   /* Clear display */
  _delay_ms(2);

  LCD_Command (0x80);   /* Cursor at home position */
}

  /* Send string to LCD function */
void LCD_String (char *str)   /* Send string to LCD function */
{
  int i;
  for(i=0;str[i]!=0;i++)    /* Send each char of string till the NULL */
  {
    LCD_Char (str[i]);
  }
} 

//Send string to LCD wih xy position

void LCD_String_xy(char row, char pos, char *str)
{
    if(row == 0 && pos<16)
    LCD_Command((pos & 0x0f) | 0x80);/* Command of first row and required position<16 */
    else if (row == 1 && pos<16)
    LCD_Command((pos & 0x0F)|0xC0);/* Command of first row and required position<16 */
    LCD_String(str);/* Call LCD string function */
}

void LCD_Clear()
{
  LCD_Command (0x01);   /* clear display */
  LCD_Command (0x80);   /* cursor at home position */
}


 