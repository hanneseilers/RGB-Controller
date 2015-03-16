/*
 * main.c
 *
 *  Created on: 13.03.2015
 *      Author: H. Eilers
 */

#include "main.h"

// VARIABLES
volatile uint8_t gLedR = 0x00;
volatile uint8_t gLedG = 0x00;
volatile uint8_t gLedB = 0x00;

volatile uint8_t gBlinkLength = 0xff;

volatile uint8_t gLastMode = 0xff;
volatile uint8_t gLastLedMode = 0x00;

volatile uint8_t gFlagBlink = 0x00;


// MAIN FUNCTION
int main(void) {

	// setup
	init();

	// main loop
	while(1){

		uint8_t vMode = getMode();
		uint8_t vLedMode = getLedMode();

		if( gLastMode != vMode || gLastLedMode != vLedMode || gFlagBlink ){
			switch(vMode){
			case MODE0:
				mode0();
				break;

			case MODE1:
				mode1();
				break;

			case MODE2:
				mode2();
				break;

			case MODE3:
				mode3();
				break;
			}

			gFlagBlink = 0x00;

			gLastMode = vMode;
			gLastLedMode = vLedMode;
		}

	}

}


void init(void){

	// set output and input
	CFG_MODE_DDR &= ~((1<<CFG_MODE_B0) | (1<<CFG_MODE_B1));
	CFG_MODE_LED_DDR &= ~((1<<PD0) | (1<<PD1) | (1<<PD2) | (1<<PD3) | (1<<PD4) | (1<<PD5));
	CFG_LED_DDR |= (1<<CFG_LED_R) | (1<<CFG_LED_G) | (1<<CFG_LED_B);

	// set pullups
	CFG_MODE_PORT |= (1<<CFG_MODE_B0) | (1<<CFG_MODE_B1);
	CFG_MODE_LED_PORT |= (1<<CFG_MODE_L0) | (1<<CFG_MODE_L1) | (1<<CFG_MODE_L2) | (1<<CFG_MODE_L3) | (1<<CFG_MODE_L4) | (1<<CFG_MODE_L5);

	// set rgb timer interrupt
	TCCR0A |= (1<<WGM01);		// ctc mode
	TCCR0B = (1<<CS00);			// prescaler 1
	TIMSK |= (1<<OCIE0A);		// compare match a interrupt enabled
	OCR0A = CFG_OCRA_DEFAULT;

	// enable interrupts
	sei();

}

void setLedColor(uint8_t r, uint8_t g, uint8_t b){
	gLedR = r;
	gLedG = g;
	gLedB = b;
}

void setBlinkLength(uint8_t vLength){
	gBlinkLength = vLength;
}

void setBlinkSpeed(uint8_t vSpeed){
	OCR0A = vSpeed;
	TCNT0 = 0x00;
}

uint8_t getMode(){
	return CFG_MODE_PIN & ( (1<<CFG_MODE_B0) | (1<<CFG_MODE_B1) );
}

uint8_t getLedMode(){
	return ~CFG_MODE_LED_PIN & ((1<<CFG_MODE_L0) | (1<<CFG_MODE_L1) | (1<<CFG_MODE_L2) | (1<<CFG_MODE_L3) | (1<<CFG_MODE_L4) | (1<<CFG_MODE_L5));
}

uint8_t getBlinkSpeed(){
	switch( getLedMode() & 0x07 ){
	case 0:
		return 0x00;

	case 1:
		return 0xa0;

	case 2:
		return 0x54;

	case 3:
		return 0x7e;

	case 4:
		return 0xa8;

	case 5:
		return 0xd2;

	case 6:
		return 0xfc;

	default:
		return 0xff;
	}
}

uint8_t getBlinkLength(){
	switch( (getLedMode() >> 3 ) & 0x07 ){
	case 0:
		return 0x00;

	case 1:
		return 0x2d;

	case 2:
		return 0x55;

	case 3:
		return 0x7d;

	case 4:
		return 0xa5;

	case 5:
		return 0xcd;

	case 6:
		return 0xf5;

	default:
		return 0xff;
	}

}

uint8_t getLedRed(){
	switch( getLedMode() & 0x03 ){
	case 0x01:
		return 0x55;

	case 0x02:
		return 0xaa;

	case 0x03:
		return 0xff;

	default:
		return 0x00;
	}
}


uint8_t getLedGreen(){
	switch( (getLedMode() & 0x0c) >> 2 ){
	case 0x01:
		return 0x55;

	case 0x02:
		return 0xaa;

	case 0x03:
		return 0xff;

	default:
		return 0x00;
	}
}


uint8_t getLedBlue(){
	switch( (getLedMode() & 0x30) >> 4  ){
	case 0x01:
		return 0x55;

	case 0x02:
		return 0xaa;

	case 0x03:
		return 0xff;

	default:
		return 0x00;
	}
}

// timer 0 overflow interrupt
ISR(TIMER0_COMPA_vect){

	static uint8_t n = 0x00;
	static uint8_t b = 0x00;

	if( b <= gBlinkLength ){
		if( n < gLedR ) CFG_LED_PORT |= (1<<CFG_LED_R);
		else CFG_LED_PORT &= ~(1<<CFG_LED_R);

		if( n < gLedG ) CFG_LED_PORT |= (1<<CFG_LED_G);
		else CFG_LED_PORT &= ~(1<<CFG_LED_G);

		if( n < gLedB ) CFG_LED_PORT |= (1<<CFG_LED_B);
		else CFG_LED_PORT &= ~(1<<CFG_LED_B);
	} else {
		CFG_LED_PORT &= ~((1<<CFG_LED_R) | (1<<CFG_LED_G) | (1<<CFG_LED_B));
	}

	n++;
	if( !n ){
		b++;
		gFlagBlink = 0xff;
	}

}
