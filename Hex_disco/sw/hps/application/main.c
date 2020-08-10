/*
 * main.c
 *
 *  Created on: Jan 12, 2020
 *      Author: Tijntj3
 */

/* Instructions
 * - When all switches are at the bottom position the default animation will play
 * - When only switch 0 is switched on, the animation will pause and can be controlled
 *   with button 3 (return 1 animation step) and button 2 (advance 1 animation step)
 * - When only switch 1 is switched on the animation will play 10 times slower than the default speed
 * - When only switch 2 is switched on the animation will play 10 times faster than the default speed
 * - As an easter egg, when switches 0,1 and 2 are switched up, the animations is reversed at default speed
 * - Any other switch combination will just play the default animation at default speed
 */

//Library references
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//Header files
#include "socal/socal.h"
#include "hps_soc_system.h"
#include "hexDisco.h"
#include "switches.h"

//Globals
unsigned int prevSwVal = 0x0;

//Loop
int main()
{
	if(hexDiscoInit() == ALT_E_ERROR)
	{
		printf("Could not complete hex setup\n");
		return -1;
	}
	else printf("Hex setup complete\n");

	while(true)
	{
		int swVal = alt_read_hword(AXIBRIDGE_BASE_ADDR + SWITCHES_0_BASE);

		if(swVal!=prevSwVal)
		{
			switch(swVal)
			{
			default:
				setModeHexDisco(defaultMode);
				break;
			case SWITCH_N0_ON:
				setModeHexDisco(pauseMode);
				break;
			case SWITCH_N1_ON:
				setModeHexDisco(slowMode);
				break;
			case SWITCH_N2_ON:
				setModeHexDisco(fastMode);
				break;
			case SWITCH_N0_ON + SWITCH_N1_ON + SWITCH_N2_ON:
				setModeHexDisco(reverseMode);
			}
		}

		if(isFunkyTime())
		{
			updateHexDisco();
		}

		prevSwVal = swVal;
	}
}
