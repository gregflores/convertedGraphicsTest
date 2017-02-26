/*
 * main.c
 *
 *  Created on: Feb 25, 2016
 *      Author: Gregorio Flores
 */
#include "msp.h"
#include "driverlib.h"
#include "color.h"
#include "graphics.h"
#include "lcd.h"
//#include "tests.h"
#include <stdint.h>
#include <stdio.h>
#include "HAL_MSP432_320x240_ILI9341.h"

//uint8_t orientation = 2;

void main(void)
{

	/* Halting WDT and disabling master interrupts */
    MAP_WDT_A_holdTimer();
    MAP_Interrupt_disableMaster();

    /* Set the core voltage level to VCORE1
    MAP_PCM_setCoreVoltageLevel(PCM_VCORE1);

    // Set 2 flash wait states for Flash bank 0 and 1
    MAP_FlashCtl_setWaitState(FLASH_BANK0, 2);
    MAP_FlashCtl_setWaitState(FLASH_BANK1, 2);

    // Initializes Clock System
    MAP_CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);
    MAP_CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1 );
    MAP_CS_initClockSignal(CS_HSMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1 );
    MAP_CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1 );
    MAP_CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    */
    FPU_enableModule();
    FlashCtl_setWaitState(FLASH_BANK0, 2);
    FlashCtl_setWaitState(FLASH_BANK1, 2);
    PCM_setPowerState(PCM_AM_DCDC_VCORE1);
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);
    CS_setDCOFrequency(48000000);
    CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_HSMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    MAP_CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);

	HAL_LCD_SpiInit();
	_delay_cycles(160000);
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

	drawString(28, 34, FONT_MD, "FWD: 000W RVS: 000W");
	drawString(28, 50, FONT_MD, "FWD: 000W RVS: 000W");
	drawString(28, 66, FONT_MD, "FWD: 000W RVS: 000W");
	drawString(28, 82, FONT_MD, "FWD: 000W RVS: 000W");
	drawString(28, 98, FONT_MD, "FWD: 000W RVS: 000W");
	drawString(28, 114, FONT_MD, "FWD: 000W RVS: 000W");
	drawString(28, 130, FONT_MD, "FWD: 000W RVS: 000W");
	drawString(28, 146, FONT_MD, "FWD: 000W RVS: 000W");
	drawString(28, 162, FONT_MD, "FWD: 000W RVS: 000W");
	drawString(28, 178, FONT_MD, "FWD: 000W RVS: 000W");


	//Counting variables for the for loops
	uint16_t i, j;

	//Activity flag. 0 is inactive, 1 is active.
	int16_t activity = 0;

	//Forward and reverse power int values. The fwd_temp and rvs_temp chars are for converting the ints
	//and displaying the values on the LCD
	uint16_t fwd[10];
	uint16_t rvs[10];
	int8_t fwd_temp[] = "";
	int8_t rvs_temp[] = "";

	//Inside and outside temperature variables. the insideTempC and outsideTempC are for converting and displaying
	int16_t insideTemp, outsideTemp;
	int8_t insideTempC[] = "", outsideTempC[] = "";

	//IP value to display the 4 numbers on the screen
	int16_t ipAddress[4] = {255, 255, 255, 255};
	int8_t ipAddress_temp[] = "";

	/* === while === */
	while (1)
	{

		/*switch*/
		switch(activity)
		{
		case 0:
			drawString(188, 34, FONT_MD_BKG, "INACTIVE");
			drawString(188, 50, FONT_MD_BKG, "INACTIVE");
			drawString(188, 66, FONT_MD_BKG, "INACTIVE");
			drawString(188, 82, FONT_MD_BKG, "INACTIVE");
			drawString(188, 98, FONT_MD_BKG, "INACTIVE");
			drawString(188, 114, FONT_MD_BKG, "INACTIVE");
			drawString(188, 130, FONT_MD_BKG, "INACTIVE");
			drawString(188, 146, FONT_MD_BKG, "INACTIVE");
			drawString(188, 162, FONT_MD_BKG, "INACTIVE");
			drawString(188, 178, FONT_MD_BKG, "INACTIVE");
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
			activity = 1;
			break;
		case 1:
			drawString(188, 34, FONT_MD_BKG, "  ACTIVE");
			drawString(188, 50, FONT_MD_BKG, "  ACTIVE");
			drawString(188, 66, FONT_MD_BKG, "  ACTIVE");
			drawString(188, 82, FONT_MD_BKG, "  ACTIVE");
			drawString(188, 98, FONT_MD_BKG, "  ACTIVE");
			drawString(188, 114, FONT_MD_BKG, "  ACTIVE");
			drawString(188, 130, FONT_MD_BKG, "  ACTIVE");
			drawString(188, 146, FONT_MD_BKG, "  ACTIVE");
			drawString(188, 162, FONT_MD_BKG, "  ACTIVE");
			drawString(188, 178, FONT_MD_BKG, "  ACTIVE");
			setColor(COLOR_16_GREEN);
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
			activity = 0;
			break;
		default:
			break;
		} /*switch*/

		for (i = 0; i < 256; i++)
		{
			for (j = 0; j < 10; j++)
				{
					fwd[j] = i;
					rvs[j] = 255-i;
				}

			ipAddress[0] = i;
			ipAddress[1] = 255-i;
			ipAddress[2] = i;
			ipAddress[3] = 255-i;
			sprintf((char*)ipAddress_temp, "%.3u", ipAddress[0]);
			drawString(196, 210, FONT_MD_BKG, ipAddress_temp);
			sprintf((char*)ipAddress_temp, "%.3u", ipAddress[1]);
			drawString(228, 210, FONT_MD_BKG, ipAddress_temp);
			sprintf((char*)ipAddress_temp, "%.3u", ipAddress[2]);
			drawString(260, 210, FONT_MD_BKG, ipAddress_temp);
			sprintf((char*)ipAddress_temp, "%.3u", ipAddress[3]);
			drawString(292, 210, FONT_MD_BKG, ipAddress_temp);

			insideTemp = i;
			outsideTemp = 255-i;
			sprintf((char*)insideTempC, "%.3u", insideTemp);
			drawString(116, 210, FONT_MD_BKG, insideTempC);
			sprintf((char*)outsideTempC, "%.3u", outsideTemp);
			drawString(116, 226, FONT_MD_BKG, outsideTempC);

			sprintf((char*)fwd_temp, "%.3u", fwd[0]);
			drawString(68, 34, FONT_MD_BKG, fwd_temp);
			sprintf((char*)fwd_temp, "%.3u", fwd[1]);
			drawString(68, 50, FONT_MD_BKG, fwd_temp);
			sprintf((char*)fwd_temp, "%.3u", fwd[2]);
			drawString(68, 66, FONT_MD_BKG, fwd_temp);
			sprintf((char*)fwd_temp, "%.3u", fwd[3]);
			drawString(68, 82, FONT_MD_BKG, fwd_temp);
			sprintf((char*)fwd_temp, "%.3u", fwd[4]);
			drawString(68, 98, FONT_MD_BKG, fwd_temp);
			sprintf((char*)fwd_temp, "%.3u", fwd[5]);
			drawString(68, 114, FONT_MD_BKG, fwd_temp);
			sprintf((char*)fwd_temp, "%.3u", fwd[6]);
			drawString(68, 130, FONT_MD_BKG, fwd_temp);
			sprintf((char*)fwd_temp, "%.3u", fwd[7]);
			drawString(68, 146, FONT_MD_BKG, fwd_temp);
			sprintf((char*)fwd_temp, "%.3u", fwd[8]);
			drawString(68, 162, FONT_MD_BKG, fwd_temp);
			sprintf((char*)fwd_temp, "%.3u", fwd[9]);
			drawString(68, 178, FONT_MD_BKG, fwd_temp);

			sprintf((char*)rvs_temp, "%.3u", rvs[0]);
			drawString(148, 34, FONT_MD_BKG, rvs_temp);
			sprintf((char*)rvs_temp, "%.3u", rvs[1]);
			drawString(148, 50, FONT_MD_BKG, rvs_temp);
			sprintf((char*)rvs_temp, "%.3u", rvs[2]);
			drawString(148, 66, FONT_MD_BKG, rvs_temp);
			sprintf((char*)rvs_temp, "%.3u", rvs[3]);
			drawString(148, 82, FONT_MD_BKG, rvs_temp);
			sprintf((char*)rvs_temp, "%.3u", rvs[4]);
			drawString(148, 98, FONT_MD_BKG, rvs_temp);
			sprintf((char*)rvs_temp, "%.3u", rvs[5]);
			drawString(148, 114, FONT_MD_BKG, rvs_temp);
			sprintf((char*)rvs_temp, "%.3u", rvs[6]);
			drawString(148, 130, FONT_MD_BKG, rvs_temp);
			sprintf((char*)rvs_temp, "%.3u", rvs[7]);
			drawString(148, 146, FONT_MD_BKG, rvs_temp);
			sprintf((char*)rvs_temp, "%.3u", rvs[8]);
			drawString(148, 162, FONT_MD_BKG, rvs_temp);
			sprintf((char*)rvs_temp, "%.3u", rvs[9]);
			drawString(148, 178, FONT_MD_BKG, rvs_temp);
		}
	}/* === while === */
}

