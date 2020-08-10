/*
 * main.h
 *
 *  Created on: Jan 12, 2020
 *      Author: Tijntj3
 */

#ifndef INC_MAIN_H_
#define INC_MAIN_H_

#include "hwlib.h"

#define OSC1TMR_BASE_ADDR 		0xFFD00000
#define OSC1TMR_CNT_OFFSET 		0x4
#define OSC1TMR_CNTR_OFFSET 	0x8

#define HEX_ALL_ON 				0x00
#define HEX_ALL_OFF				0x7f

#define HEX_N0_ON 				0x01
#define HEX_N1_ON 				0x02
#define HEX_N2_ON 				0x04
#define HEX_N3_ON 				0x08
#define HEX_N4_ON 				0x10
#define HEX_N5_ON 				0x20
#define HEX_N6_ON 				0x40

#define LEDS_ALL_ON 			0x3FF
#define LEDS_ALL_OFF			0x000

#define LEDS_N0_ON				0x001
#define LEDS_N1_ON				0x002
#define LEDS_N2_ON				0x004
#define LEDS_N3_ON				0x008
#define LEDS_N4_ON				0x010
#define LEDS_N5_ON				0x020
#define LEDS_N6_ON				0x040
#define LEDS_N7_ON				0x080
#define LEDS_N8_ON				0x100
#define LEDS_N9_ON				0x200

enum statesHexDisco {
	defaultMode,
	pauseMode,
	slowMode,
	fastMode,
	reverseMode
};

//public
ALT_STATUS_CODE hexDiscoInit();
ALT_STATUS_CODE isFunkyTime();
void updateHexDisco();
void setModeHexDisco(enum statesHexDisco mode);

//private
void updateAnim();
void advHexDisco();
void decHexDisco();
void defaultHexDisco();
void pauseHexDisco();
void slowHexDisco();
void fastHexDisco();

#endif /* INC_MAIN_H_ */
