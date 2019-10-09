#include "spi_conf.h"

/* Setting up the SPI bus
 *
 * Setting it up at a modest 250KHz, that is F_CPU / 4, default clock speed
*/
void SPI_Init()
{
	//implicitly setting clock speed at FCPU / 4
	SPCR = (1 << SPE) | //enabling SPI
			(1 << MSTR) | //setting SPI mode as master
			(0 << CPOL) | //setting CPOL as 0, SCK leading and trailing edges as rising and falling
			(0 << CPHA);  //setting sample at leading edge and setup at trailing edge
}

__UINT8_TYPE__ SPI_GetSpiStatus()
{
	//I had to hardcode the address of SPI status register since it was not defined
	return *((volatile unsigned char *)(0x2e));
}