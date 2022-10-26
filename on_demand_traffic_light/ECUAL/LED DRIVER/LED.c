
#include "../../UTILITIES/types.h"
#include "../../UTILITIES/defines.h"
#include "../../MCAL/DIO DRIVER/dio.h"
#include "LED.h"


/* uses th dio pin initialization function to initialize a pin as output */

void LED_INIT(uint8_t led_pin_num, uint8_t led_port_name){
	
DIO_PIN_INIT(led_pin_num, led_port_name, OUT);

}

/* uses th dio pin writing function to write high to a pin */

void LED_ON (uint8_t led_pin_num, uint8_t led_port_name){
	
DIO_PIN_WRITE(led_pin_num, led_port_name, HIGH);

}

/* uses th dio pin writing function to write low to a pin */


void LED_OFF (uint8_t led_pin_num, uint8_t led_port_name){
	
DIO_PIN_WRITE(led_pin_num, led_port_name, LOW);

}