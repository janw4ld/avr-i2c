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
    #endif

    while (1) {
        _TWI_DEBUG TWI_send_byte(TWI_master, SLAVE_ADDRESS, FR_ON);
        _TWI_LCD;
        _TWI_DEBUG TWI_send_byte(TWI_master, SLAVE_ADDRESS, FR_OFF);
        _TWI_LCD;
        _TWI_DEBUG TWI_send_byte(TWI_master, SLAVE_ADDRESS, FL_ON);
        _TWI_LCD;
        _TWI_DEBUG TWI_send_byte(TWI_master, SLAVE_ADDRESS, FL_OFF);
        _TWI_LCD;
        _TWI_DEBUG TWI_send_byte(TWI_master, SLAVE_ADDRESS, BR_ON);
        _TWI_LCD;
        _TWI_DEBUG TWI_send_byte(TWI_master, SLAVE_ADDRESS, BR_OFF);
        _TWI_LCD;
        _TWI_DEBUG TWI_send_byte(TWI_master, SLAVE_ADDRESS, BL_ON);
        _TWI_LCD;
        _TWI_DEBUG TWI_send_byte(TWI_master, SLAVE_ADDRESS, BL_OFF);
        _TWI_LCD;
    }
}