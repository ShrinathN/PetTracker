#include "main.h"
//user header files
#include "spi_conf.h"
#include "timer_conf.h"

void main()
{
	cli(); //disabling interrupts until everything has been set up
	Timer2_Init(); //setting up timer2
	SPI_Init(); //setting up SPI
	//TODO: RH_RF95 init comes here
	sei(); //enabling interrupts
	set_sleep_mode(SLEEP_MODE_PWR_SAVE); //setting mode as power save
	while(1)
	{
		sleep_mode();
	}
}

ISR(TIMER2_OVF_vect)
{
	//RH_RF95 transmit
}