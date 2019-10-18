#include "spi_conf.h"
#include "rh_rf95.h"

void RH_RF95_Init()
{
	RH_RF95_SetMode(MODE_SLEEP);
	_delay_ms(20);
	SPI_WriteBlock(RF95_init_string[0], (RF95_init_string + 1), sizeof(RF95_init_string) - 1);
}

void RH_RF95_SetMode(RF95_Modes mode)
{
	SPI_WriteRegister(0x01, //register address
					(1 << 7) |//LORA mode
					mode);
}

void RH_RF95_SetTxData(U8 * data, U8 length)
{
	SPI_WriteRegister(0x0d, 0x0); //resetting buffer pointer to beginning
	SPI_WriteBlock(0x0, data, length); //writing the data in the internal memory
	SPI_WriteRegister(0x22, length); //setting the payload length
}

void RH_RF95_Transmit(void)
{
	RH_RF95_SetMode(MODE_TRANS);
}