#ifndef SPI_CONF_H
#define SPI_CONF_H
#include "main.h"

//===========CONFIGURATION============
#define SPI_DIRECTION_REGISTER DDRB
#define SPI_PORT PORTB
#define SPI_SCK_PIN PB5
#define SPI_MISO_PIN PB4
#define SPI_MOSI_PIN PB3
#define SPI_SS_PIN PB1

//macros
#define WAIT_SPI while(!(SPSR & (1 << SPIF))) //for waiting while the SPIF pin is not set in the SPSR register
#define SPI_SS_HIGH SPI_PORT |= (1 << SPI_SS_PIN)
#define SPI_SS_LOW SPI_PORT &= ~(1 << SPI_SS_PIN)


//public function declaration
void SPI_Init();
U8 SPI_ReadRegister(U8 spi_register_address);
U8 SPI_WriteRegister(U8 spi_register_address, U8 data);
void SPI_ReadBlock(U8 spi_starting_address, U8 * buffer, U8 bytes_to_read);
void SPI_WriteBlock(U8 spi_starting_address, U8 * buffer, U8 bytes_to_write);
U8 SPI_Transmit(U8 data);


#endif