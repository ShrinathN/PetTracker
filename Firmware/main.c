#include "main.h"
//user header files
#include "spi_conf.h"
#include "timer_conf.h"
// #include "rh_rf95.h"

static U8 data[] = ANIMAL_ID;

void main()
{
	cli(); //disabling interrupts until everything has been set up
	Timer2_Init(); //setting up timer2
	SPI_Init(); //setting up SPI
	RH_RF95_Init(); //RH_RF95 chip init
	MCUCR |= (0b11 << 4); //select power-save mode as sleep mode
	sei(); //enable interrupts
	while(1)
	{
		sleep_mode(); //sleep
	}
}

ISR(TIMER2_OVF_vect)
{
	RH_RF95_SetMode(1);
	_delay_ms(10);
	RH_RF95_SetTxData(data, strlen(ANIMAL_ID));
	RH_RF95_Transmit(); //RH_RF95 transmit
	_delay_ms(500); //this is for calculation purposes only, ideally this should be dependent upon DIO0 <-> INT0
	RH_RF95_SetMode(0); //put RF95 to sleep
}