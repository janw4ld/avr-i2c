#include "i2c_int.h"
#include <avr/io.h>
#include "light.h"
#include <avr/interrupt.h>

void update_light(uint8_t recieved_data);
#define NULL ((void *)0)

int main() {
    TWI_init(BITRATE, SLAVE_ADDRESS);
    TWI_int(update_light, NULL);

    LIGHT_DIR |= LIGHT_MASK;

    while (1)
        ;
}

void update_light(uint8_t recieved_data) {
    static uint8_t light_status;

    if (recieved_data) {
        light_status ^= (recieved_data & LIGHT_MASK);

        LIGHT_PORT &= ~LIGHT_MASK;
        LIGHT_PORT |= light_status;
    }
}
