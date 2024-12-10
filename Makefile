# @file: Makefile
# @author: Martin Janitor
# @date: 26.11.2024
# @version: 1.0
# @details: Makefile for compiling program and uploading code to MCU

CC=avr-gcc
OPTIMALIZATION=-O2
OPTIONAL= -Wl,-Map=output.map 
MCU= attiny85
FREQ= 8000000
PROGRAMMER= usbasp

hex:
	$(CC) $(OPTIMALIZATION) -DF_CPU=$(FREQ) -mmcu=$(MCU) -c main.c 
	$(CC) $(OPTIMALIZATION) -DF_CPU=$(FREQ) -mmcu=$(MCU) -c WS2812B_LED_control.c

	$(CC) -DF_CPU=$(FREQ) $(OPTIMALIZATION) $(OPTIONAL) -mmcu=$(MCU) -o main.elf main.o WS2812B_LED_control.o
	avr-objcopy -O ihex main.elf main.hex

flash:
# -B 5 value for slower version of some programmers
	avrdude -c $(PROGRAMMER) -p $(MCU) -U flash:w:main.hex -B 5

clean:
# Linux
	rm -f *.o *.hex *.elf *.map
# Windows
	del *.o *.hex *.elf *.map