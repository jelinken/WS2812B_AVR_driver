/**
 * @file: WS2812B_LED_control.h
 * @author: Martin Janitor
 * @date: 26.11.2024
 * @version: 1.0
 * @details:  Provide configuration for RGB LED strip WS2812B. 
 *            Datasheet: https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf
 *  @warning: This implementation is working only with AVR MCUs with 8 MHz crystal
 *  @note: Set RGB_LEDs_buffer based on example: 
 *  -------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    | GREEN     | RED       | BLUE      |       | GREEN     | RED       | BLUE      |  ...    |       GREEN             |         RED             |           BLUE          |      
    | buffer [0]| buffer[1] | buffer[2] |       | buffer [3]| buffer[4] | buffer[5] |  ...    | buffer [NUM_LEDS_RGB-3] | buffer [NUM_LEDS_RGB-2] | buffer [NUM_LEDS_RGB-1] |
    -------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef __WS2812B_LED_CONTROL_H__
    #define __WS2812B_LED_CONTROL_H__

    #include <avr/io.h>
    #include <util/delay.h>
    #include <stdlib.h>
    #include <string.h>

    #define NUM_LEDS_RGB 29

    #define NUM_LEDS (NUM_LEDS_RGB * 3) // 29 RGBs diodes, every RGB consists of 3 LEDs

    #define DRIVER_PIN PB2

    #define NUM_REPEAT_ANIMATION 100


    /**
     * @brief Funtion initialize PIN on which is connected RGB LED strip WS2821B.
     * @note Set PIN on which in conneted strip is available via MACRO 'DRIVER_PIN'.
     *       Set NACRO 'NUM_LEDS_RGB' which defines number of RGB LEDs in strip.
     */
    void WS2812B_init(void);

    /**
     * @brief Funtion clear buffer for control all LEDs in strip (set all value in buffer to '0').
     * @param RGB_LEDs_buffer pointer to array which contains values for LEDs in strip, minimum size of this array must be (NUM_RGB_LEDs * 3),
     *                        size of this array is defined via macro 'NUM_LEDS'.
     */
    void WS2812B_reset_buffer(uint8_t* RGB_LEDs_buffer);

    /**
     * @brief Funtion set specific color for RGB LED diode in strip 
     * @param R Value of Red color in range [0-255]
     * @param G Value of Green color in range [0-255]
     * @param B Value of Blue in range [0-255]
     * @param RGB_LED_position position of RGB LED in strip, position can be number from range [0 - NUM_LEDS_RGB]
     * @param RGB_LEDs_buffer pointer to array which contains values for LEDs in strip
     * @note Mixim R, G, B value you can set any color
     */
    void WS2812B_set_color(uint8_t R, uint8_t G, uint8_t B, uint8_t RGB_LED_position, uint8_t* RGB_LEDs_buffer);

    /**
     * @brief Funtion set same RBG color for RGB LEDs in range [start_index, end_index]
     * @param R Value of Red color in range [0-255]
     * @param G Value of Green color in range [0-255]
     * @param B Value of Blue in range [0-255]
     * @param start_index Start point for RGB color in range
     * @param end_index End point for RGB color in range
     * @param RGB_LEDs_buffer pointer to array which contains values for LEDs in strip
     */
    void WS2812B_set_color_range(uint8_t R, uint8_t G, uint8_t B, uint8_t start_index, uint8_t end_index, uint8_t* RGB_LEDs_buffer);

    /**
     * @brief Funtion sends signal for all RGB LEDs in strip via PIN [DRIVER_PIN]
     * @param RGB_LEDs_array pointer to array which contains values for LEDs in strip
     */
    void WS2812B_send_signal(uint8_t* RGB_LEDs_buffer);
   
    /**
     * @brief Funtion show how can be done test animation
     * @param RGB_LEDs_buffer pointer to array which contains values for LEDs in strip
     */
    void WS2812B_animation1(uint8_t* RGB_LEDs_buffer);

    /**
     * @brief Funtion show how can be done test animation
     * @param RGB_LEDs_buffer pointer to array which contains values for LEDs in strip
     */
    void WS2812B_animation2(uint8_t* RGB_LEDs_buffer);

#endif