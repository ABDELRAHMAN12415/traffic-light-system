/*#include "../../UTILITIES/types.h"
#include "../../UTILITIES/bit_manipulation.h"
#include "../../UTILITIES/registers.h"
#include "../../ECUAL/LED DRIVER/LED.h"
#include "../../MCAL/DIO DRIVER/dio.h"
#include "timer.h"


uint8_t timer_Ov_CM =0;
uint8_t X =0;




void main(void)
{

//EN_GENERAL_INTERRUBTS();	 //enable global interrupt
LED_INIT(1,PORT_A);


while (1)
{
	
SET_TIMER_MODE(TIMER0 , MODE_NORMAL);	//select normal mode of timer0

while (X == 0)
{	
	
	
TIMER_VALUE(TIMER0,11);	//count register initialization
TIMER_START(TIMER0,CLK5);     //select F/1024 prescaler of timer0 and start at normal mode
TIMER_ov_CHECK (TIMER0);
	timer_Ov_CM++;
	LED_ON(1,PORT_A);
TIMER_STOP(TIMER0);	
	
	if (timer_Ov_CM >= 4)
	{
		timer_Ov_CM=0;
		X = 1;
		
	}
	
}




SET_TIMER_MODE(TIMER0 , MODE_CTC);	//select normal mode of timer0	

while (X == 1)
{
	
TIMER_VALUE(TIMER0,244);		//count register initialization
TIMER_START(TIMER0,CLK5);     //select F/1024 prescaler of timer0 and start at normal mode
TIMER_ov_CHECK (TIMER0);
	timer_Ov_CM++;
	LED_OFF(1,PORT_A);
TIMER_STOP(TIMER0);

	if (timer_Ov_CM >= 4)
	{
		timer_Ov_CM=0;
		X = 0;
		
	}	
	
}

}
}*/