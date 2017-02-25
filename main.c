/*
 * main.c
 *
 *  Created on: Sep 15, 2014
 *      Author: RobG
 */
#include "msp.h"
#include "driverlib.h"
#include "color.h"
#include "graphics.h"
#include "lcd.h"
#include "tests.h"
#include <stdint.h>

#include "HAL_MSP432_320x240_ILI9341.h"

//uint8_t orientation = 2;

void main(void) {

	/* Halting WDT and disabling master interrupts */
    MAP_WDT_A_holdTimer();
    MAP_Interrupt_disableMaster();

    /* Set the core voltage level to VCORE1 */
    MAP_PCM_setCoreVoltageLevel(PCM_VCORE1);

    /* Set 2 flash wait states for Flash bank 0 and 1*/
    MAP_FlashCtl_setWaitState(FLASH_BANK0, 2);
    MAP_FlashCtl_setWaitState(FLASH_BANK1, 2);

    /* Initializes Clock System */
    MAP_CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);
    MAP_CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1 );
    MAP_CS_initClockSignal(CS_HSMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1 );
    MAP_CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1 );
    MAP_CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);

    HAL_LCD_SpiInit();

	_delay_cycles(160000); // wait

	initLCD();

	clearScreen(1);
	//setColor(COLOR_16_NAVY);
	//fillRect(0,0,getScreenWidth() - 1, getScreenHeight() - 1);

	setColor(COLOR_16_WHITE);

	drawString(4, 2, FONT_MD, "MEGAHERTZ");
	drawString(236, 2, FONT_MD, "GIRAF Tech");

	drawString(4, 34, FONT_MD, " 1");
	drawString(4, 50, FONT_MD, " 2");
	drawString(4, 66, FONT_MD, " 3");
	drawString(4, 82, FONT_MD, " 4");
	drawString(4, 98, FONT_MD, " 5");
	drawString(4, 114, FONT_MD, " 6");
	drawString(4, 130, FONT_MD, " 7");
	drawString(4, 146, FONT_MD, " 8");
	drawString(4, 162, FONT_MD, " 9");
	drawString(4, 178, FONT_MD, "10");

	drawString(4, 210, FONT_MD, "TEMP  Inside:");
	drawString(116, 210, FONT_MD, "000F");
	drawString(4, 226, FONT_MD, "TEMP Outside:");
	drawString(116, 226, FONT_MD, "000F");

	drawString(156, 210, FONT_MD, " IP: 255.255.255.255");
	drawString(156, 226, FONT_MD, "Web: GIRAFTECH.XYZ");

	drawString(28, 34, FONT_MD, "FWD: 000W RVS: 000W INACTIVE");
	drawString(28, 50, FONT_MD, "FWD: 000W RVS: 000W INACTIVE");
	drawString(28, 66, FONT_MD, "FWD: 000W RVS: 000W INACTIVE");
	drawString(28, 82, FONT_MD, "FWD: 000W RVS: 000W INACTIVE");
	drawString(28, 98, FONT_MD, "FWD: 000W RVS: 000W INACTIVE");
	drawString(28, 114, FONT_MD, "FWD: 000W RVS: 000W INACTIVE");
	drawString(28, 130, FONT_MD, "FWD: 000W RVS: 000W INACTIVE");
	drawString(28, 146, FONT_MD, "FWD: 000W RVS: 000W INACTIVE");
	drawString(28, 162, FONT_MD, "FWD: 000W RVS: 000W INACTIVE");
	drawString(28, 178, FONT_MD, "FWD: 000W RVS: 000W INACTIVE");

	setColor(COLOR_16_RED);
	fillCircle(263, 39, 4);
	fillCircle(263, 55, 4);
	fillCircle(263, 71, 4);
	fillCircle(263, 87, 4);
	fillCircle(263, 103, 4);
	fillCircle(263, 119, 4);
	fillCircle(263, 135, 4);
	fillCircle(263, 151, 4);
	fillCircle(263, 167, 4);
	fillCircle(263, 183, 4);
	setColor(COLOR_16_WHITE);

	while (1) {
		drawString(68, 34, FONT_MD_BKG, "001");
		drawString(68, 50, FONT_MD_BKG, "001");
		drawString(68, 66, FONT_MD_BKG, "001");
		drawString(68, 82, FONT_MD_BKG, "001");
		drawString(68, 98, FONT_MD_BKG, "001");
		drawString(68, 114, FONT_MD_BKG, "001");
		drawString(68, 130, FONT_MD_BKG, "001");
		drawString(68, 146, FONT_MD_BKG, "001");
		drawString(68, 162, FONT_MD_BKG, "001");
		drawString(68, 178, FONT_MD_BKG, "001");
	}

}

