#ifndef MAIN_H
#define MAIN_H

//macros
#define U8_MAX 0xff

//typedefs
typedef unsigned char U8;
typedef signed char S8;

//will use the 1MHz internal oscillator for this, gotta save power
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <string.h>

#define ANIMAL_ID "THNDR"






#endif