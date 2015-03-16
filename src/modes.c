/*
 * modes.c
 *
 *  Created on: 13.03.2015
 *      Author: H. Eilers
 */


#include "main.h"

void mode0(){

	if( getMode() != gLastMode ){

		setBlinkLength( CFG_BLINK_LEN_MAX );
		setBlinkSpeed( CFG_BLINK_SPEED_MAX );

		// indicate start
		setLedColor(0xff, 0xff, 0xff);
		uint8_t vLastMode = getMode();
		_delay_ms(25);

		// get color
		while( getMode() == vLastMode )	setLedColor(getLedRed(), getLedGreen(), getLedBlue());
		waitForMode(MODE0);

	}

	// set blink speed an length
	setBlinkLength( getBlinkLength() );
	setBlinkSpeed( getBlinkSpeed() );

}

void mode1(void){

	setBlinkSpeed(0xff);
	setBlinkLength(0xff);

	if( gFlagBlink ){

		if( gLedR == 0x00 && gLedG == 0x00 && gLedB == 0x00 ) setLedColor(0xff, 0x00, 0x00); // init
		else if( gLedR == 0xff && gLedG < 0xff && gLedB == 0x00 ) gLedG += FADE_INC;	// green raise
		else if(  gLedR > 0x00 && gLedG == 0xff && gLedB == 0x00 ) gLedR -= FADE_INC;	// red fall
		else if(  gLedR == 0x00 && gLedG == 0xff && gLedB < 0xff ) gLedB += FADE_INC;	// blue raise
		else if(  gLedR == 0x00 && gLedG > 0x00 && gLedB == 0xff ) gLedG -= FADE_INC;	// green fall
		else if(  gLedR < 0xff && gLedG == 0x00 && gLedB == 0xff ) gLedR += FADE_INC;	// red raise
		else if(  gLedR == 0xff && gLedG == 0x00 && gLedB > 0x00 ) gLedB -= FADE_INC;	// blue fall
		else setLedColor(0xff, 0x00, 0x00);

	}

}

void mode2(void){

	static uint8_t nOn = 0x00;
	static uint8_t nOff = 0x00;
	static uint8_t pause = 0x00;
	static uint8_t tick = 0x00;

	if( !tick  ){

		if( pause ){
			setLedColor(0x00, 0x00, 0x00);
			pause = 0x00;
		} else {

			if( nOn < MODE2_ON ){

				// set alarm color
				switch( getLedMode() ){
				case 0x01:
					setLedColor(0xff, 0x00, 0x00);
					break;

				case 0x02:
					setLedColor(0x00, 0xff, 0x00);
					break;

				case 0x04:
					setLedColor(0x00, 0x00, 0xff);
					break;

				case 0x08:
					setLedColor(0xff, 0x00, 0xff);
					break;

				case 0x10:
					setLedColor(0x00, 0xff, 0xff);
					break;

				case 0x20:
					setLedColor(0xff, 0x6f, 0x00);
					break;

				default:
					setLedColor(0xff, 0x3f, 0x00);
					break;
				}
				nOn++;

			} else {
				nOff++;
			}

			if( nOn == MODE2_ON && nOff == MODE2_OFF ){
				nOn = 0x00;
				nOff = 0x00;
			}

			pause = 0xff;

		}

	}

	tick++;
	if( tick == MODE2_TICK ) {
		tick = 0x00;
	}


}

void mode3(void){

	// set blink speed and length
	setBlinkLength( CFG_BLINK_LEN_MAX );
	setBlinkSpeed( CFG_BLINK_SPEED_MAX );

	// set led colors
	setLedColor(getLedRed(), getLedGreen(), getLedBlue());

}

void waitForAck(){
	uint8_t vMode = getMode();
	while( getMode() == vMode );
}

void waitForMode(uint8_t vMode){
	while( getMode() != vMode );
}
