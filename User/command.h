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
#ifndef AFUIOT_command_H_
#define AFUIOT_command_H_
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

#ifdef __cplusplus
}
#endif
#endif

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef COMMAND_H_
#define COMMAND_H_

#ifdef __cplusplus
extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
#include "stdarg.h"
#include "stdint.h"

/* Exported typedef ----------------------------------------------------------*/
/*call back*/
typedef void (*Cmd_CallBack)(int argc, char *argv[]);

/*entry of cmd*/
typedef struct CmdEntrance {
	char const *cmd;
	Cmd_CallBack pCB;
	struct CmdEntrance *next;
} CmdEntrance_t;

/* Exported define -----------------------------------------------------------*/
#ifndef DEBUG
#define DEBUG 1
#endif

#define COMMAND_BUF_MAX 256
#define COMMAND_PRINT_BUF_MAX 1024

#if DEBUG > 0
#define DBG_LOG(format, ...) \
  CommandPrintf("log> " format "\r\n", ##__VA_ARGS__)
#define DBG_SEND(data, len) CommandSend(data, len)
#else
#define DBG_LOG(format)
#define DBG_SEND(data, len)
#endif

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define CMD_ARGC_MAX 16

#define CMD_ENT_DEF(cmd, ent) \
  static CmdEntrance_t CmdEntrance_##cmd = {#cmd, ent, NULL}

#define CMD_ENT(cmd) &CmdEntrance_##cmd

/*string equal*/
#define STR_EQUAL(des, token) (strcmp((char *)des, (char *)token) == 0)
#define STR_NEQUAL(des, token) \
  (strncmp((char *)des, (char *)token, strlen((char *)token)) == 0)

/*arg equal*/
#define ARGV_EQUAL(token) (strcmp(argv[0], (char *)token) == 0)
#define ARGV_LEGAL(argv) (argv != NULL && isalnum(argv[0]))

/* External variables --------------------------------------------------------*/

/* External functions --------------------------------------------------------*/
void CommandInit(void);

void CommandNewRec(uint8_t rd);
void CommandReceivePolling(void);

void CommandSend(uint8_t *data, uint16_t len);
void CommandPrintf(char *format, ...);

void CommandVirtual(char *cmd);

uint8_t Cmd_AddEntrance(CmdEntrance_t *pEnt);
void Cmd_Handle(char *cmd);

#ifdef __cplusplus
}
#endif

#endif
