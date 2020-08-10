/*
 * buttons.c
 *
 *  Created on: Jan 18, 2020
 *      Author: Tijntj3
 */

//Library references
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//Header files
#include "hps_soc_system.h"
#include "socal/socal.h"
#include "buttons.h"

int prevStateBut = BUTTON_ALL_OFF;

enum buttons debBut()
{
	enum buttons status = notDebounced;
	int stateBut = alt_read_hword(AXIBRIDGE_BASE_ADDR + BUTTONS_0_BASE);

	if(stateBut!=prevStateBut)
	{
		switch(stateBut)
		{
		default:
			break;
		case BUTTON_N0_ON:
			status = button0;
			break;
		case BUTTON_N1_ON:
			status = button1;
			break;
		case BUTTON_N2_ON:
			status = button2;
			break;
		case BUTTON_N3_ON:
			status = button3;
			break;
		}
	}

	prevStateBut = stateBut;

	return status;
}
