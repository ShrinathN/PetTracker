#include "timer_conf.h"

/*
 * This function will initialze the TIM2
 *
 * This will clock the TIM2 from the external 32.768KHz crystal, with a prescaler of 1024.
 * At every overflow, every 7.968s the MCU will leave low power mode and execute the ISR
 * Lets assume we'll finish all SPI LoRa related tasks in 30ms
 *
*/
void Timer2_Init()
{
	ASSR |= (1 << AS2); //setting the crystal source to TOSC1
	while(ASSR & 0b111); //wait until TCR2UB, OCR2UB, and TCN2UB are ready
	TCCR2 = (1 << CS22) | (1 << CS21) | (1 << CS20); //setting prescaler as 1024
	TIMSK |= (1 << 6); //enabling overflow interrupt, TOIE2

}
