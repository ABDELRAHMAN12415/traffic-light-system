#include "../UTILITIES/types.h"
#include "../UTILITIES/bit_manipulation.h"
#include "../UTILITIES/registers.h"
#include "../UTILITIES/defines.h"
#include "../ECUAL/LED DRIVER/LED.h"
#include "application.h"


#define normal 0
#define pedstrain 1
   

uint8_t seg[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
uint8_t mode = normal;
uint8_t timerOverflowCount = 0;
uint8_t sec_Count = 0;
uint8_t cars_light_state = 0;
	
//resets timer value and increases ov_counter by one

ISR(TIMER0_OV)
{
	timerOverflowCount++;
	TIMER_VALUE(TIMER0,11);       //count register reinitialization
}

//when button pressed -enter pedestrian mode(according to the last state).

ISR(EXT_INT_0)//INT0_vect
{
	 OFF_EXT_INT(INT0);
	mode = pedstrain;
	cars_light_state = sec_Count;
	sec_Count = 0;
}

  
//1-initializing each port 
//2-initialize timer 0
//3-set external interrupt0 sense
//4-enable interrupts


void app_init(void){

//1-initializing each port 

DIO_PORT_INIT(PORT_A,OUT);	//configure PORTA as output

DIO_PORT_INIT(PORT_B,OUT);	//configure PORTB as output

DIO_PORT_INIT(PORT_C,OUT);	//configure PORTC as output

DIO_PORT_INIT(PORT_D,IN);	//configure PORTD as input
	
//2-initialize timer 0	
	
SET_TIMER_MODE(TIMER0 , MODE_NORMAL);	//select normal mode of timer0	

TIMER_VALUE(TIMER0,11);	//count register initialization

//3-set external interrupt0 sense

EXT_INT_SENSE(INT0,RISING_EDGE);	//set external interrupt 0 sense to rising edge

//4-enable interrupts

EN_GENERAL_INTERRUBTS();	 //enable global interrupt

EN_TIMER_INT(TIMER0);	//enable timer OV interrupt

EN_EXT_INT(INT0);	//enable external interrupt 0
	
}

	/*
    1-initialize all ports as low
	2-enter normal mode
			//start the timer
			//a second is counted every 4 timer over flows
 	  		//display the seconds remain until the next light change
			//an if condition to determine which leds to light at the mean time
			
				//if pedestrian button is pressed//
		
	3-reinitialize the timer and all ports as low
	4-save the previous state of the leds (using the second_count of the normal mode)
	5-enter pedestrian mode
			//restart the timer
		//reduce the second count every 4 timer over flows
			//display the seconds remain until the next light change
		//an if condition to determine which leds to light at the mean time
			//exit the pedestrian mode when the second count reaches 0
		
				//the button interrupt stops the external interrupt of the button for the mean time//
				
	6-re enable the button interrupt and re enter the normal mode  
	*/



void app_start(void){
	
	while (1) 
   {
		// 6-re enable the button interrupt and re enter the normal mode //
		  
	EN_EXT_INT(INT0);			//re-enable external interrupt 0
	
		// 1-initialize all ports as low
		
  		DIO_PORT_WRITE(PORT_A,LOW);	//turn all PORTA leds off
  		DIO_PORT_WRITE(PORT_B,LOW);	//turn all PORTB leds off
  		DIO_PORT_WRITE(PORT_C,LOW);	//turn all PORTC leds off
		  
		// 2-enter normal mode
		  
		while (mode == normal)
		{
			
			//start the timer
				TIMER_START(TIMER0,CLK5);     //select F/1024 prescaler of timer0 and start
			
			// a second is counted every 4 timer over flows
				if (timerOverflowCount >= 4)
				{
					sec_Count++;
					timerOverflowCount=0;
				}	
				
			// display the seconds remain until the next light change
				if (sec_Count < 5)
				{
					PORTC = seg[5-sec_Count];
				} 
				else if (sec_Count < 10)
				{
					PORTC = seg[10-sec_Count];
				}
				else if (sec_Count < 15)
				{
					PORTC = seg[15-sec_Count];
				} 
				else
				{
					PORTC = seg[20-sec_Count];
				}
			
			// an if condition to determine which leds to light at the mean time
				if (sec_Count < 5)
				{
					
					LED_ON(green_led_pin,cars_port);
					LED_ON(red_led_pin,pedestrian_port);
					
					LED_OFF(yellow_led_pin,cars_port);
					LED_OFF(yellow_led_pin,pedestrian_port);

				}
				else if (sec_Count < 10)
				{
					
					if (timerOverflowCount == 1 || timerOverflowCount == 3)
					{
					LED_ON(yellow_led_pin,cars_port);
					LED_ON(yellow_led_pin,pedestrian_port);
					}
					else
					{
					LED_OFF(yellow_led_pin,cars_port);
					LED_OFF(yellow_led_pin,pedestrian_port);						
					}
					LED_OFF(green_led_pin,cars_port);
					LED_OFF(red_led_pin,pedestrian_port);
					

	
				}
				else if (sec_Count < 15)
				{
					
					LED_ON(red_led_pin,cars_port);
					LED_ON(green_led_pin,pedestrian_port);
					LED_OFF(yellow_led_pin,cars_port);
					LED_OFF(yellow_led_pin,pedestrian_port);				
					
				}
				else if (sec_Count < 20)
				{
					
					if (timerOverflowCount == 1 || timerOverflowCount == 3)
					{
						LED_ON(yellow_led_pin,cars_port);
						LED_ON(yellow_led_pin,pedestrian_port);
					}
					else
					{
						LED_OFF(yellow_led_pin,cars_port);
						LED_OFF(yellow_led_pin,pedestrian_port);
					}
					
					LED_OFF(red_led_pin,cars_port);
					LED_OFF(green_led_pin,pedestrian_port);
					
				}
				else 
				{
					sec_Count =0;
				}
			
		}
		
		// 3-reinitialize the timer and all ports as low
		TIMER_STOP(TIMER0);
		TIMER_VALUE(TIMER0,11);      //count register reinitialization
		
		DIO_PORT_WRITE(PORT_A,LOW);	//turn all PORTA leds off
		DIO_PORT_WRITE(PORT_B,LOW);	//turn all PORTB leds off
		DIO_PORT_WRITE(PORT_C,LOW);	//turn all PORTC leds off	
			
		// 4-save the previous state of the leds (using the second_count of the normal mode)
		if (cars_light_state < 15 && cars_light_state >= 10)	//cars light was on red
		{
			sec_Count = 10;
		} 
		else	//cars light was on green or yellow
		{
			sec_Count = 15;
		}	
		
		// 5-enter pedestrian mode	
		while (mode == pedstrain)
		{	
				//restart the timer
				TIMER_START(TIMER0,CLK5);     //select F/1024 prescaler of timer0 and start
				
				//reduce the second count every 4 timer over flows
				if (timerOverflowCount >= 4)
				{
					sec_Count--;
					timerOverflowCount=0;
				}
				
				//display the seconds remain until the next light change		
				if (sec_Count > 10)
				{
					PORTC = seg[sec_Count-10];
				} 
				else if (sec_Count > 5)
				{
					PORTC = seg[sec_Count-5];
				}
				else
				{
					PORTC = seg[sec_Count];
				} 
					
				//an if condition to determine which leds to light at the mean time	
				if (sec_Count <= 15 && sec_Count > 10 ){
					if (timerOverflowCount == 1 || timerOverflowCount == 3)
					{
						LED_ON(yellow_led_pin,cars_port);
						LED_ON(yellow_led_pin,pedestrian_port);
					}
					else
					{
						LED_OFF(yellow_led_pin,cars_port);
						LED_OFF(yellow_led_pin,pedestrian_port);
					}

				}
				else if (sec_Count <= 10 && sec_Count > 5){
					LED_ON(red_led_pin,cars_port);
					LED_ON(green_led_pin,pedestrian_port);
					LED_OFF(yellow_led_pin,cars_port);
					LED_OFF(yellow_led_pin,pedestrian_port);
					
				}
				else if (sec_Count <= 5 && sec_Count > 0){
					if (timerOverflowCount == 1 || timerOverflowCount == 3)
					{
						LED_ON(yellow_led_pin,cars_port);
						LED_ON(yellow_led_pin,pedestrian_port);
					}
					else
					{
						LED_OFF(yellow_led_pin,cars_port);
						LED_OFF(yellow_led_pin,pedestrian_port);
					}
					
					LED_OFF(red_led_pin,cars_port);
					
				}
				//exit the pedestrian mode when the second count reaches 0			
				else mode = normal;	
				
		}
			
	}
	
}






