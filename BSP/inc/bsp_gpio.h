#ifndef __BSP_MATRIX_KEY_H_
#define __BSP_MATRIX_KEY_H_

#include "stm32f10x.h"

typedef enum KEY_VALUES
{
    KEY_UP      = 0x0c,
    KEY_DOWN    = 0x16,
    KEY_LEFT    = 0x20,
    KEY_RIGHT   = 0x2A,

    KEY_ENTRY   = 0x0b,
    KEY_OK      = 0x15,
    KEY_CANCEL  = 0x1f,
    KEY_QUIT    = 0x29,

    KEY_NUL     = 0xff,

}KEY_VALUES;


extern unsigned char g_ucKeyValues;      // 当前按键值,全局
extern unsigned char g_ucKeyContinu;     // 连续按键的标志


void gpioInit(void);
u8 gpioStatusUpdate(void);
extern unsigned char gpio[4][4];

#endif
