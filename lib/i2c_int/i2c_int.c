#include "i2c_int.h"

#include <avr/io.h>
#include <avr/interrupt.h>

// acknowledge the interrupt and clear TWINT bit
#define _TWI_int TWCR = (1 << TWIE) | (1 << TWINT) | (1 << TWEA) | (1 << TWEN)

#define TW_STATUS (TWSR & TW_STATUS_MASK)

void (*TWI_int_recieved)(uint8_t);
void (*TWI_int_requested)();

void TWI_int(volatile void (*on_recieve)(uint8_t),
             volatile void (*on_request)()) {
    TWI_int_recieved = on_recieve;
    TWI_int_requested = on_request;
    sei();
    _TWI_int;
}

inline __attribute__((always_inline)) void TWI_write(uint8_t data) {
    TWDR = data;
}

ISR(TWI_vect) {
    _TWI_int;
    switch (TW_STATUS) {
        case TW_SR_DATA_ACK:
            TWI_int_recieved(TWDR);
            break;
        case TW_ST_SLA_ACK:
            TWI_int_requested();
            break;
        case TW_BUS_ERROR:
            TWCR = 0;
            TWBR = 0;
            break;
        // default:
        //     break;
        // case TW_SR_SLA_ACK:
        // case TW_ST_DATA_ACK:
        //     //_TWI_int;
        //     break;
    }
}