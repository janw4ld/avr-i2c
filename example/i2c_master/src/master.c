#include "lcd.h"
#include "i2c_poll.h"
#define _TWI_DEBUG
#define _TWI_LCD
#include "i2c_debug.h"
#include <util/delay.h>

#include "light.h"

int main() {
    TWI_init(BITRATE, MASTER_ADDRESS);

#ifdef _LCD_H
    lcd_init();
    lcd_cmd(CURSOR_ON);
#endif

#define BIG_DELAY 200
#define DELAY 100
    while (1) {
        _TWI_DEBUG TWI_send_str(TWI_master, SLAVE_ADDRESS, (uint8_t[]){FR_ON, FL_ON, BR_ON, BL_ON, '\0'});
        _TWI_LCD;
        _delay_ms(BIG_DELAY);
        _TWI_DEBUG TWI_send_str(TWI_master, SLAVE_ADDRESS, (uint8_t[]){FR_OFF, FL_OFF, BR_OFF, BL_OFF, '\0'});
        _TWI_LCD;
        _delay_ms(BIG_DELAY);
        _TWI_DEBUG TWI_send_byte(TWI_master, SLAVE_ADDRESS, FR_ON);
        _TWI_LCD;
        _delay_ms(DELAY);
        _TWI_DEBUG TWI_send_byte(TWI_master, SLAVE_ADDRESS, FR_OFF);
        _TWI_LCD;
        _delay_ms(DELAY);
        _TWI_DEBUG TWI_send_byte(TWI_master, SLAVE_ADDRESS, FL_ON);
        _TWI_LCD;
        _delay_ms(DELAY);
        _TWI_DEBUG TWI_send_byte(TWI_master, SLAVE_ADDRESS, FL_OFF);
        _TWI_LCD;
        _delay_ms(DELAY);
        _TWI_DEBUG TWI_send_byte(TWI_master, SLAVE_ADDRESS, BR_ON);
        _TWI_LCD;
        _delay_ms(DELAY);
        _TWI_DEBUG TWI_send_byte(TWI_master, SLAVE_ADDRESS, BR_OFF);
        _TWI_LCD;
        _delay_ms(DELAY);
        _TWI_DEBUG TWI_send_byte(TWI_master, SLAVE_ADDRESS, BL_ON);
        _TWI_LCD;
        _delay_ms(DELAY);
        _TWI_DEBUG TWI_send_byte(TWI_master, SLAVE_ADDRESS, BL_OFF);
        _TWI_LCD;
        _delay_ms(BIG_DELAY);
    }
}