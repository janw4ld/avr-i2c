#include "lcd.h"
#include "lcd_config.h"
#include "lcd_private.h"

#include <stdio.h>
#include <util/delay.h>

#ifdef LCD_DYNALLOC
#include <stdlib.h>
#endif

#include "dio.h"
#include "macros.h"

#ifdef LCD_TRACK_POS
uint8_t xpos = 0;
uint8_t ypos = 0;
#endif

void lcd_send(uint8_t message);

void lcd_init() {
#ifdef LCD_TRACK_POS
    xpos = 0;
    ypos = 0;
#endif

    dio_t data_bus[LCD_BUS_WIDTH] = LCD_DATA_PINS;
    // pin init
    dio_set_direction(LCD_EN_PIN, DIO_DIRECTION_OUTPUT);
    dio_set_direction(LCD_RS_PIN, DIO_DIRECTION_OUTPUT);
    for (uint8_t pin = 0; pin < LCD_BUS_WIDTH; pin++) {
        dio_set_direction(data_bus[pin], DIO_DIRECTION_OUTPUT);
    }

    // LCD Init
#if LCD_MODE == LCD_4BIT_2LINE_MODE
    lcd_send_cmd(LCD_NIBBLES);
#endif
    lcd_send_cmd(LCD_MODE);
    lcd_send_cmd(CURSOR_OFF);
    lcd_send_cmd(LCD_ENTRY);
    _delay_us(500);
}

void lcd_send(uint8_t message) {
    dio_t data_bus[LCD_BUS_WIDTH] = LCD_DATA_PINS;
    // dio_set_port_level(LCD_DATA_PORT, message & 0xf0);

#if LCD_MODE == LCD_4BIT_2LINE_MODE

#define nibble (message >> 4)

    for (uint8_t pin = 0; pin < LCD_BUS_WIDTH; pin++) {
        dio_set_level(data_bus[pin], _get_bit(nibble, pin));
    }

    dio_pulse(LCD_EN_PIN, LCD_DELAY);

#endif

    for (uint8_t pin = 0; pin < LCD_BUS_WIDTH; pin++) {
        dio_set_level(data_bus[pin], _get_bit(message, pin));
    }

    dio_pulse(LCD_EN_PIN, LCD_DELAY);
    _delay_us(LCD_DELAY);
}

void lcd_send_cmd(uint8_t command) {
    // RS -> CMD:0
    dio_set_level(LCD_RS_PIN, DIO_LEVEL_LOW);
    _delay_us(5);  // TODO give this a name?

    lcd_send(command);
    _delay_us(2000 - LCD_DELAY);  // total of 2ms delay after EN pulse
}

void lcd_send_data(char data) {
#ifdef LCD_TRACK_POS
    if ((++xpos >= LCD_LENGTH)) {   // if x position overflows, move it to
        xpos = 0;                   // the first character
        ypos++;                     // of the next line, but
        ypos %= LCD_LINES;          // rollover the line number on overflow
        lcd_set_cursor(xpos, ypos);
    }
#endif

    // RS -> data:1
    dio_set_level(LCD_RS_PIN, DIO_LEVEL_HIGH);
    _delay_us(LCD_DELAY);  // TODO try setting this to 5us

    lcd_send(data);
}

void lcd_set_cursor(uint8_t x, uint8_t y) {
#ifdef LCD_TRACK_POS
    xpos = x;
    ypos = y;
#endif

#define LINE_SHIFT 6  // LCD controller constant
    uint8_t address = x | (y << LINE_SHIFT);
    lcd_send_cmd(SET_CURSOR_LOCATION | address);
}

void lcd_send_str(char str[]) {
    for (uint8_t i = 0;
         (str[i] != '\0') &&            // loop on characters until string is terminated
         (i < LCD_LENGTH * LCD_LINES);  // or the entire screen was rewritten once
         i++) {
        lcd_send_data(str[i]);
    }
}

void lcd_off() {
    dio_t data_bus[LCD_BUS_WIDTH] = LCD_DATA_PINS;
    lcd_send_cmd(LCD_CLEAR);

    for (uint8_t pin = 0; pin < LCD_BUS_WIDTH; pin++) {
        dio_set_level(data_bus[pin], DIO_LEVEL_OFF);
        dio_set_direction(data_bus[pin], DIO_DIRECTION_OFF);
    }

    dio_set_level(LCD_RS_PIN, DIO_LEVEL_OFF);
    dio_set_level(LCD_EN_PIN, DIO_LEVEL_OFF);
}

void lcd_printf(char *format, ...) {
    va_list args;
    va_start(args, format);
#ifdef LCD_DYNALLOC
#include <stdlib.h>
    uint8_t len = snprintf(NULL, 0, format, args);
    char *str_buffer = malloc(len + 1);
    vsnprintf(str_buffer, len + 1, format, args);
#else
    char str_buffer[LCD_LENGTH * LCD_LINES];
    vsnprintf(str_buffer, LCD_LENGTH * LCD_LINES, format, args);
#endif
    va_end(args);
    lcd_send_str(str_buffer);
}

/*
void lcd_send_int(int32_t data) {
    char str_buffer[LCD_LENGTH];
    sprintf(str_buffer, "%ld", data);
    lcd_send_str(str_buffer);
}
 */