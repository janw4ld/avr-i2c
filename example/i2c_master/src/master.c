#include "lcd.h"
#include "i2c_poll.h"
#include "i2c_debug.h"
#include <util/delay.h>

#include "light.h"

int main() {
    TWI_init(BITRATE, MASTER_ADDRESS);

    lcd_init();
    lcd_cmd(CURSOR_ON);

#define BIG_DELAY 200
#define DELAY 100
    while (1) {
        _TWI_DEBUG TWI_send_str(TWI_master, SLAVE_ADDRESS, (uint8_t[]){FR_ON, FL_ON, BR_ON, BL_ON, '\0'});
        _TWI_LCD;
        _delay_ms(BIG_DELAY);

        TWI_send_str(TWI_master, SLAVE_ADDRESS, (uint8_t[]){FR_OFF, FL_OFF, BR_OFF, BL_OFF, '\0'});
        _delay_ms(BIG_DELAY);

        TWI_send_byte(TWI_master, SLAVE_ADDRESS, FR_ON);
        _delay_ms(DELAY);

        TWI_send_byte(TWI_master, SLAVE_ADDRESS, FR_OFF);
        _delay_ms(DELAY);

        TWI_send_byte(TWI_master, SLAVE_ADDRESS, FL_ON);
        _delay_ms(DELAY);

        _TWI_DEBUG TWI_send_byte(TWI_master, SLAVE_ADDRESS, FL_OFF);
        _TWI_LCD;
        _delay_ms(DELAY);

        TWI_send_byte(TWI_master, SLAVE_ADDRESS, BR_ON);
        _delay_ms(DELAY);

        TWI_send_byte(TWI_master, SLAVE_ADDRESS, BR_OFF);
        _delay_ms(DELAY);

        TWI_send_byte(TWI_master, SLAVE_ADDRESS, BL_ON);
        _delay_ms(DELAY);
        
        TWI_send_byte(TWI_master, SLAVE_ADDRESS, BL_OFF);
        _delay_ms(BIG_DELAY);
    }
}