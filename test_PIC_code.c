///////////////////////////////////////////////////////////////////////
// File Name:      cert_practical1_f
// Created by:     Emma Ní Bhriain
// Course:         Internet of Things
// Date Created:   1/11/16
///////////////////////////////////////////////////////////////////////
// Purpose:        Description of Program
//
//                 Demonstrates Hello world, data types and operators
///////////////////////////////////////////////////////////////////////

/////////////////////////
//preprocessor directives

// Pic Chip that we are compiling for
#include <16F877A.h>



// setup clock speed 4mhz crystal
#use delay(clock=20000000)

#include <BENGLCD420.c>

// setup chip
#fuses HS,NOLVP,NOWDT,NOPROTECT,NOBROWNOUT,PUT

//set up rs232 pins on pic
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7)



//end of preprocessor directives
//////////////////////

void startup_screen();


//////////////////////////////
//
//    MAIN PROGRAM THE START
//
//////////////////////////////
void main()
{
///////////////////////////////
// variable declarations
// specify, name and initialse 
// the data types
///////////////////////////////
char option = 0;
int ADC_value = 0;


lcd_init();
startup_screen();

//initialise the board

//set all pins on portb of pic to be outputs
set_tris_b (0x00);

set_tris_a (0xdf);

//set adc channels on pic as per you circuit
setup_adc(  ADC_CLOCK_INTERNAL  );
setup_adc_ports( ALL_ANALOG );

// The statements (instructions)
////////////////////////////////
while(true) // super loop
   {
   //send message on the serial port
   printf("=====================================\n\r");
   printf("operators(student name here)\n\r");
   printf("=====================================\n\r");
   printf("<1> Turn on  LED 1 \r\n");
   printf("<2> Turn off LED 1 \r\n");
   printf("<3> Turn on  LED 2 \r\n");
   printf("<4> Turn off LED 2 \r\n");
   printf("<5> Turn on  LED 3 \r\n");
   printf("<6> Turn off LED 3 \r\n");
   printf("<7> Read Temperature \r\n");
   printf("<8> Read Digital input \r\n");
   printf("=====================================\n\r");

   // wait for the option to be entered from the user
   option = getchar();
   lcd_gotoxy( 3,3);
   printf(lcd_putc,"%c", option);
   

   if(option == '1')
     {
     printf("=====================================\n\r");
     printf("<1> Turn on  LED 1 \r\n");
     printf("=====================================\n\r");
     output_bit( PIN_B4, 0);
     lcd_putc('\f');
     lcd_gotoxy( 3,1);
     printf(lcd_putc,"LED 1 is on");
     }

   else if(option == '2')
     {
     printf("=====================================\n\r");
     printf("<2> Turn off LED 1 \r\n");
     printf("=====================================\n\r");
     output_bit( PIN_B4, 1);
     lcd_putc('\f');
     lcd_gotoxy( 3,1);
     printf(lcd_putc,"LED 1 is off");
     }

   else if(option == '3')
     {
     printf("=====================================\n\r");
     printf("<3> Turn LED 2 on \r\n");
     printf("=====================================\n\r");
     output_bit( PIN_B5, 0);
     lcd_putc('\f');
     lcd_gotoxy( 3,2);
     printf(lcd_putc,"LED 2 is on");
     }

   else if(option == '4')
     {
     printf("=====================================\n\r");
     printf("<4> Turn LED 2 off \r\n");
     printf("=====================================\n\r");
     output_bit( PIN_B5, 1);
     lcd_putc('\f');
     lcd_gotoxy( 3,2);
     printf(lcd_putc,"LED 2 is off");
     }
     
     else if(option == '5')
     {
     printf("=====================================\n\r");
     printf("<5> Turn LED 3 on \r\n");
     printf("=====================================\n\r");
     output_bit( PIN_A5, 0);
     lcd_putc('\f');
     lcd_gotoxy( 3,3);
     printf(lcd_putc,"LED 3 is on");
     }
     
     else if(option == '6')
     {
     printf("=====================================\n\r");
     printf("<6> Turn LED 3 off \r\n");
     printf("=====================================\n\r");
     output_bit( PIN_A5, 1);
     lcd_putc('\f');
     lcd_gotoxy( 3,3);
     printf(lcd_putc,"LED 3 is off");
     }

   else if(option == '7')
     {
     printf("=====================================\n\r");
     printf("<7> Read Temperature \r\n");
     printf("=====================================\n\r");

      //set up adc channel for temperature sensor
     set_adc_channel(0);
     delay_us(10);
     
     //clear lcd display
     lcd_putc('\f');
     
      do
      {
         //read the adc value
         ADC_value = read_adc();
         printf("A/D value = %u\n\r", ADC_value);
         lcd_putc('\f');
         lcd_gotoxy( 0,4);
         printf(lcd_putc,"  Analogue in = %u\n\r",ADC_value);
         if(ADC_value<200)
         {
            output_bit( PIN_A5, 1);
         }
         else
         {
            output_bit( PIN_A5, 0);
         }
      }
      while(1); //input(PIN_A4));
      
     }
     
     else if(option == '8')
     {
     printf("=====================================\n\r");
     printf("<8> Read digital input \r\n");
     printf("=====================================\n\r");
     
     if(input(PIN_A4))
      {
         printf("Digital input on\n\r");
      }
     else
     {
         printf("Digital input off\n\r");
     }
     }
   else
     {
     printf("=====================================\n\r");
     printf("            INVALID OPTION\n\r");
     printf("=====================================\n\r");
     }

   // delay 250ms before before sending out message again
   delay_ms(250);
   }//end of while

}//end of main

void startup_screen(void)
{
//bitmap design for custom icons
unsigned char unlocked_pattern[8] = {14,16,16,31,27,27,31,0};
unsigned char locked_pattern[8]   = {14,17,17,31,27,27,31,0};
unsigned char space_invader1[8]   = {0,17,14,27,21,14,31,17};
unsigned char space_invader2[8]   = {0,17,14,27,21,14,31,10};

int16 i;

//send down first custom pattern
LCD_build(0,locked_pattern);

//send down second custom pattern
LCD_build(1,unlocked_pattern);

//send down third custom pattern
LCD_build(2,space_invader1);

//send down fourth custom pattern
LCD_build(3,space_invader2);

//print out welcome info on lcd
lcd_gotoxy( 1,1);
printf(lcd_putc," Internet of Things");

//display fisrt custom pattern
lcd_gotoxy( 10,2);
lcd_send_byte(1,0x00);

//space invader animation
for(i=9;i<=11;i++)
   {
   //display third custom pattern
   lcd_gotoxy(i,3);
   lcd_send_byte(1,0x02);

   //delay to see effect
   delay_ms(400);

   //display fourth custom pattern
   lcd_gotoxy(i,3);
   lcd_send_byte(1,0x03);

   //delay to see effect
   delay_ms(400);

   //blank this position at x, y
   lcd_gotoxy(i,3);
   lcd_send_byte(1,0x20);
   }

//display second custom pattern
lcd_gotoxy( 10,2);
//lcd_send_byte(1,0x01);
printf(lcd_putc,"2016");

lcd_gotoxy( 6,3);
printf(lcd_putc,"Once more");
lcd_gotoxy( 1,4);
printf(lcd_putc,"  Unto the breach\n");

//delay for a short time
delay_ms(1000);

//clear lcd display
lcd_putc('\f');
}
