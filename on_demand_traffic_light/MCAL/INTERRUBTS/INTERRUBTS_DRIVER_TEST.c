/*#include "../../UTILITIES/types.h"
#include "../../UTILITIES/registers.h"
#include "../../UTILITIES/bit_manipulation.h"
#include "../DIO DRIVER/dio.h"
#include "../TIMER DRIVER/timer.h"
#include "interrubt.h"

uint8_t timer0_OverflowCount = 0;
uint8_t seg[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};



	ISR(TIMER0_OV)//TIMER0_OVER_FLOW_VEC
	{
	timer0_OverflowCount++;
	TIMER_VALUE(TIMER0,11);       //count register reinitialization
	}
	

	ISR(EXT_INT_0)//EXTERNAL_INTERRUPT0_vect
	{
	DIO_PIN_TOGGLE(5,PORT_B);
	}
	
	ISR(EXT_INT_1)//EXTERNAL_INTERRUPT0_vect
	{
	DIO_PIN_TOGGLE(6,PORT_B);
	}
	
	ISR(EXT_INT_2)//EXTERNAL_INTERRUPT0_vect
	{
	DIO_PIN_TOGGLE(7,PORT_B);
	}	
	
	
	
	
	
void main(void)
{
	

	DIO_PORT_INIT(PORT_C,OUT);	//configure PORTC as output
	
	DIO_PIN_INIT(2,PORT_D,IN);	//configure pin 2 of PORTD as input for int0
	DIO_PIN_INIT(5,PORT_B,OUT);	//configure pin 2 of PORTD as output for int0
	
	DIO_PIN_INIT(3,PORT_D,IN);	//configure pin 3 of PORTD as input for int1
	DIO_PIN_INIT(6,PORT_B,OUT);	//configure pin 2 of PORTD as output for int1
	
	DIO_PIN_INIT(2,PORT_B,IN);	//configure pin 2 of PORTB as input for int2
	DIO_PIN_INIT(7,PORT_B,OUT);	//configure pin 2 of PORTD as output for int2
	
	//enable interrupts

	EN_GENERAL_INTERRUBTS();	 //enable global interrupt

	EN_TIMER_INT(TIMER0);	//enable timer0 interrupt
	
	EN_EXT_INT(INT0);	//enable external interrupt 0
	EN_EXT_INT(INT1);	//enable external interrupt 1
	EN_EXT_INT(INT2);	//enable external interrupt 2
	
	//set external interrupts sense

	EXT_INT_SENSE(INT0,RISING_EDGE);	//set external interrupt 0 sense to rising edge
	EXT_INT_SENSE(INT1,RISING_EDGE);	//set external interrupt 0 sense to rising edge
	EXT_INT_SENSE(INT2,FALLING_EDGE);	//set external interrupt 0 sense to rising edge


SET_TIMER_MODE(TIMER0 , MODE_NORMAL);	//select normal mode of timer0

TIMER_VALUE(TIMER0,11);	//count register initialization
TIMER_START(TIMER0,CLK5);     //select F/1024 prescaler of timer0 and start at normal mode	

while (1)
{
	
		PORTC = seg[timer0_OverflowCount];


if (timer0_OverflowCount>=9)
{
	timer0_OverflowCount = 0;
}
	
	}
	
}*/