#ifndef __OLED_H
#define __OLED_H

#include "stdint.h"

//-----------------OLED PORT DEFINITION----------------
#define OLED_SCL_Clr() IO_L(SPI_SCK)
#define OLED_SCL_Set() IO_H(SPI_SCK)

#define OLED_SDA_Clr() IO_L(SPI_MOSI)
#define OLED_SDA_Set() IO_H(SPI_MOSI)

#define OLED_RES_Clr() IO_L(LCD_RES)
#define OLED_RES_Set() IO_H(LCD_RES)

#define OLED_DC_Clr() IO_L(LCD_DC)
#define OLED_DC_Set() IO_H(LCD_DC)

#define OLED_CS_Clr() IO_L(SPI_CS)
#define OLED_CS_Set() IO_H(SPI_CS)

#define OLED_EN_Clr() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET) //
#define OLED_EN_Set() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET)

#define OLED_CMD 0  // OLED command
#define OLED_DATA 1 // OLED data

void OLED_ColorTurn(uint8_t i);
void OLED_DisplayTurn(uint8_t i);
void OLED_Contract(uint8_t i);
void OLED_WR_Byte(uint8_t dat, uint8_t mode);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);
void OLED_Refresh(void);
void OLED_ClearScreen(void);
void OLED_ClearGram(void);
void OLED_DrawPoint(uint8_t x, uint8_t y, uint8_t t);
void OLED_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t mode);
void OLED_DrawCircle(uint8_t x, uint8_t y, uint8_t r);
void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t size1,
		uint8_t mode);
void OLED_ShowString(uint8_t x, uint8_t y, uint8_t *chr, uint8_t size1,
		uint8_t mode);
void OLED_ShowNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len,
		uint8_t size1, uint8_t mode);
void OLED_ShowPicture(uint8_t x, uint8_t y, uint8_t sizex, uint8_t sizey,
		uint8_t BMP[], uint8_t mode);
uint8_t OLED_GetPoint(uint8_t x, uint8_t y);

void OLED_Init(void);
void OLED_Off(void);

#endif
