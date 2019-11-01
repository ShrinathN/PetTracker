#include "spi_conf.h"
#include "rh_rf95.h"

/*
 * Initializes the RF96
 *
 * This function initializes the RF96, by first putting it in sleep mode, then sending over the RF95_init_string, to initialize
*/
void RH_RF95_Init()
{
	RH_RF95_SetMode(MODE_SLEEP);
	_delay_ms(20);
	SPI_WriteBlock((U8)RF95_init_string[0], (U8*)(RF95_init_string + 1), (U8)sizeof(RF95_init_string) - 1);
}

/*
 * Used to set the mode
 *
 * Used to set the mode on the RF96 chip
 * @param (RF95_Modes)mode this is the mode enum, it can be 0x0, 0x1 or 0x3
*/
void RH_RF95_SetMode(RF95_Modes mode)
{
	SPI_WriteRegister(0x01, //register address
					(1 << 7) |//LORA mode
					mode);
}

/*
 * Sets up the Tx data in the RF96
 *
 * Writes the Tx data into the buffer starting at address 0, then writes the length of the payload in the register
 * @param (U8*)data is the pointer to the payload data
 * @param (U8)length is the length of the payload
*/
void RH_RF95_SetTxData(U8 * data, U8 length)
{
	SPI_WriteRegister(0x0d, 0x0); //resetting buffer pointer to beginning
	SPI_WriteBlock(0x0, data, length); //writing the data in the internal memory
	SPI_WriteRegister(0x22, length); //setting the payload length
}

/*
 * Sets the mode to transmit mode
*/
void RH_RF95_Transmit(void)
{
	RH_RF95_SetMode(MODE_TRANS);
}