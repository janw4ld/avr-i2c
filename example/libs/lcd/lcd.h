#ifndef _LCD_H
#define _LCD_H

#include <stdint.h>
#include <stdarg.h>

/* LCD_MODE values */
// common to lcd.c and lcd_config.h
#define LCD_4BIT_2LINE_MODE 0x28
#define LCD_8BIT_2LINE_MODE 0x38

/* user facing LCD commands */
// to be used in main() as lcd_send_cmd(command);
#define LCD_ON      0x0D
#define LCD_CLEAR   0x01
#define CURSOR_ON   0x0E
#define CURSOR_OFF  0x0C
#define SHIFT_LEFT  0x18
#define SHIFT_RIGHT 0x1C

void lcd_init(void);
void lcd_off();
void lcd_send_cmd(uint8_t command);
void lcd_send_data(char data);
void lcd_set_cursor(uint8_t x, uint8_t y);
void lcd_send_str(char str[]);
void lcd_printf(char *format, ...);

/* less verbose aliases */
#define lcd_print(string) lcd_send_str(string)
#define lcd_write(byte) lcd_send_data(byte)
#define lcd_cmd(command) lcd_send_cmd(command)
#define lcd_xy(x, y) lcd_set_cursor(x, y)

// todo?
// void lcd_set_customglyph(uint8_t arr[], uint8_t block_num);
// void lcd_send_customglyph(uint8_t block_num);

#endif