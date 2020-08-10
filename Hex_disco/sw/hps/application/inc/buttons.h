/*
 * buttons.h
 *
 *  Created on: Jan 18, 2020
 *      Author: Tijntj3
 */

#ifndef INC_BUTTONS_H_
#define INC_BUTTONS_H_

#include "hwlib.h"

#define BUTTON_ALL_OFF	0x0F

#define BUTTON_N0_ON	0x0E
#define BUTTON_N1_ON	0x0D
#define BUTTON_N2_ON	0x0B
#define BUTTON_N3_ON	0x07

enum buttons
{
	notDebounced,
	button0,
	button1,
	button2,
	button3
};

enum buttons debBut();

#endif /* INC_BUTTONS_H_ */
