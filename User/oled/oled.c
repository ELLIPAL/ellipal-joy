#include "oled.h"

#include "includes.h"
#include "oledfont.h"

uint8_t OLED_GRAM[96][12];

// Turn function
void OLED_ColorTurn(uint8_t i) {
	if (i == 0) {
		OLED_WR_Byte(0xA6, OLED_CMD);  // normal display
	}
	if (i == 1) {
		OLED_WR_Byte(0xA7, OLED_CMD);  // Inverted color display
	}
}

// Rotate the screen 180 degrees
void OLED_DisplayTurn(uint8_t i) {
	if (i == 0) {
		OLED_WR_Byte(0xC0, OLED_CMD);  // reverse display
		OLED_WR_Byte(0xA1, OLED_CMD);
	}
	if (i == 1) {
		OLED_WR_Byte(0xC8, OLED_CMD);  // normal display
		OLED_WR_Byte(0xA0, OLED_CMD);
	}
}

void OLED_Contract(uint8_t i) {
	OLED_WR_Byte(0x81, OLED_CMD);
	OLED_WR_Byte(i, OLED_CMD);
}

void OLED_WR_Byte(uint8_t dat, uint8_t cmd) {
	uint8_t i;

	if (cmd)
		OLED_DC_Set();
	else
		OLED_DC_Clr();
	OLED_CS_Clr();
	for (i = 0; i < 8; i++) {
		OLED_SCL_Clr();
		if (dat & 0x80)
			OLED_SDA_Set();
		else
			OLED_SDA_Clr();
		OLED_SCL_Set();
		dat <<= 1;
	}
	OLED_CS_Set();
	OLED_DC_Set();
}

// OLED ON
void OLED_DisPlay_On(void) {
	OLED_WR_Byte(0x8D, OLED_CMD);  // Charge Pump Enable
	OLED_WR_Byte(0x14, OLED_CMD);  // Charge Pump On
	OLED_WR_Byte(0xAF, OLED_CMD);  // light up the screen
}

// OLED OFF
void OLED_DisPlay_Off(void) {
	OLED_WR_Byte(0x8D, OLED_CMD);  // Charge Pump Enable
	OLED_WR_Byte(0x10, OLED_CMD);  // Charge Pump On
	OLED_WR_Byte(0xAE, OLED_CMD);  // Turn off the screen
}

// Update Video Memory to OLED
void OLED_Refresh(void) {
	uint8_t i, n;
	for (i = 0; i < 12; i++) {
		OLED_WR_Byte(0xb0 + i, OLED_CMD);  // Set line start address
		OLED_WR_Byte(0x00, OLED_CMD);      // Set low column start address
		OLED_WR_Byte(0x11, OLED_CMD);      // Set high column start address
		for (n = 0; n < 96; n++) {
			OLED_WR_Byte(OLED_GRAM[n][i], OLED_DATA);
		}
	}
}

// Clear Screen Function
void OLED_ClearScreen(void) {
	uint8_t i, n;
	for (i = 0; i < 12; i++) {
		OLED_WR_Byte(0xb0 + i, OLED_CMD);  // Set line start address
		OLED_WR_Byte(0x00, OLED_CMD);      // Set low column start address
		OLED_WR_Byte(0x11, OLED_CMD);      // Set high column start address
		for (n = 0; n < 96; n++) {
			OLED_WR_Byte(0, OLED_DATA);
		}
	}
}

void OLED_ClearGram(void) {
	uint8_t i, n;
	for (i = 0; i < 12; i++) {
		for (n = 0; n < 96; n++) {
			OLED_GRAM[n][i] = 0;  // clear all data
		}
	}
}

// Draw Point
// x:0~127
// y:0~63
// t:1 Filling  0,Empty
void OLED_DrawPoint(uint8_t x, uint8_t y, uint8_t t) {
	uint8_t i, m, n, tx, ty;

	tx = x;
	ty = y;
	x = 95 - ty;
	y = tx;

	i = y / 8;
	m = y % 8;
	n = 1 << m;

	if (t) {
		OLED_GRAM[x][i] |= n;
	} else {
		OLED_GRAM[x][i] = ~OLED_GRAM[x][i];
		OLED_GRAM[x][i] |= n;
		OLED_GRAM[x][i] = ~OLED_GRAM[x][i];
	}
}

uint8_t OLED_GetPoint(uint8_t x, uint8_t y) {
	uint8_t i, m;
	i = y / 8;
	m = y % 8;
	return (OLED_GRAM[x][i] >> (8 - m)) & 0x01;
}

// Draw Line
// x1,y1:star coordinate
// x2,y2:end coordinate
void OLED_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t mode) {
	uint16_t t;
	int xerr = 0, yerr = 0, delta_x, delta_y, distance;
	int incx, incy, uRow, uCol;
	delta_x = x2 - x1 + 1; // Calculate the coordinate increment
	delta_y = y2 - y1 + 1;
	uRow = x1; // Line drawing starting coordinates
	uCol = y1;
	if (delta_x > 0)
		incx = 1;  // Set step direction
	else if (delta_x == 0)
		incx = 0;  // Vertical line
	else {
		incx = -1;
		delta_x = -delta_x;
	}
	if (delta_y > 0)
		incy = 1;
	else if (delta_y == 0)
		incy = 0;  // horizontal line
	else {
		incy = -1;
		delta_y = -delta_x;
	}
	if (delta_x > delta_y)
		distance = delta_x;  // Choose the base incremental axis
	else
		distance = delta_y;
	for (t = 0; t < distance + 1; t++) {
		OLED_DrawPoint(uRow, uCol, mode);  // draw point
		xerr += delta_x;
		yerr += delta_y;
		if (xerr > distance) {
			xerr -= distance;
			uRow += incx;
		}
		if (yerr > distance) {
			yerr -= distance;
			uCol += incy;
		}
	}
}
// x,y:Center coordinates
// r: the radius of the circle
void OLED_DrawCircle(uint8_t x, uint8_t y, uint8_t r) {
	int a, b, num;
	a = 0;
	b = r;
	while (2 * b * b >= r * r) {
		OLED_DrawPoint(x + a, y - b, 1);
		OLED_DrawPoint(x - a, y - b, 1);
		OLED_DrawPoint(x - a, y + b, 1);
		OLED_DrawPoint(x + a, y + b, 1);

		OLED_DrawPoint(x + b, y + a, 1);
		OLED_DrawPoint(x + b, y - a, 1);
		OLED_DrawPoint(x - b, y - a, 1);
		OLED_DrawPoint(x - b, y + a, 1);

		a++;
		num = (a * a + b * b) - r * r; // Calculate the distance of the drawn point from the center of the circle
		if (num > 0) {
			b--;
			a--;
		}
	}
}

// Display a character at the specified position, including some characters
// x:0~127
// y:0~63
// size1:Font 6x8/6x12/8x16/12x24
// mode:0,Inverted display;1,normal display
void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t size1,
		uint8_t mode) {
	uint8_t i, m, temp, size2, chr1;
	uint8_t x0 = x, y0 = y;
	if (size1 == 8)
		size2 = 6;
	else
		size2 = (size1 / 8 + ((size1 % 8) ? 1 : 0)) * (size1 / 2); // Get the number of bytes occupied by the dot matrix set corresponding to a character of the font
	chr1 = chr - ' ';       // Calculate the offset value
	for (i = 0; i < size2; i++) {
		if (size1 == 8) { // call 0806 font
			temp = asc2_0806[chr1][i];
		} else if (size1 == 12) { // call 1206 font
			temp = asc2_1206[chr1][i];
		} else if (size1 == 16) { // call 1608 font
			temp = asc2_1608[chr1][i];
		} else if (size1 == 24) { // call 2412字体
			temp = asc2_2412[chr1][i];
		} else
			return;
		for (m = 0; m < 8; m++) {
			if (temp & 0x01)
				OLED_DrawPoint(x, y, mode);
			else
				OLED_DrawPoint(x, y, !mode);
			temp >>= 1;
			y++;
		}
		x++;
		if ((size1 != 8) && ((x - x0) == size1 / 2)) {
			x = x0;
			y0 = y0 + 8;
		}
		y = y0;
	}
}

// show string
// x,y: starting coordinates
// size1: font size
// chr: string starting address
// mode:0,Inverted display; 1, normal display
void OLED_ShowString(uint8_t x, uint8_t y, uint8_t *chr, uint8_t size1,
		uint8_t mode) {
	while ((*chr >= ' ') && (*chr <= '~')) // Determine whether it is an illegal character
	{
		OLED_ShowChar(x, y, *chr, size1, mode);
		if (size1 == 8)
			x += 6;
		else
			x += size1 / 2;
		chr++;
	}
}

// m^n
uint32_t OLED_Pow(uint8_t m, uint8_t n) {
	uint32_t result = 1;
	while (n--) {
		result *= m;
	}
	return result;
}

// show num
// x,y : starting coordinates
// num : number to show
// len : number of digits
// size: font size
// mode:0,Inverted display; 1, normal display
void OLED_ShowNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len,
		uint8_t size1, uint8_t mode) {
	uint8_t t, temp, m = 0;
	if (size1 == 8)
		m = 2;
	for (t = 0; t < len; t++) {
		temp = (num / OLED_Pow(10, len - t - 1)) % 10;
		if (temp == 0) {
			OLED_ShowChar(x + (size1 / 2 + m) * t, y, '0', size1, mode);
		} else {
			OLED_ShowChar(x + (size1 / 2 + m) * t, y, temp + '0', size1, mode);
		}
	}
}

// Show Picture
// x,y：starting coordinates
// sizex,sizey, picture length and width
// BMP[]：array of images to write
// mode:0,Inverted display; 1, normal display
void OLED_ShowPicture(uint8_t x, uint8_t y, uint8_t sizex, uint8_t sizey,
		uint8_t BMP[], uint8_t mode) {
	uint16_t j = 0;
	uint8_t x0, y0;
	uint8_t i, n, temp;

	for (x0 = 0; x0 < sizex; x0++) {
		y0 = 0;
		while (y0 < sizey) {
			temp = BMP[j];
			j++;

			n = (sizey - y0);
			if (n > 8) {
				n = 8;
			}
			for (i = 0; i < n; i++) {
				if (temp & 0x80)
					OLED_DrawPoint(x + x0, y + y0, mode);
				else
					OLED_DrawPoint(x + x0, y + y0, !mode);
				temp <<= 1;
				y0++;
			}
		}
	}
}

// OLED Init
void OLED_Init(void) {
	OLED_VCC_ON();
	OLED_VDD_ON();
	OLED_CS_Set();

	OLED_RES_Clr();
	HAL_Delay(200);
	OLED_RES_Set();

	OLED_WR_Byte(0xAE, OLED_CMD); /*display off*/
	OLED_WR_Byte(0xD5, OLED_CMD); /*set osc division*/
	OLED_WR_Byte(0xe1, OLED_CMD);
	OLED_WR_Byte(0xA8, OLED_CMD); /*multiplex ratio*/
	OLED_WR_Byte(0x5F, OLED_CMD); /*duty = 1/64*/
	OLED_WR_Byte(0xD3, OLED_CMD); /*set display offset*/
	OLED_WR_Byte(0x00, OLED_CMD);
	OLED_WR_Byte(0x40, OLED_CMD); /*set display start line*/
	OLED_WR_Byte(0xA0, OLED_CMD); /*set segment remap*/  // A1
	OLED_WR_Byte(0xC8, OLED_CMD); /*Com scan direction*/
	OLED_WR_Byte(0xDA, OLED_CMD); /*set COM pins*/
	OLED_WR_Byte(0x12, OLED_CMD);
	OLED_WR_Byte(0x81, OLED_CMD); /*contract control*/
	OLED_WR_Byte(220, OLED_CMD);
	OLED_WR_Byte(0xD9, OLED_CMD); /*set pre-charge period*/
	OLED_WR_Byte(0x22, OLED_CMD);
	OLED_WR_Byte(0xdb, OLED_CMD); /*set vcomh*/
	OLED_WR_Byte(0x20, OLED_CMD);
	OLED_WR_Byte(0xA4, OLED_CMD);
	OLED_WR_Byte(0xA6, OLED_CMD); /*normal / reverse*/  // A6正显 A7反显
	OLED_WR_Byte(0xB0, OLED_CMD); /*set page address*/
	OLED_ClearScreen();
	OLED_WR_Byte(0xAF, OLED_CMD); /*display ON*/
}

void OLED_Off(void) {
	OLED_VCC_OFF();
	OLED_VDD_OFF();
}
