#include "dio.h"
#include "dio_private.h"

#include <avr/io.h>
#include <util/delay.h>

#include "macros.h"

void dio_set_direction(dio_t dio, dio_direction_t direction) {
    _assign_bit(_ddr(dio), _pin(dio), direction);
}

void dio_set_level(dio_t dio, dio_level_t level) {
    _assign_bit(_port(dio), _pin(dio), level);
}

dio_level_t dio_get_level(dio_t dio) {
    return _get_bit(_read(dio), _pin(dio));
}

void dio_set_port_direction(dio_port_t port, dio_direction_t direction) {
    switch (direction) {
        case 0:                       // if the direction corresponds to LOW
            _ddr(port) &= ~REG_MASK;  // take all the bits LOW
            break;
        case 1:                       // if it corresponds to HIGH
            _ddr(port) = REG_MASK;    // pull all the bits HIGH
            break;
        default:                      // on invalid direction,
            break;                    // do nothing
    }
}

void dio_set_port_level(dio_port_t port, dio_level_t level) {
    _port(port) = (level & REG_MASK);
}

void dio_off() {
    /* loop on all port addresses */
    for (dio_port_t address = DIO_PORTA;
         address >= DIO_PORTD;          // this comparison is reversed
         address += DIO_PORT_OFFSET) {  // because the offset is negative
        /* and take all their levels and dirs down */
        dio_set_port_level(_port(address), DIO_LEVEL_OFF);
        dio_set_port_direction(_port(address), DIO_DIRECTION_OFF);
    }
}