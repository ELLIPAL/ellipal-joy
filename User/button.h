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
#ifndef ellipal_button_H_
#define ellipal_button_H_
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported define -----------------------------------------------------------*/
#define BUTTON_NUM_MAX 3

#define BUTTON_LEFT 2
#define BUTTON_RIGHT 1
#define BUTTON_OK 3

/* Exported typedef ----------------------------------------------------------*/
typedef enum {
	button_none,
	button_press,
	button_press_free,
	button_longpress,
	button_longpress_free
} ButtonStatusEnum;

typedef void (*ButtonHandleCallBackDef)(uint8_t button, ButtonStatusEnum status);

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
#define IS_BUTTON_LEFT() (IO_READ(KEY2) == 0)
#define IS_BUTTON_RIGHT() (IO_READ(KEY1) == 0)
#define IS_BUTTON_OK() (IO_READ(KEY3) == 0)

/* External variables --------------------------------------------------------*/
extern ButtonStatusEnum button_status[];

/* External functions --------------------------------------------------------*/
void ButtonScanPolling(void);
uint8_t IsButtonPress(void);
void ButtonCallBackReg(ButtonHandleCallBackDef cb);

#ifdef __cplusplus
}
#endif
#endif

