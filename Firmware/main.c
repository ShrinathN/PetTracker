//will use the 1MHz internal oscillator for this, gotta save power
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
//user header files
#include "spi_conf.h"
#include "timer_conf.h"

void main()
{
	while(1)
	{
	}
}