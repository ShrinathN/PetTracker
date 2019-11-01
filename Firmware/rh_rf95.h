#ifndef RH_RF95_H
#define RH_RF95_H
//includes
#include "main.h"

//enums
typedef enum {
	MODE_SLEEP = 0x0,
	MODE_STDBY = 0x1,
	MODE_TRANS = 0x3
}RF95_Modes;

const static U8 RF95_init_string[] = {
	0x6,	//register address
	217,	//0x06 -> setting frequency to 868MHz
	0,		//0x07
	0,		//0x08
	0xff,	//0x09 -> selecting max power
	0b1001, //0x0a -> setting ramp up down time as 40us
	0x2b,	//0x0b -> overcurrent protection default
	0x20,	//0x0c -> LNA gain set to max, LNA current default
	0x0,	//0x0d -> fifo ptr as 0
	0x0,	//0x0e -> FifoTxBase as 0
	0x0,	//0x0f -> FifoRxBase as 0
	0x0,	//0x10 -> FifoRxCurrentAddr, read only
	0x0,	//0x11 -> RegIrqFlagsMask, setting as 0, default
	0xff,	//0x12 -> RegIrqFlags, clearing them all
	0x0,	//0x13 -> bytes read in last payload read only
	0x0,	//0x14 -> number of valid headers since Tx mode MSB
	0x0,	//0x15 -> number of valid headers since Tx mode LSB
	0xff,	//0x16 -> number of valid packets since Tx Mode, clearing
	0x0,	//0x17
	0x0,	//0x18
	0x0,	//0x19
	0x0,	//0x1a
	0x0,	//0x1b
	0x0,	//0x1c
	0x69,	//0x1d -> RegModemConfig1, setting signal bandwidth as 62.5KHz and error coding rate as 4/8, and implicit header mode
	0xc3,	//0x1e -> RegModemConfig2, setting spread factor as 12, packet mode
	0x64,	//0x1f -> RegSymbTimeoutLsb, default
	0x0,	//0x20 -> setting preamble length as 8
	0x8,	//0x21
	0x5,	//0x22 -> PAYLOAD LENGTH!!!
	0xff,	//0x23 -> RegMaxPayloadLength, default
	0x0,	//0x24 -> RegHopPeriod, default
	0x0,	//0x25 -> RegFifoRxByteAdd, read only
	0x4		//0x26 -> setting in mobile node
};

//public functions
void RH_RF95_Init(void);
void RH_RF95_DIO0_config(void);
void RH_RF95_SetMode(RF95_Modes mode);
void RH_RF95_SetTxData(U8 * data, U8 length);
void RH_RF95_Transmit(void);

#endif