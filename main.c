/**
 * @file: main.c
 * @author: Martin Janitor
 * @date: 26.11.2024
 * @version: 1.0
 * @details:  Provide example how to do animation with WS2812B RGB LED strip. 
 *            First look atconfig.h file and set parameters.
 */

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "WS2812B_LED_control.h"

int main(void) {
     
  // Initialize RGB LEDs strip PIN connection
  WS2812B_init();

  // Array which contains G, R, B byte values for every RGB LED diode in WS2812B strip
  uint8_t RGB_buffer [NUM_LEDS] = {0};
   
  // Run Animations
  WS2812B_animation1(RGB_buffer);
  WS2812B_animation2(RGB_buffer);
  
  // Endless loop
  while(1);               
  return 0; 
}