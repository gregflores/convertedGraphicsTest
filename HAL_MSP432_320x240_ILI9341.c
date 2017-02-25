/*
 * mcuLCD.c
 *
 *  Created on: Feb 19, 2017
 *      Author: Gregorio Flores
 */
#include "HAL_MSP432_320x240_ILI9341.h"

#include "msp.h"
#include "lcd.h"
#include "config.h"
#include "driverlib.h"
void HAL_LCD_SpiInit()
{

    MAP_GPIO_setAsOutputPin(LCD_DC_PORT,
                        LCD_DC_PIN);

    MAP_GPIO_setOutputLowOnPin(LCD_DC_PORT,
                           LCD_DC_PIN);

    MAP_GPIO_setAsOutputPin(LCD_CS_PORT,
                        LCD_CS_PIN);

    MAP_GPIO_setOutputLowOnPin(LCD_CS_PORT,
                           LCD_CS_PIN);
    //
    // Configure SPI peripheral.
    //
	MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(LCD_MOSI_PORT,
                                                LCD_MOSI_PIN,
                                                GPIO_PRIMARY_MODULE_FUNCTION);

	MAP_GPIO_setAsPeripheralModuleFunctionInputPin(LCD_MISO_PORT,
                                                LCD_MISO_PIN,
												GPIO_PRIMARY_MODULE_FUNCTION);

	MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(LCD_SCLK_PORT,
    											LCD_SCLK_PIN,
												GPIO_PRIMARY_MODULE_FUNCTION);

    eUSCI_SPI_MasterConfig spiMasterConfig =
    {
        EUSCI_SPI_CLOCKSOURCE_SMCLK,                      		// SMCLK Clock Source
        MAP_CS_getSMCLK(),                                  			// Get SMCLK frequency
        16000000,                                                	// SPICLK = 16 MHz
        EUSCI_SPI_MSB_FIRST,                             			// MSB First
		EUSCI_SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT, 	// Phase //  EUSCI_B_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT
        EUSCI_SPI_CLOCKPOLARITY_INACTIVITY_LOW,         			// Low polarity
		EUSCI_SPI_3PIN                                   			// SPI Mode
    };

    SPI_initMaster(EUSCI_B0_BASE, &spiMasterConfig);
    SPI_enableModule(EUSCI_B0_BASE);

    SPI_clearInterruptFlag(EUSCI_B0_BASE,  EUSCI_B_SPI_RECEIVE_INTERRUPT);
}


void writeData(uint8_t data)
{
    // USCI_B0 Busy? //
    while (UCB0STATW & UCBUSY);

    // Transmit data
    UCB0TXBUF = data;
}


void writeCommand(uint8_t command)
{
    // Set to command mode
    GPIO_setOutputLowOnPin(LCD_DC_PORT, LCD_DC_PIN);

    // USCI_B0 Busy? //
    while (UCB0STATW & UCBUSY);

    // Transmit data
    UCB0TXBUF = command;

    // Set back to data mode
    GPIO_setOutputHighOnPin(LCD_DC_PORT, LCD_DC_PIN);
}


void delay(uint8_t x10ms)
{
	while (x10ms > 0)
	{
		_delay_cycles(160000);
		x10ms--;
	}
}
