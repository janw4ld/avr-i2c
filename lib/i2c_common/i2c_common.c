#include "i2c_common.h"

#include <avr/io.h>

#include "macros.h"
#include "psc.h"

#include <math.h>

#define TW_STATUS (TWSR & TW_STATUS_MASK)

#define __finline inline __attribute__((always_inline)) 

i2c_return_t TWI_init(uint32_t frequency, uint8_t address) {
    uint16_t bitrate = UINT16_MAX;
    uint8_t scale;

    // automatically pick the smallest acceptable scale to get the required bitrate
    for (scale = PSC_1;
         (scale <= PSC_64) && (bitrate > UINT8_MAX);
         scale *= 4) {
        bitrate = round((float)F_CPU / (float)frequency - 16) / (2 * (float)scale);
    }

    uint8_t prescaler = psc_select(SCL, scale);
    _assign_pattern(TWSR, TWPS0, 0b11, prescaler);

    // 400K = 16Mhz/(16 + 2*TWBR*PSC_1) -> TWBR = x = 12
    TWBR = bitrate;

    TWSR &= ~TW_STATUS_MASK;  // clear status
    TWAR = (address << 1);

    _clear_bit(TWCR, TWIE);

    return TWI_check_status(0);
}

i2c_return_t TWI_check_status(i2c_status_t operation) {
    i2c_return_t return_code = TWI_ERR;

    if (TW_STATUS == operation) {
        return_code = (operation | TWI_OK);
    } else if (TW_STATUS != operation) {
        return_code = (TW_STATUS | TWI_ERR);
    }

    return return_code;
}

__finline
void TWI_off() {
    TWSR = 0;
    TWBR = 0;
    TWAR = 0;
}