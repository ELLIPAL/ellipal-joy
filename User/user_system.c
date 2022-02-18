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

/* Includes ------------------------------------------------------------------*/
#include "adc.h"
#include "includes.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* External variables --------------------------------------------------------*/
uint16_t g_bat_adc_volt = 0, g_bat_read_level = 0;

/* Private function prototypes -----------------------------------------------*/

/* External functions --------------------------------------------------------*/

/**
 * @brief Read battery voltage
 *
 * @return uint16_t millivolt
 */
uint16_t SystemReadBatVolt(void) {
	uint32_t volt, res;

	BAT_ADC_EN();
	TS_DELAY(10);

	LL_ADC_ClearFlag_EOC(hadc1.Instance);
	LL_ADC_REG_StartConversion(hadc1.Instance);
	while (!LL_ADC_IsActiveFlag_EOC(hadc1.Instance)) {
		continue;
	}
	res = HAL_ADC_GetValue(&hadc1);
	volt = res * 9900 / 4095;

	if (IS_CHRG()) {
		volt -= 80;
	}
	BAT_ADC_DIS();

	g_bat_adc_volt = volt;
	return g_bat_adc_volt;
}

/**
 * @brief Read battery voltage percentage
 *
 * @return uint8_t 0-100
 */
uint8_t SystemReadBatLevel(void) {
	uint16_t perc;

	SystemReadBatVolt();

	if (g_bat_adc_volt > 4100 && IS_USB_IN()) {
		perc = 100;
	} else if (g_bat_adc_volt > 4060 && !IS_USB_IN()) {
		perc = 100;
	} else if (g_bat_adc_volt > 4020) {
		perc = 90;
	} else if (g_bat_adc_volt > 3970) {
		perc = 80;
	} else if (g_bat_adc_volt > 3920) {
		perc = 70;
	} else if (g_bat_adc_volt > 3860) {
		perc = 60;
	} else if (g_bat_adc_volt > 3810) {
		perc = 50;
	} else if (g_bat_adc_volt > 3780) {
		perc = 40;
	} else if (g_bat_adc_volt > 3740) {
		perc = 30;
	} else if (g_bat_adc_volt > 3700) {
		perc = 20;
	} else if (g_bat_adc_volt > 3600) {
		perc = 10;
	} else if (g_bat_adc_volt > 3500) {
		perc = 5;
	} else {
		perc = 0;
	}

	if (IS_USB_IN()) {
		if (perc > g_bat_read_level) {
			g_bat_read_level = perc;
		} else if (g_bat_read_level - perc >= 20) {
			g_bat_read_level = perc;
		}
	} else {
		if (perc < g_bat_read_level) {
			g_bat_read_level = perc;
		} else if (perc - g_bat_read_level >= 20) {
			g_bat_read_level = perc;
		}
	}

	return g_bat_read_level;
}

/**
 * @brief Device enter sleep mode.
 *
 */
void DeviceSleep(void) {
	PWREx_WakeupPinTypeDef config;

	config.PinPolarity = PWR_PIN_POLARITY_LOW;
	config.PinPull = PWR_PIN_PULL_UP;

	config.WakeUpPin = PWR_WAKEUP_PIN1;
	HAL_PWREx_EnableWakeUpPin(&config);
	config.WakeUpPin = PWR_WAKEUP_PIN2;
	HAL_PWREx_EnableWakeUpPin(&config);
	config.WakeUpPin = PWR_WAKEUP_PIN6;
	HAL_PWREx_EnableWakeUpPin(&config);

	config.PinPolarity = PWR_PIN_POLARITY_HIGH;
	config.PinPull = PWR_PIN_NO_PULL;
	config.WakeUpPin = PWR_WAKEUP_PIN4;
	HAL_PWREx_EnableWakeUpPin(&config);

	HAL_PWR_EnterSTANDBYMode();
}

/* Private functions ---------------------------------------------------------*/
