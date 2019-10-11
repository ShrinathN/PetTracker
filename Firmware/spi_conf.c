#include "spi_conf.h"

//private function declaration

/* Setting up the SPI bus
 *
 * Setting it up at a modest 250KHz, that is F_CPU / 4, default clock speed
*/
void SPI_Init()
{
	//setting up pin directions for SS
	SPI_DIRECTION_REGISTER |= (1 << SPI_SS_PIN);

	//setting up the pull up resistors of the pins
	SPI_PORT |= (1 << SPI_SCK_PIN) |
			(1 << SPI_MISO_PIN) |
			(1 << SPI_MOSI_PIN) |
			(1 << SPI_SS_PIN); //SS pin

	//implicitly setting clock speed at FCPU / 4
	SPCR = (1 << SPE) | //enabling SPI
			(1 << MSTR) | //setting SPI mode as master
			(0 << CPOL) | //setting CPOL as 0, SCK leading and trailing edges as rising and falling
			(0 << CPHA);  //setting sample at leading edge and setup at trailing edge
}

/* This function reads the value of a single register and returns it
 *
 * @param (U8)spi_register_address address of the register in the SPI device
 * @return value stored in the register
*/
U8 SPI_ReadRegister(U8 spi_register_address)
{
	U8 register_data = U8_MAX;
	SPI_SS_LOW; //pulling SPI pin low
	WAIT_SPI; //until all data has been pushed out, wait
	SPDR = spi_register_address; //sending the register address
	WAIT_SPI; //waiting for the address to be sent
	SPDR = 0x0; //reading the register data finally, sending a 0x0
	WAIT_SPI; //waiting again
	SPI_SS_HIGH; //pulling SPI SS line high again
	register_data = SPDR; //reading the data from the SPI data register
	return register_data; //returning the data read
}

/* This function writes a single value into a register and returns the older value of the same register
 *
 * @param (U8)spi_register_address address of the register in the SPI device
 * @param (U8)data the data to be written to the register
 * @return older value stored in the register
*/
U8 SPI_WriteRegister(U8 spi_register_address, U8 data)
{
	U8 register_old_data = U8_MAX;
	SPI_SS_LOW; //pulling SPI pin low
	WAIT_SPI; //until all data has been pushed out, wait
	SPDR = spi_register_address | (1 << 7); //sending the register address, and write bit
	WAIT_SPI; //waiting for the address to be sent
	SPDR = data; //writing the new register value
	WAIT_SPI; //waiting again
	SPI_SS_HIGH; //pulling SPI SS line high again
	register_old_data = SPDR; //reading the old value of the register from the SPDR
	return register_old_data; //returning the old register value
}

/* This function reads a block of data
 *
 * This function reads a block of data and stores it into the given buffer
 * @param (U8)spi_starting_address starting address of the block of data, this is assuming the address auto-increments with each read
 * @param (U8*)buffer a pointer to the buffer where the data is to be stored
 * @param (U8)bytes_to_read the number of bytes to read from the memory of the SPI device
*/
void SPI_ReadBlock(U8 spi_starting_address, U8 * buffer, U8 bytes_to_read)
{
	U8 counter = 0;
	SPI_SS_LOW; //pulling SPI pin low
	WAIT_SPI; //until all data has been pushed out, wait
	SPDR = spi_starting_address; //sending the register address
	WAIT_SPI; //waiting for the address to be sent
	while(counter < bytes_to_read)
	{
		SPDR = 0x0; //reading the register data finally, sending a 0x0 as dummy
		WAIT_SPI; //waiting again
		buffer[counter] = SPDR; //storing the data into the buffer
		counter++; //incrementing the counter
	}
	SPI_SS_HIGH; //pulling SPI SS line high again
}

/* This function writes a block of data
 *
 * This function writes to a block of data from the given buffer
 * @param (U8)spi_starting_address starting address of the block of data, this is assuming the address auto-increments with each read
 * @param (U8*)buffer a pointer to the buffer where the data is to be read from
 * @param (U8)bytes_to_write the number of bytes to write to the SPI device from the buffer
*/
void SPI_WriteBlock(U8 spi_starting_address, U8 * buffer, U8 bytes_to_write)
{
	U8 counter = 0;
	SPI_SS_LOW; //pulling SPI pin low
	WAIT_SPI; //until all data has been pushed out, wait
	SPDR = spi_starting_address | (1 << 7); //sending the start register address and write bit
	WAIT_SPI; //waiting for the address to be sent
	while(counter < bytes_to_write)
	{
		SPDR = buffer[counter]; //writing the data from the buffer
		WAIT_SPI; //waiting again
		counter++; //incrementing the counter
	}
	counter = SPDR; //this is done so that the SPIF bit in the SPSR is cleared
	SPI_SS_HIGH; //pulling SPI SS line high again
}