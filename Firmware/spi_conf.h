#ifndef TIMER_CONF_H
#define TIMER_CONF_H
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
#define SPI_SS_HIGH SPI_PORT |= SPI_SS_PIN
#define SPI_SS_LOW SPI_PORT &= ~SPI_SS_PIN;


//public function declaration
void SPI_Init();
__UINT8_TYPE__ SPI_GetSpiStatus();


#endif