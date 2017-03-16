///////////////////////////////////////////////////////////////////////
// File Name:      cert_practical1_f
// Created by:     <Please put name here>
// Course:         <Please put course name here>
// Date Created:   16/9/10
///////////////////////////////////////////////////////////////////////
// Purpose:        Description of Program
//
//                 Demonstrates Hello world, data types and operators
///////////////////////////////////////////////////////////////////////

/////////////////////////
//preprocessor directives

// Pic Chip that we are compiling for
#include <16F877A.h>
#device ICD=TRUE
#include <stdio.h>
#include <stdlib.h>

// setup clock speed 20mhz crystal
#use delay(clock=20000000)

// setup chip
#fuses HS,NOLVP,NOWDT,NOPROTECT,NOBROWNOUT,PUT

//set up rs232 pins on pic
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7)

#include "BENGLCD420.C"
//void startup_screen(void);
void led_test(void);
//end of preprocessor directives
//////////////////////
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

//initialise the board

//set all pins on portb of pic to be outputs
set_tris_b (0x00);

set_tris_a(0xdf);

//set adc channels on pic as per you circuit
setup_adc(  ADC_CLOCK_INTERNAL  );
setup_adc_ports( ALL_ANALOG );
lcd_init();
led_test();
//startup_screen();
// The statements (instructions)
////////////////////////////////
while(true) // super loop
   {
   
     printf(lcd_putc("Serial baud 9600 \n"));
   lcd_gotoxy( 1,4);
   
  

   // wait for the option to be entered from the user
   option = getchar();

   if(option == '1')
     {
     printf("=====================================\n\r");
     printf("<1> Turn on green LED 1 \r\n");
     printf("=====================================\n\r");
     output_bit( PIN_B4, 0);
     printf(lcd_putc("LED 1 on \n"));
      //delay_ms(1000);
     lcd_putc('\f');
     }

   else if(option == '2')
     {
     printf("=====================================\n\r");
     printf("<2> Turn off green LED 1 \r\n");
     printf("=====================================\n\r");
     output_bit( PIN_B4, 1);
     printf(lcd_putc("LED 1 off \n"));
     // delay_ms(1000);
     lcd_putc('\f');
     }

   else if(option == '3')
     {
     printf("=====================================\n\r");
     printf("<3> Turn on red LED \r\n");
     printf("=====================================\n\r");
     output_bit( PIN_B5, 0);
     printf(lcd_putc("LED 2 on \n"));
   //   delay_ms(1000);
     lcd_putc('\f');
     }

   else if(option == '4')
     {
     printf("=====================================\n\r");
     printf("<4> Turn off red LED \r\n");
     printf("=====================================\n\r");
     output_bit( PIN_B5, 1);
     printf(lcd_putc("LED 2 off \n"));
    //  delay_ms(1000);
     lcd_putc('\f');
     }

 else if(option == '5')
     {
     printf("=====================================\n\r");
     printf("<5> Turn on red LED \r\n");
     printf("=====================================\n\r");
     output_bit( PIN_A5, 0);
     printf(lcd_putc("LED 3 on \n"));
   //  delay_ms(1000);
     lcd_putc('\f');
     }

   else if(option == '6')
     {
     printf("=====================================\n\r");
     printf("<6> Turn off red LED \r\n");
     printf("=====================================\n\r");
     output_bit( PIN_A5, 1);
     
     printf(lcd_putc("LED 3 off \n"));
   //  delay_ms(1000);
     lcd_putc('\f');
     }
    
   else
     {
     printf("=====================================\n\r");
     printf("            INVALID OPTION\n\r");
     printf(lcd_putc,"  INVALID OPTION      ");
     printf("=====================================\n\r");
     }

   // delay 10ms before before sending out message again
   delay_ms(10);
   
   
    
   
        
   }//end of while
   
} 


void startup_screen(void)
{

//print out welcome info on lcd
lcd_gotoxy( 1,1);
printf(lcd_putc," W.I.T I.O.T Year 2");

//display fisrt custom pattern
lcd_gotoxy( 10,2);
lcd_send_byte(1,0x00);



lcd_gotoxy( 9,3);
printf(lcd_putc,"2016");
lcd_gotoxy( 4,4);
printf(lcd_putc," Hello World   \n");

//delay for a short time


//clear lcd display
lcd_putc('\f');
}

void led_test(void){
 output_bit( PIN_B5, 0);
 output_bit( PIN_B4, 0);
  output_bit( PIN_A5, 0);
 output_bit( PIN_A5, 1);
 output_bit( PIN_B5, 1);
  output_bit( PIN_B4, 1); 

}

