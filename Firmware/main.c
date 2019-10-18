#include "main.h"
//user header files
#include "spi_conf.h"
#include "timer_conf.h"
// #include "rh_rf95.h"

static U8 data[5] = {'h','e','l','l','o'};

void main()
{
	cli(); //disabling interrupts until everything has been set up
	DDRB |= 1;
	// Timer2_Init(); //setting up timer2

	PORTB ^= 1;
	_delay_ms(1000);
	SPI_Init(); //setting up SPI

	PORTB ^= 1;
	_delay_ms(1000);
	RH_RF95_Init(); //RH_RF95 chip init

	PORTB ^= 1;
	_delay_ms(1000);
	RH_RF95_SetTxData(data, 5);
	while(1)
	{
		//testing
		RH_RF95_Transmit();
		PORTB ^= 1;
		_delay_ms(1000);
	}
}

// ISR(TIMER2_OVF_vect)
// {
// 	//RH_RF95 transmit
// }