# WS2812B RGB LED Strip Controller

This project is designed to control a WS2812B RGB LED strip using an ATtiny85 microcontroller. The code is written in C and optimized for AVR microcontrollers
which uses 8MHz crystal. Datasheet is available on [site](https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf).

## Features

- Control individual LEDs or the entire strip.
- Support for RGB color blending.
- Efficient signal timing compatible with WS2812B data protocol.
- Uses the internal 8MHz oscillator of the ATtiny85, with precise timing optimizations.

    
    
## Prerequisites

### Hardware

- **Microcontroller**: ATtiny85 or any AVR based MCU
- **LED Strip**: WS2812B
- **Power Supply**: 5V DC for the LED strip (and 5V or 3.3V for MCU).
- **Resistor**: ~330Ω resistor between the ATtiny85 output pin and the WS2812B data pin.

### Software
| Tool              | Purpose                           | Used Version          |
|-------------------|-----------------------------------|-----------------------|
| AVR GCC Toolchain | Compiling C code for AVR MCUs     | `7.3.0`               |
| make              | Build automation tool             | `3.8.1`               | 
| avrdude           | Flashing code to microcontroller  | `6.4`                 | 

 

## Setup and Usage
Set Macro DRIVER_PIN in file WS2812B_LED_control.h for RGB LED strip.
### Compile
```bash
make
```

### Flash
```bash
make flash
```

Some examples are provided in main.c file [WS2812B_animation1, WS2812B_animation2]

## License
This project is open-source. Feel free to modify and distribute it under the MIT License.

> [!WARNING]
> Works only with 8MHz crystal