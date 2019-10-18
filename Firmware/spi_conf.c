#include "spi_conf.h"

//private function declaration


U8 SPI_Transmit(U8 data)
{
	U8 to_return_value = U8_MAX;
	SPDR = data; //sending the data
	WAIT_SPI;
	to_return_value = SPDR;
	return to_return_value;
}

/* Setting up the SPI bus
 *
 * Setting it up at a modest 2MHz, that is F_CPU / 4, default clock speed
*/
void SPI_Init(void)
{
	//setting up pin directions for SCK, MOSI and SS as output, MISO is input
	SPI_DIRECTION_REGISTER |= (1 << SPI_SCK_PIN) |
							(1 << SPI_MOSI_PIN) |
							(1 << SPI_SS_PIN) |
							(1 << PB2); //apparently you need to set the SS pin as output EVEN if you are not using it. I wasted too much time on this

	//implicitly setting clock speed at FCPU / 4
	SPCR = (1 << SPE) | //enabling SPI
			(1 << MSTR) | //setting SPI mode as master
			(0 << CPOL) | //setting CPOL as 0, SCK leading and trailing edges as rising and falling
			(0 << CPHA);  //setting sample at leading edge and setup at trailing edge

	SPI_SS_HIGH; //pulling SS high for the first time
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
	SPI_Transmit(spi_register_address); //sending the register address, with implicit read bit
	register_data = SPI_Transmit(0x0); //sending dummy 0x0 to read register
	SPI_SS_HIGH; //pulling SPI SS line high again
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
	SPI_Transmit((1 << 7) | spi_register_address); //sending register address, with write bit
	register_old_data = SPI_Transmit(data); //writing the data to the register, and reading old data
	SPI_SS_HIGH; //pulling SPI SS line high again
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
	SPI_Transmit(spi_starting_address); //sending the register address
	while(counter < bytes_to_read)
	{
		buffer[counter] = SPI_Transmit(0x0); //storing the data into the buffer
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
	SPI_Transmit((1 << 7) | spi_starting_address); //sending the register address, with write bit
	while(counter < bytes_to_write)
	{
		SPI_Transmit(buffer[counter]); //storing the data into the buffer
		counter++; //incrementing the counter
	}
	SPI_SS_HIGH; //pulling SPI SS line high again
}