/*
 * tests.c
 *
 *  Created on: Sep 11, 2014
 *      Author: RobG
 */

#include "graphics.h"
#include "lcd.h"
#include <stdint.h>
#include "tests.h"
#include <Math.h>

extern const unsigned int colors[];

uint16_t cc = 0;
uint16_t sx = 0;
uint16_t sy = 0;
uint16_t d = 0;
uint16_t o = 0;
uint16_t yo = 140;

const uint16_t starty[13] = { 30, 48, 150, 50, 40, 85, 38, 105, 66, 130, 35, 71,
		117 };
const uint16_t startx[17] = { 180, 30, 100, 96, 48, 50, 150, 70, 40, 38, 123, 132,
		80, 35, 110, 55, 99 };
const uint8_t dim[9] = { 20, 14, 5, 17, 10, 5, 3, 18, 12 };
const uint8_t offset[10] = { 6, 4, 1, 9, 7, 2, 8, 0, 3, 5 };

const uint8_t ti1[10] = { 94, 36, 109, 36, 97, 92, 82, 92, 94, 36 };
const uint8_t ti2[82] = { 0, 58, 41, 58, 41, 0, 80, 0, 80, 25, 88, 28, 84, 47,
		72, 47, 68, 65, 80, 65, 76, 84, 75, 95, 76, 103, 82, 110, 94, 112, 110,
		107, 115, 93, 106, 93, 104, 90, 110, 65, 122, 65, 126, 47, 114, 47, 118,
		29, 148, 32, 148, 54, 156, 65, 154, 95, 130, 106, 116, 120, 111, 134,
		114, 149, 98, 150, 80, 138, 62, 104, 54, 97, 46, 99, 38, 106, 30, 104,
		20, 88, 0, 58 };

///////////////////////////
// TI Logo
///////////////////////////
void drawTILogo(uint16_t x, uint16_t y, uint16_t color) {
	uint8_t sx = 0;
	uint8_t sy = 0;
	uint16_t ax = 0;
	uint16_t ay = 0;
	setColor(color);
	drawCircle(105 + x, 23 + y, 8);
	uint8_t i = 0;
	sx = ti1[i++] + x;
	sy = ti1[i++] + y;
	while (i < 10) {
		ax = ti1[i++] + x;
		ay = ti1[i++] + y;
		drawLine(sx, sy, ax, ay);
		sx = ax;
		sy = ay;
	}
	i = 0;
	sx = ti2[i++] + x;
	sy = ti2[i++] + y;
	while (i < 82) {
		ax = ti2[i++] + x;
		ay = ti2[i++] + y;
		drawLine(sx, sy, ax, ay);
		sx = ax;
		sy = ay;
	}
}


///////////////////////////
//
///////////////////////////

///////////////////////////
//
///////////////////////////
void drawLogicLines(uint8_t h) {
	uint8_t * addr = 0;
	addr += 0x1C00;
	uint16_t y = 0;
	uint8_t c = 1;
	while (y < getScreenHeight()) {
		setColor(colors[c]);
		drawLogicLine(1, y, getScreenWidth(), h, (uint8_t*) addr);
		y += (h + 2);
		c++;
		addr += getScreenWidth();
	}
}

uint16_t getColor() {
	cc++;
	if (cc == 43)
		cc = 0;
	return colors[cc];
}

uint16_t getX() {
	sx++;
	if (sx == 17)
		sx = 0;
	return startx[sx];
}

uint16_t getY() {
	sy++;
	if (sy == 13)
		sy = 0;
	return starty[sy] + yo;
}

uint8_t getD() {
	d++;
	if (d == 9)
		d = 0;
	return dim[d];
}

uint8_t getO() {
	o++;
	if (o == 10)
		o = 0;
	return offset[o];
}

void shesGotColors(uint16_t times) {

	uint16_t x;
	uint16_t y;
	uint8_t d;
	uint16_t repeatTimes = times;

	while (repeatTimes > 0) {
		setColor(getColor());
		x = getX();
		y = getY();
		d = getD();
		drawLine(x - d - getO(), y - d - getO(), x + d + getO(),
				y + d + getO());

		setColor(getColor());
		x = getX();
		y = getY();
		d = getD();
		fillRect(x - d - getO(), y - d - getO(), x + d + getO(),
				y + d + getO());

		setColor(getColor());
		x = getX();
		y = getY();
		d = getD();
		drawRect(x - d - getO(), y - d - getO(), x + d + getO(),
				y + d + getO());

		setColor(getColor());
		x = getX();
		y = getY();
		d = getD();
		fillCircle(x, y, d + getO());

		setColor(getColor());
		x = getX();
		y = getY();
		d = getD();
		drawLine(x - d - getO(), y + d + getO(), x + d + getO(),
				y - d - getO());

		setColor(getColor());
		x = getX();
		y = getY();
		d = getD();
		drawCircle(x, y, d + getO());

		repeatTimes--;
	}
}
/////////////////////////////////////////
// end of test
/////////////////////////////////////////
