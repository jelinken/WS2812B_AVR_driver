
/**
 * @file: WS2812B_LED_control.c
 * @author: Martin Janitor
 * @date: 26.11.2024
 * @version: 1.0
 * @details:  Provide implementation of functions for controling WS2812B RGB LED strip
 *            First look to "WS2812B_LED_control.h" config file and read information how
 *            to use functions. Implementation of functions is based on datasheet: 
 *            https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf
 */

#include "WS2812B_LED_control.h"

void WS2812B_init(void)
{
    // Set DRIVER pin as output
    DDRB |= (1 << DRIVER_PIN);

    // Set value to zero for DRIVER pin
    PORTB &= ~(1 << DRIVER_PIN);
}

void WS2812B_reset_buffer(uint8_t* RGB_LEDs_buffer){
  if(RGB_LEDs_buffer == NULL) return;

  // Set all values of array to 0 value
  memset(RGB_LEDs_buffer,0,NUM_LEDS);
}


void WS2812B_set_color(uint8_t R, uint8_t G, uint8_t B, uint8_t RGB_LED_position, uint8_t* RGB_LEDs_buffer){
  // Chech if position is correct
  if(RGB_LED_position > (NUM_LEDS_RGB-1) || RGB_LEDs_buffer != NULL) return;

  // Calculate led position based on multiply by 3 because every RGB LED consists of 3 LED diodes
  uint8_t index_position = RGB_LED_position*3;

  // Assign Values based on datasheet
  RGB_LEDs_buffer[index_position] = G;
  RGB_LEDs_buffer[++index_position] = R;
  RGB_LEDs_buffer[++index_position] = B;
}

void WS2812B_set_color_range(uint8_t R, uint8_t G, uint8_t B, uint8_t start_index, uint8_t end_index, uint8_t* RGB_LEDs_buffer){
  // Chech if write is possible
  if((start_index == end_index) || (start_index > (NUM_LEDS_RGB-1) || end_index > (NUM_LEDS_RGB-1)) || RGB_LEDs_buffer == NULL) return;

  // Reverse indexes
  if(start_index > end_index)
  {
    uint8_t tmp = end_index;
    end_index = start_index;
    start_index = tmp;
  }

  // Assign R,G,B values for all RGB LEDs in range
  for(uint8_t i=0; i<(end_index-start_index); i++)
  {
    WS2812B_set_color(R,G,B,start_index+i,RGB_LEDs_buffer);
  }
}

void WS2812B_send_signal(uint8_t* RGB_LEDs_buffer){
  // Check if input array is empty
  if(RGB_LEDs_buffer == NULL) return;

  /* Mask which contains result of shift (2<<i) for 8 bits, 
  order is from MBS to LSB based on datasheet */
  const uint8_t mask [8] = {128,64,32,16,8,4,2,1};
  //uint8_t val = NUM_LEDS;

 // Iterate array of RGB LEDs values which contains bytes values in order (G, R, B) * number of RGB LEDs
  for(uint8_t i=0; i<NUM_LEDS;i++){

    // Iterate all bits in byte and send impulse on PIN
    for(uint8_t x =0; x<8;x++)
    {
      // Check if bit on position is 1
      if(RGB_LEDs_buffer[i] & mask[x])
      {
        // !!! Impulses are usable only for 8 MHz crystal on AVR architecture MCU !!!
        // If using dhigher frequency crystal add 'nop' instructions (test via logic analyzer or oscilloscope)

        // T1H impulse based on datsheet. Execution time: 875ns
        PORTB |= (1 << DRIVER_PIN);
        __asm__ __volatile__( "nop\n\t"
                              "nop\n\t"
                              "nop\n\t");
        PORTB &= ~(1 << DRIVER_PIN);

        // T1L impulse based on datsheet. Execution time: 1458ns
        __asm__ __volatile__("nop\n\t");
      }

      else
      { 
        // T0H impulse based on datsheet. Execution time: 375ns
        PORTB |= (1 << DRIVER_PIN);
        PORTB &= ~(1 << DRIVER_PIN);

        // T0L impulse based on datsheet. Execution time: 1583ns
        __asm__ __volatile__( "nop\n\t");
  
      }
    }
  }

  // RES impulse based on datsheet. Execution time:
  for(uint8_t i=0; i<20;i++){
      __asm__ __volatile__( "nop\n\t"
                            "nop\n\t"
                            "nop\n\t"
                            "nop\n\t"
                            "nop\n\t");
  }
           
}

void WS2812B_animation1(uint8_t* RGB_LEDs_buffer){
  // Check if input array is empty
  if(RGB_LEDs_buffer == NULL) return;

  // Count leds
  for(uint8_t x=0; x<NUM_REPEAT_ANIMATION; x++){
    for(uint8_t i=0; i < (NUM_LEDS_RGB/2); i++)
    {
      // Set array to all zeroes
      WS2812B_reset_buffer(RGB_LEDs_buffer);

      // Iterate RGB LEDS in range [15-28]
      WS2812B_set_color_range(235, 6, 124,(NUM_LEDS_RGB/2), (NUM_LEDS_RGB/2)+1+i,RGB_LEDs_buffer);

      // Iterate RGB LEDS in range [13 - 0]
      WS2812B_set_color_range(235, 6, 124,(NUM_LEDS_RGB/2)-i, (NUM_LEDS_RGB/2)-1,RGB_LEDs_buffer);

      // Send signal to WS2812B pin
      WS2812B_send_signal(RGB_LEDs_buffer);

      // Some delay
      _delay_ms(60);
    }

    for(uint8_t i=0; i<(NUM_LEDS_RGB/2); i++)
    {
        WS2812B_reset_buffer(RGB_LEDs_buffer);

        // Iterate RGB LEDS in range [28-15]
        WS2812B_set_color_range(0, 255, 245,(NUM_LEDS_RGB), (NUM_LEDS_RGB)-i,RGB_LEDs_buffer);

        // Iterate RGB LEDS in range [0 - 13]
        WS2812B_set_color_range(0, 255, 245,0, i,RGB_LEDs_buffer);
        WS2812B_send_signal(RGB_LEDs_buffer);

        // Some delay
        _delay_ms(70);
    }

  }
}

void WS2812B_animation2(uint8_t* RGB_LEDs_buffer){
  // Check if input array is empty
  if(RGB_LEDs_buffer == NULL) return;

  for(uint8_t y=0; y<NUM_REPEAT_ANIMATION; y++){

    // Send snake of length 4 which moving in RGB LED strip
    for(uint8_t i=0; i<NUM_LEDS_RGB; i++)
    {
        WS2812B_reset_buffer(RGB_LEDs_buffer);
        WS2812B_set_color_range(0, 255, 245,i, i+4,RGB_LEDs_buffer);
        WS2812B_send_signal(RGB_LEDs_buffer);
        _delay_ms(60);
    }
  }
}


