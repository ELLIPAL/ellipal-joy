/**
 * Copyright (c) 2019-2022 ELLIPAL.
 *
 * @license (MIT license)
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:The above copyright
 * notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef ellipal_system_H_
#define ellipal_system_H_
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"

/* Exported define -----------------------------------------------------------*/
#define VERSION "ellipal_mmemonic_v1.0"

/* Exported typedef ----------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
#define IO_READ(x) ((x##_GPIO_Port->IDR & x##_Pin) ? 1 : 0)
#define IO_H(x) (x##_GPIO_Port->BSRR = x##_Pin)
#define IO_L(x) (x##_GPIO_Port->BSRR = (uint32_t)x##_Pin << 16)
#define IO_TOGGLE(x) (x##_GPIO_Port->ODR ^= x##_Pin)
#define IO_WRITE(x, state) \
  (HAL_GPIO_WritePin(x##_GPIO_Port, x##_Pin, (GPIO_PinState)state))

#define TS_DELAY(x) HAL_Delay(x)
#define TS_INIT(ts)     \
  do {                  \
    ts = HAL_GetTick(); \
  } while (0)

#define TS_IS_OVER(ts, over) (HAL_GetTick() - ts >= over)
#define TS_COUNT(ts) (HAL_GetTick() - ts)
#define TS_READ() (HAL_GetTick())

#define OLED_VDD_ON() IO_L(OLED_VDD_EN)
#define OLED_VDD_OFF() IO_H(OLED_VDD_EN)

#define OLED_VCC_ON() IO_H(OLED_VCC_EN)
#define OLED_VCC_OFF() IO_L(OLED_VCC_EN)

#define BAT_ADC_EN() IO_L(BAT_ADC_EN)
#define BAT_ADC_DIS() IO_H(BAT_ADC_EN)

#define IS_CHRG() (IO_READ(IS_CHRG) == 0)
#define IS_USB_IN() IO_READ(USB_IN)

/* External variables --------------------------------------------------------*/
extern uint16_t g_bat_adc_volt, g_bat_read_level;

/* External functions --------------------------------------------------------*/
uint16_t SystemReadBatVolt(void);
uint8_t SystemReadBatLevel(void);
void DeviceSleep(void);

#ifdef __cplusplus
}
#endif
#endif
