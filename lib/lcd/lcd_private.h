#ifndef _LCD_PRIVATE_H
#define _LCD_PRIVATE_H

#include "lcd_config.h"

#define INIT_DELAY 500
#define LCD_DELAY 40

#ifndef LCD_MODE
#define LCD_MODE LCD_8BIT_2LINE_MODE
#endif

#if LCD_MODE == LCD_4BIT_2LINE_MODE
#define LCD_BUS_WIDTH 4
#else
#define LCD_BUS_WIDTH 8
#endif

#ifndef LCD_LENGTH
#define LCD_LENGTH 16
#endif

#define LCD_LINES 2

/* private LCD commands */
#define LCD_NIBBLES 0x02
#define SET_CURSOR_LOCATION 0x80
#define LCD_ENTRY 0x06  // LCD_ENTRY is the display mode where
                        // the cursor automatically moves one
                        // step with each character displayed

#endif