/*
 * main.h
 *
 *  Created on: 13.03.2015
 *      Author: H. Eilers
 */

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#ifndef MAIN_H_
#define MAIN_H_

// SYSTEM INCLUDES
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// CUSTOM INCLUDES
#include "modes.h"


// DEFINES
#define CFG_LED_PORT	PORTB
#define CFG_LED_DDR		DDRB
#define CFG_LED_R		PB2
#define CFG_LED_G		PB3
#define CFG_LED_B		PB4

#define CFG_MODE_PORT	PORTA
#define CFG_MODE_DDR	DDRA
#define CFG_MODE_PIN	PINA
#define CFG_MODE_B0		PA0
#define CFG_MODE_B1		PA1

#define CFG_MODE_LED_PORT	PORTD
#define CFG_MODE_LED_DDR	DDRD
#define CFG_MODE_LED_PIN	PIND
#define CFG_MODE_L0			PD0
#define CFG_MODE_L1			PD1
#define CFG_MODE_L2			PD2
#define CFG_MODE_L3			PD3
#define CFG_MODE_L4			PD4
#define CFG_MODE_L5			PD5

#define CFG_OCRA_DEFAULT	0xff
#define CFG_BLINK_SPEED_MAX	0x00
#define CFG_BLINK_LEN_MAX	0xff

// VARIABLES
extern volatile uint8_t gLedR;
extern volatile uint8_t gLedG;
extern volatile uint8_t gLedB;

extern volatile uint8_t gBlinkLength;

extern volatile uint8_t gLastMode;
extern volatile uint8_t gLastLedMode;

extern volatile uint8_t gFlagBlink;

// FUNCTIONS
void init(void);
void setLedColor(uint8_t r, uint8_t g, uint8_t b);
void setBlinkLength(uint8_t vLength);
void setBlinkSpeed(uint8_t vSpeed);
uint8_t getMode();
uint8_t getLedMode();
uint8_t getBlinkSpeed();
uint8_t getBlinkLength();

uint8_t getLedRed();
uint8_t getLedGreen();
uint8_t getLedBlue();

#endif /* MAIN_H_ */
