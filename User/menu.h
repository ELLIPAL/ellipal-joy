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
#ifndef ellipal_menu_H_
#define ellipal_menu_H_
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/* Exported define -----------------------------------------------------------*/

/* Exported typedef ----------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* External variables --------------------------------------------------------*/

/* External functions --------------------------------------------------------*/
void ShowPowerOnoffPage(void);
void ShowGenerateNoticePage(void);
void ShowNumberSelectPage(uint8_t num);
void ShowGeneratedPage(void);
void ShowMnemoicsPage(uint8_t page_num, uint8_t page_total, uint8_t index,
		uint8_t mnem_num, char *mnem[]);
void ShowReGenerateNoticePage(uint8_t is_yes);
void ShowNoOperationPage(uint8_t sec);
void ShowKeepPage(void);
void ShowImportPage(void);
void ShowChargePage(uint8_t grap, uint8_t num);
void ShowUpArrow(void);
void ShowLeftRightArrow(void);
void ShowBattery(uint8_t perc);

#ifdef __cplusplus
}
#endif
#endif
