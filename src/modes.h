/*
 * modes.h
 *
 *  Created on: 13.03.2015
 *      Author: H. Eilers
 */

#ifndef MODES_H_
#define MODES_H_

#define FADE_INC		1
#define MODE2_ON		3
#define MODE2_OFF		1
#define MODE2_TICK		10

#define MODE0	0x00
#define MODE1	0x01
#define MODE2	0x02
#define MODE3	0x03

void waitForAck();
void waitForMode(uint8_t vMode);

void mode0(void);
void mode1(void);
void mode2(void);
void mode3(void);

#endif /* MODES_H_ */
