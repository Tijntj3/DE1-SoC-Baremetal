/*
 * hexDisco.c
 *
 *  Created on: Jan 15, 2020
 *      Author: Tijntj3
 */

//Library references
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//Header files
#include "hexDisco.h"
#include "hps_soc_system.h"
#include "socal/socal.h"
#include "buttons.h"

//Globals
enum statesHexDisco modeHexDisco;

unsigned char animState;
unsigned int prevCount;

//Setup
ALT_STATUS_CODE hexDiscoInit()
{
	defaultHexDisco();

	animState = 0;
	updateAnim();

	return ALT_E_SUCCESS;
}

ALT_STATUS_CODE isFunkyTime()
{
	ALT_STATUS_CODE status = ALT_E_FALSE;
	unsigned int curCount = alt_read_word(OSC1TMR_BASE_ADDR + OSC1TMR_CNT_OFFSET);

	if(curCount > prevCount || modeHexDisco == pauseMode)
	{
		status = ALT_E_TRUE;
	}

	prevCount = curCount;
	return status;
}

void updateHexDisco()
{
	switch(modeHexDisco)
	{
	default:
		advHexDisco();
		break;
	case pauseMode:
		switch(debBut())
		{
		default:
			break;
		case button2:
			advHexDisco();
			break;
		case button3:
			decHexDisco();
			break;
		}
		break;
	case reverseMode:
		decHexDisco();
		break;
	}

	updateAnim();
}

void setModeHexDisco(enum statesHexDisco mode)
{
	modeHexDisco = mode;

	switch(modeHexDisco)
	{
	default:
		break;
	case defaultMode:
		defaultHexDisco();
		break;
	case pauseMode:
		pauseHexDisco();
		break;
	case slowMode:
		slowHexDisco();
		break;
	case fastMode:
		fastHexDisco();
		break;
	case reverseMode:
		defaultHexDisco();
		break;
	}
}

void defaultHexDisco()
{
	alt_write_word(OSC1TMR_BASE_ADDR + OSC1TMR_CNTR_OFFSET, 0x0);
	alt_write_word(OSC1TMR_BASE_ADDR, 2500000);
	alt_write_word(OSC1TMR_BASE_ADDR + OSC1TMR_CNTR_OFFSET, 0x3);
}


void advHexDisco()
{
	animState = (animState + 1)%85;
}

void decHexDisco()
{
	animState = (animState - 1);

	if(animState == 255)
	{
		animState = 84;
	}
}

void pauseHexDisco()
{
	alt_write_word(OSC1TMR_BASE_ADDR + OSC1TMR_CNTR_OFFSET, 0x0);
}

void slowHexDisco()
{
	alt_write_word(OSC1TMR_BASE_ADDR + OSC1TMR_CNTR_OFFSET, 0x0);
	alt_write_word(OSC1TMR_BASE_ADDR, 25000000);
	alt_write_word(OSC1TMR_BASE_ADDR + OSC1TMR_CNTR_OFFSET, 0x3);
}

void fastHexDisco()
{
	alt_write_word(OSC1TMR_BASE_ADDR + OSC1TMR_CNTR_OFFSET, 0x0);
	alt_write_word(OSC1TMR_BASE_ADDR, 250000);
	alt_write_word(OSC1TMR_BASE_ADDR + OSC1TMR_CNTR_OFFSET, 0x3);
}

void updateAnim()
{
	switch(animState)
	{
	default:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_5_BASE, HEX_ALL_OFF);
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_4_BASE, HEX_ALL_OFF);
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_3_BASE, HEX_ALL_OFF);
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_2_BASE, HEX_ALL_OFF);
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_1_BASE, HEX_ALL_OFF);
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_0_BASE, HEX_ALL_OFF);
		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_ALL_OFF);
		break;

	case 1:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_5_BASE, HEX_ALL_OFF - HEX_N5_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_N9_ON);
		break;

	case 2:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_5_BASE, HEX_ALL_OFF - HEX_N5_ON - HEX_N0_ON);
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_4_BASE, HEX_ALL_OFF);
		break;

	case 3:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_4_BASE, HEX_ALL_OFF - HEX_N5_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_N9_ON + LEDS_N8_ON);
		break;

	case 4:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_4_BASE, HEX_ALL_OFF - HEX_N5_ON - HEX_N4_ON);
		break;

	case 5:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_4_BASE, HEX_ALL_OFF - HEX_N5_ON - HEX_N4_ON - HEX_N3_ON);
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_3_BASE, HEX_ALL_OFF);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_N9_ON + LEDS_N8_ON + LEDS_N7_ON);
		break;

	case 6:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_3_BASE, HEX_ALL_OFF - HEX_N4_ON);
		break;

	case 7:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_3_BASE, HEX_ALL_OFF - HEX_N5_ON - HEX_N4_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_N9_ON + LEDS_N8_ON + LEDS_N7_ON + LEDS_N6_ON);
		break;

	case 8:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_3_BASE, HEX_ALL_OFF - HEX_N5_ON - HEX_N4_ON - HEX_N0_ON);
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_2_BASE, HEX_ALL_OFF);
		break;

	case 9:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_2_BASE, HEX_ALL_OFF - HEX_N5_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_N9_ON + LEDS_N8_ON + LEDS_N7_ON + LEDS_N6_ON + LEDS_N5_ON);
		break;

	case 10:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_2_BASE, HEX_ALL_OFF - HEX_N5_ON - HEX_N4_ON);
		break;

	case 11:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_2_BASE, HEX_ALL_OFF - HEX_N5_ON - HEX_N4_ON - HEX_N3_ON);
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_1_BASE, HEX_ALL_OFF);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_N9_ON + LEDS_N8_ON + LEDS_N7_ON + LEDS_N6_ON + LEDS_N5_ON + LEDS_N4_ON);
		break;

	case 12:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_1_BASE, HEX_ALL_OFF - HEX_N4_ON);
		break;

	case 13:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_1_BASE, HEX_ALL_OFF - HEX_N5_ON - HEX_N4_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_N9_ON + LEDS_N8_ON + LEDS_N7_ON + LEDS_N6_ON + LEDS_N5_ON + LEDS_N4_ON + LEDS_N3_ON);
		break;

	case 14:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_1_BASE, HEX_ALL_OFF - HEX_N5_ON - HEX_N4_ON - HEX_N0_ON);
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_0_BASE, HEX_ALL_OFF);
		break;

	case 15:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_0_BASE, HEX_ALL_OFF - HEX_N5_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_N9_ON + LEDS_N8_ON + LEDS_N7_ON + LEDS_N6_ON + LEDS_N5_ON + LEDS_N4_ON + LEDS_N3_ON + LEDS_N2_ON);
		break;

	case 16:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_0_BASE, HEX_ALL_OFF - HEX_N5_ON - HEX_N4_ON);
		break;

	case 17:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_0_BASE, HEX_ALL_OFF - HEX_N5_ON - HEX_N4_ON - HEX_N3_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_N9_ON + LEDS_N8_ON + LEDS_N7_ON + LEDS_N6_ON + LEDS_N5_ON + LEDS_N4_ON + LEDS_N3_ON + LEDS_N2_ON + LEDS_N1_ON);
		break;

	case 18:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_0_BASE, HEX_ALL_OFF - HEX_N5_ON - HEX_N4_ON - HEX_N3_ON - HEX_N2_ON);
		break;

	case 19:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_0_BASE, HEX_ALL_OFF - HEX_N5_ON - HEX_N4_ON - HEX_N3_ON - HEX_N2_ON - HEX_N1_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_ALL_ON);
		break;

	case 20:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_0_BASE, HEX_ALL_OFF - HEX_N5_ON - HEX_N4_ON - HEX_N3_ON - HEX_N2_ON - HEX_N1_ON - HEX_N0_ON);
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_1_BASE, HEX_ALL_OFF - HEX_N5_ON - HEX_N4_ON - HEX_N0_ON);
		break;

	case 21:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_1_BASE, HEX_ALL_OFF - HEX_N5_ON - HEX_N4_ON - HEX_N1_ON - HEX_N0_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_ALL_ON);
		break;

	case 22:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_1_BASE, HEX_ALL_OFF - HEX_N5_ON - HEX_N4_ON - HEX_N2_ON - HEX_N1_ON - HEX_N0_ON);
		break;

	case 23:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_1_BASE, HEX_ALL_OFF - HEX_N5_ON - HEX_N4_ON - HEX_N3_ON - HEX_N2_ON - HEX_N1_ON - HEX_N0_ON);
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_2_BASE, HEX_ALL_OFF - HEX_N5_ON - HEX_N4_ON - HEX_N3_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_ALL_ON);
		break;

	case 24:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_2_BASE, HEX_ALL_OFF - HEX_N5_ON - HEX_N4_ON - HEX_N3_ON - HEX_N2_ON);
		break;

	case 25:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_2_BASE, HEX_ALL_OFF - HEX_N5_ON - HEX_N4_ON - HEX_N3_ON - HEX_N2_ON - HEX_N1_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_N8_ON + LEDS_N7_ON + LEDS_N6_ON + LEDS_N5_ON + LEDS_N4_ON + LEDS_N3_ON + LEDS_N2_ON + LEDS_N1_ON + LEDS_N0_ON);
		break;

	case 26:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_2_BASE, HEX_ALL_OFF - HEX_N5_ON - HEX_N4_ON - HEX_N3_ON - HEX_N2_ON - HEX_N1_ON - HEX_N0_ON);
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_3_BASE, HEX_ALL_OFF - HEX_N5_ON - HEX_N4_ON - HEX_N0_ON);
		break;

	case 27:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_3_BASE, HEX_ALL_OFF - HEX_N5_ON - HEX_N4_ON - HEX_N1_ON - HEX_N0_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_N7_ON + LEDS_N6_ON + LEDS_N5_ON + LEDS_N4_ON + LEDS_N3_ON + LEDS_N2_ON + LEDS_N1_ON + LEDS_N0_ON);
		break;

	case 28:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_3_BASE, HEX_ALL_OFF - HEX_N5_ON - HEX_N4_ON - HEX_N2_ON - HEX_N1_ON - HEX_N0_ON);
		break;

	case 29:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_3_BASE, HEX_ALL_OFF - HEX_N5_ON - HEX_N4_ON - HEX_N3_ON - HEX_N2_ON - HEX_N1_ON - HEX_N0_ON);
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_4_BASE, HEX_ALL_OFF - HEX_N5_ON - HEX_N4_ON - HEX_N3_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_N6_ON + LEDS_N5_ON + LEDS_N4_ON + LEDS_N3_ON + LEDS_N2_ON + LEDS_N1_ON + LEDS_N0_ON);
		break;

	case 30:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_4_BASE, HEX_ALL_OFF - HEX_N5_ON - HEX_N4_ON - HEX_N3_ON - HEX_N2_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_N5_ON + LEDS_N4_ON + LEDS_N3_ON + LEDS_N2_ON + LEDS_N1_ON + LEDS_N0_ON);
		break;

	case 31:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_4_BASE, HEX_ALL_OFF - HEX_N5_ON - HEX_N4_ON - HEX_N3_ON - HEX_N2_ON - HEX_N1_ON);
		break;

	case 32:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_4_BASE, HEX_ALL_OFF - HEX_N5_ON - HEX_N4_ON - HEX_N3_ON - HEX_N2_ON - HEX_N1_ON - HEX_N0_ON);
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_5_BASE, HEX_ALL_OFF - HEX_N5_ON - HEX_N0_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_N4_ON + LEDS_N3_ON + LEDS_N2_ON + LEDS_N1_ON + LEDS_N0_ON);
		break;

	case 33:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_5_BASE, HEX_ALL_OFF - HEX_N5_ON - HEX_N1_ON - HEX_N0_ON);
		break;

	case 34:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_5_BASE, HEX_ALL_OFF - HEX_N5_ON - HEX_N2_ON - HEX_N1_ON - HEX_N0_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_N3_ON + LEDS_N2_ON + LEDS_N1_ON + LEDS_N0_ON);
		break;

	case 35:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_5_BASE, HEX_ALL_OFF - HEX_N5_ON - HEX_N3_ON - HEX_N2_ON - HEX_N1_ON - HEX_N0_ON);
		break;

	case 36:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_5_BASE, HEX_ALL_OFF - HEX_N5_ON - HEX_N4_ON - HEX_N3_ON - HEX_N2_ON - HEX_N1_ON - HEX_N0_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_N2_ON + LEDS_N1_ON + LEDS_N0_ON);
		break;

	case 37:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_5_BASE, HEX_ALL_ON);
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_4_BASE, HEX_ALL_ON - HEX_N6_ON);
		break;

	case 38:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_4_BASE, HEX_ALL_ON);
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_3_BASE, HEX_ALL_ON - HEX_N6_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_N1_ON + LEDS_N0_ON);
		break;

	case 39:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_3_BASE, HEX_ALL_ON);
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_2_BASE, HEX_ALL_ON - HEX_N6_ON);
		break;

	case 40:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_2_BASE, HEX_ALL_ON);
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_1_BASE, HEX_ALL_ON - HEX_N6_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_N0_ON);
		break;

	case 41:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_1_BASE, HEX_ALL_ON);
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_0_BASE, HEX_ALL_ON - HEX_N6_ON);
		break;

	case 42:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_0_BASE, HEX_ALL_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_ALL_OFF);
		break;

	case 43:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_0_BASE, HEX_ALL_ON + HEX_N1_ON);
		break;

	case 44:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_0_BASE, HEX_ALL_ON + HEX_N1_ON + HEX_N0_ON);
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_1_BASE, HEX_ALL_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_N0_ON);
		break;

	case 45:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_1_BASE, HEX_ALL_ON + HEX_N1_ON);
		break;

	case 46:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_1_BASE, HEX_ALL_ON + HEX_N1_ON + HEX_N2_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_N1_ON + LEDS_N0_ON);
		break;

	case 47:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_1_BASE, HEX_ALL_ON + HEX_N1_ON + HEX_N2_ON + HEX_N3_ON);
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_2_BASE, HEX_ALL_ON);
		break;

	case 48:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_2_BASE, HEX_ALL_ON + HEX_N2_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_N2_ON + LEDS_N1_ON + LEDS_N0_ON);
		break;

	case 49:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_2_BASE, HEX_ALL_ON + HEX_N2_ON + HEX_N1_ON);
		break;

	case 50:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_2_BASE, HEX_ALL_ON + HEX_N2_ON + HEX_N1_ON + HEX_N0_ON);
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_3_BASE, HEX_ALL_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_N3_ON + LEDS_N2_ON + LEDS_N1_ON + LEDS_N0_ON);
		break;

	case 51:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_3_BASE, HEX_ALL_ON + HEX_N1_ON);
		break;

	case 52:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_3_BASE, HEX_ALL_ON + HEX_N2_ON + HEX_N1_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_N4_ON + LEDS_N3_ON + LEDS_N2_ON + LEDS_N1_ON + LEDS_N0_ON);
		break;

	case 53:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_3_BASE, HEX_ALL_ON + HEX_N3_ON + HEX_N2_ON + HEX_N1_ON);
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_4_BASE, HEX_ALL_ON);
		break;

	case 54:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_4_BASE, HEX_ALL_ON + HEX_N2_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_N5_ON + LEDS_N4_ON + LEDS_N3_ON + LEDS_N2_ON + LEDS_N1_ON + LEDS_N0_ON);
		break;

	case 55:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_4_BASE, HEX_ALL_ON + HEX_N2_ON + HEX_N1_ON);
		break;

	case 56:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_4_BASE, HEX_ALL_ON + HEX_N2_ON + HEX_N1_ON + HEX_N0_ON);
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_5_BASE, HEX_ALL_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_N6_ON + LEDS_N5_ON + LEDS_N4_ON + LEDS_N3_ON + LEDS_N2_ON + LEDS_N1_ON + LEDS_N0_ON);
		break;

	case 57:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_5_BASE, HEX_ALL_ON + HEX_N1_ON);
		break;

	case 58:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_5_BASE, HEX_ALL_ON + HEX_N2_ON + HEX_N1_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_N7_ON + LEDS_N6_ON + LEDS_N5_ON + LEDS_N4_ON + LEDS_N3_ON + LEDS_N2_ON + LEDS_N1_ON + LEDS_N0_ON);
		break;

	case 59:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_5_BASE, HEX_ALL_ON + HEX_N3_ON + HEX_N2_ON + HEX_N1_ON);
		break;

	case 60:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_5_BASE, HEX_ALL_ON + HEX_N4_ON + HEX_N3_ON + HEX_N2_ON + HEX_N1_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_N8_ON + LEDS_N7_ON + LEDS_N6_ON + LEDS_N5_ON + LEDS_N4_ON + LEDS_N3_ON + LEDS_N2_ON + LEDS_N1_ON + LEDS_N0_ON);
		break;

	case 61:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_5_BASE, HEX_ALL_ON + HEX_N5_ON + HEX_N4_ON + HEX_N3_ON + HEX_N2_ON + HEX_N1_ON);
		break;

	case 62:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_5_BASE, HEX_ALL_ON + HEX_N5_ON + HEX_N4_ON + HEX_N3_ON + HEX_N2_ON + HEX_N1_ON + HEX_N0_ON);
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_4_BASE, HEX_ALL_ON + HEX_N2_ON + HEX_N1_ON + HEX_N0_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_ALL_ON);
		break;

	case 63:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_4_BASE, HEX_ALL_ON + HEX_N5_ON + HEX_N2_ON + HEX_N1_ON + HEX_N0_ON);
		break;

	case 64:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_4_BASE, HEX_ALL_ON + HEX_N5_ON + HEX_N4_ON + HEX_N2_ON + HEX_N1_ON + HEX_N0_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_ALL_ON);
		break;

	case 65:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_4_BASE, HEX_ALL_ON + HEX_N5_ON + HEX_N4_ON + HEX_N3_ON + HEX_N2_ON + HEX_N1_ON + HEX_N0_ON);
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_3_BASE, HEX_ALL_ON + HEX_N3_ON + HEX_N2_ON + HEX_N1_ON);
		break;

	case 66:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_3_BASE, HEX_ALL_ON + HEX_N4_ON + HEX_N3_ON + HEX_N2_ON + HEX_N1_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_ALL_ON);
		break;

	case 67:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_3_BASE, HEX_ALL_ON + HEX_N5_ON + HEX_N4_ON + HEX_N3_ON + HEX_N2_ON + HEX_N1_ON);
		break;

	case 68:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_3_BASE, HEX_ALL_ON + HEX_N5_ON + HEX_N4_ON + HEX_N3_ON + HEX_N2_ON + HEX_N1_ON + HEX_N0_ON);
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_2_BASE, HEX_ALL_ON + HEX_N2_ON + HEX_N1_ON + HEX_N0_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_N9_ON + LEDS_N8_ON + LEDS_N7_ON + LEDS_N6_ON + LEDS_N5_ON + LEDS_N4_ON + LEDS_N3_ON + LEDS_N2_ON + LEDS_N1_ON);
		break;

	case 69:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_2_BASE, HEX_ALL_ON + HEX_N5_ON + HEX_N2_ON + HEX_N1_ON + HEX_N0_ON);
		break;

	case 70:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_2_BASE, HEX_ALL_ON + HEX_N5_ON + HEX_N4_ON + HEX_N2_ON + HEX_N1_ON + HEX_N0_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_N9_ON + LEDS_N8_ON + LEDS_N7_ON + LEDS_N6_ON + LEDS_N5_ON + LEDS_N4_ON + LEDS_N3_ON + LEDS_N2_ON);
		break;

	case 71:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_2_BASE, HEX_ALL_ON + HEX_N5_ON + HEX_N4_ON + HEX_N3_ON + HEX_N2_ON + HEX_N1_ON + HEX_N0_ON);
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_1_BASE, HEX_ALL_ON + HEX_N3_ON + HEX_N2_ON + HEX_N1_ON);
		break;

	case 72:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_1_BASE, HEX_ALL_ON + HEX_N4_ON + HEX_N3_ON + HEX_N2_ON + HEX_N1_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_N9_ON + LEDS_N8_ON + LEDS_N7_ON + LEDS_N6_ON + LEDS_N5_ON + LEDS_N4_ON + LEDS_N3_ON);
		break;

	case 73:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_1_BASE, HEX_ALL_ON + HEX_N5_ON + HEX_N4_ON + HEX_N3_ON + HEX_N2_ON + HEX_N1_ON);
		break;

	case 74:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_1_BASE, HEX_ALL_ON + HEX_N5_ON + HEX_N4_ON + HEX_N3_ON + HEX_N2_ON + HEX_N1_ON + HEX_N0_ON);
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_0_BASE, HEX_ALL_ON + HEX_N1_ON + HEX_N0_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_N9_ON + LEDS_N8_ON + LEDS_N7_ON + LEDS_N6_ON + LEDS_N5_ON + LEDS_N4_ON);
		break;

	case 75:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_0_BASE, HEX_ALL_ON + HEX_N5_ON + HEX_N1_ON + HEX_N0_ON);
		break;

	case 76:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_0_BASE, HEX_ALL_ON + HEX_N5_ON + HEX_N4_ON + HEX_N1_ON + HEX_N0_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_N9_ON + LEDS_N8_ON + LEDS_N7_ON + LEDS_N6_ON + LEDS_N5_ON);
		break;

	case 77:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_0_BASE, HEX_ALL_ON + HEX_N5_ON + HEX_N4_ON + HEX_N3_ON + HEX_N1_ON + HEX_N0_ON);
		break;

	case 78:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_0_BASE, HEX_ALL_ON + HEX_N5_ON + HEX_N4_ON + HEX_N3_ON + HEX_N2_ON + HEX_N1_ON + HEX_N0_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_N9_ON + LEDS_N8_ON + LEDS_N7_ON + LEDS_N6_ON);
		break;

	case 79:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_0_BASE, HEX_ALL_OFF);
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_1_BASE, HEX_ALL_OFF - HEX_N6_ON);
		break;

	case 80:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_1_BASE, HEX_ALL_OFF);
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_2_BASE, HEX_ALL_OFF - HEX_N6_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_N9_ON + LEDS_N8_ON + LEDS_N7_ON);
		break;

	case 81:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_2_BASE, HEX_ALL_OFF);
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_3_BASE, HEX_ALL_OFF - HEX_N6_ON);
		break;

	case 82:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_3_BASE, HEX_ALL_OFF);
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_4_BASE, HEX_ALL_OFF - HEX_N6_ON);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_N9_ON + LEDS_N8_ON);
		break;

	case 83:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_4_BASE, HEX_ALL_OFF);
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_5_BASE, HEX_ALL_OFF - HEX_N6_ON);
		break;

	case 84:
		alt_write_word(AXIBRIDGE_BASE_ADDR + HEX_5_BASE, HEX_ALL_OFF);

		alt_write_hword(AXIBRIDGE_BASE_ADDR + LEDS_0_BASE, LEDS_N9_ON);
		break;
	}
}


