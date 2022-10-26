
#ifndef LED_H_
#define LED_H_

#define cars_port PORT_A
#define pedestrian_port PORT_B

#define green_led_pin 0
#define yellow_led_pin 1
#define red_led_pin 2

void LED_INIT(uint8_t led_pin_num, uint8_t led_port_name);
void LED_ON (uint8_t led_pin_num, uint8_t led_port_name);
void LED_OFF (uint8_t led_pin_num, uint8_t led_port_name);

#endif 