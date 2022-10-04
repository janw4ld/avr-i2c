#include "i2c_poll.h"
#include "config/i2c_config.h"

#include "macros.h"
#include "psc.h"

#include <avr/io.h>
#include <util/delay.h>

#include <stdarg.h>

#define TWI_READ 1
#define TWI_WRITE 0

#ifndef TWI_RETRIES
#define TWI_RETRIES 5000
#endif
#ifndef TWI_DELAY
#define TWI_DELAY 1
#endif

#define _TWI_try(bit)                                                  \
    do {                                                               \
        _set_bit(TWCR, bit);                                           \
        _set_bit(TWCR, TWINT);                                         \
        _set_bit(TWCR, TWEN);                                          \
        uint32_t timeout = 0;                                          \
        while (_get_bit(TWCR, TWINT) == 0 && timeout <= TWI_RETRIES) { \
            _delay_us(TWI_DELAY);                                      \
            timeout++;                                                 \
        }                                                              \
        if (timeout == TWI_RETRIES) {                                  \
            _clear_bit(TWCR, bit);                                     \
            return (TW_STATUS | TWI_TIMEOUT);                          \
        }                                                              \
    } while (0)

#define _TWI_poll(condition)                                          \
    do {                                                              \
        uint32_t timeout = 0;                                         \
        while ((TW_STATUS != condition) && (timeout < TWI_RETRIES)) { \
            _delay_us(TWI_DELAY);                                     \
            timeout++;                                                \
        }                                                             \
        if (timeout == TWI_RETRIES) {                                 \
            return (TW_STATUS | TWI_TIMEOUT);                         \
        }                                                             \
    } while (0)

#define _TWI_wait _TWI_try(TWINT)

i2c_return_t TWI_start() {
    _TWI_try(TWSTA);  // will return timeout if it fails

    return TWI_check_status(TW_START);
}

i2c_return_t TWI_repstart() {
    _TWI_try(TWSTA);

    return TWI_check_status(TW_REP_START);
}

i2c_return_t TWI_stop() {
    TWSR &= ~TW_STATUS_MASK;  // clear status

    _set_bit(TWCR, TWSTO);
    _TWI_wait;

    TWBR = 0;
    TWCR = 0;

    return (TW_STATUS | TWI_OK);
}

i2c_return_t TWI_write_req(uint8_t address) {
    // Write address + write bit in data register
    TWDR = (address << 1) | TWI_WRITE;

    _TWI_wait;

    return TWI_check_status(TW_MT_SLA_W_ACK);
}

i2c_return_t TWI_read_req(uint8_t address) {
    // Write address + write bit in data register
    TWDR = (address << 1) | TWI_READ;

    _TWI_wait;

    _TWI_poll(TW_MT_SLA_R_ACK);
    return TWI_check_status(TW_MT_SLA_R_ACK);
}

i2c_return_t TWI_write_accept(void) {
    _TWI_try(TWEA);

    //_TWI_poll(TW_SR_SLA_ACK);
    return TWI_check_status(TW_SR_SLA_ACK);
}

i2c_return_t TWI_read_accept(void) {
    _TWI_try(TWEA);

    //_TWI_poll(TW_ST_SLA_ACK);
    return TWI_check_status(TW_ST_SLA_ACK);
}

i2c_return_t TWI_write(i2c_mode_t mode, uint8_t data) {
    i2c_status_t operation = ((mode == TWI_slave) ? TW_ST_DATA_ACK
                                                  : TW_MT_DATA_ACK);

    TWDR = data;

    if (mode == TWI_slave) {
        _TWI_try(TWEA);
    } else {
        _TWI_wait;
    }

    _TWI_poll(operation);
    return TWI_check_status(operation);
}

i2c_return_t TWI_read(i2c_mode_t mode, uint8_t *buff) {
    i2c_status_t operation = ((mode == TWI_slave) ? TW_SR_DATA_ACK
                                                  : TW_MR_DATA_ACK);
    _TWI_try(TWEA);
    _TWI_poll(operation);
    *buff = TWDR;
    return TWI_check_status(operation);
}

i2c_return_t TWI_send_str(i2c_mode_t mode, ...) {
    i2c_return_t status = 0;
    va_list argv;
    va_start(argv, mode);
    switch (mode) {
        case TWI_master:
            TWI_start();
            uint8_t address = va_arg(argv, int);
            TWI_write_req(address);
            break;
        case TWI_slave:
            TWI_read_accept();
            break;
    }
    const char *str = va_arg(argv, char *);
    va_end(argv);

    do {
        status |= (TWI_write(mode, *(uint8_t *)str) & TWI_ERROR_MASK);
        str++;
    } while (*(str - 1) != '\0');

    if (mode == TWI_master)
        TWI_stop();

    return (((mode == TWI_slave) ? TW_ST_STRING
                                 : TW_MT_STRING) |
            status);
}

i2c_return_t TWI_recieve_str(i2c_mode_t mode, ...) {
    i2c_return_t status = 0;
    va_list argv;
    va_start(argv, mode);
    switch (mode) {
        case TWI_master:
            TWI_start();
            uint8_t address = va_arg(argv, int);
            TWI_read_req(address);
            break;
        case TWI_slave:
            TWI_write_accept();
            break;
    }
    char *str = va_arg(argv, char *);
    va_end(argv);

    do {
        status |= (TWI_read(mode, (uint8_t *)str) & TWI_ERROR_MASK);
        str++;
    } while (*(str - 1) != '\0');

    if (mode == TWI_master)
        TWI_stop();

    return (((mode == TWI_slave) ? TW_SR_STRING
                                 : TW_MR_STRING) |
            status);
}

i2c_return_t TWI_send_byte(i2c_mode_t mode, ...) {
    i2c_return_t status = 0;
    va_list argv;
    va_start(argv, mode);
    switch (mode) {
        case TWI_master:
            TWI_start();
            uint8_t address = va_arg(argv, int);
            TWI_write_req(address);
            break;
        case TWI_slave:
            TWI_read_accept();
            break;
    }
    const uint8_t data = va_arg(argv, int);
    va_end(argv);

    status |= (TWI_write(mode, data) & TWI_ERROR_MASK);

    if (mode == TWI_master)
        TWI_stop();

    return (((mode == TWI_slave) ? TW_ST_STRING
                                 : TW_MT_STRING) |
            status);
}

i2c_return_t TWI_recieve_byte(i2c_mode_t mode, ...) {
    i2c_return_t status = 0;
    va_list argv;
    va_start(argv, mode);
    switch (mode) {
        case TWI_master:
            TWI_start();
            uint8_t address = va_arg(argv, int);
            TWI_read_req(address);
            break;
        case TWI_slave:
            TWI_write_accept();
            break;
    }
    uint8_t *data = va_arg(argv, uint8_t *);
    va_end(argv);

    status |= (TWI_read(mode, (uint8_t *)data) & TWI_ERROR_MASK);

    if (mode == TWI_master)
        TWI_stop();

    return (((mode == TWI_slave) ? TW_SR_STRING
                                 : TW_MR_STRING) |
            status);
}

/*
i2c_return_t TWI_printf(i2c_mode_t mode, char *format, ...)
{

    va_list args;
    va_start(args, format);
    uint8_t len = snprintf(NULL, 0, format, args);
    char str_buffer[UINT8_MAX];
    vsnprintf(str_buffer, len + 1, format, args);
    va_end(args);
    TWI_send_str(mode, str_buffer);
    free(str_buffer);
    return ((mode == TWI_slave) ? TW_ST_STRING
                                : TW_MT_STRING);
} */