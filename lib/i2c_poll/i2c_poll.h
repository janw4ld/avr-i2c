#ifndef _I2C_POLL_H
#define _I2C_POLL_H

#include "i2c_common.h"

i2c_return_t TWI_start();
i2c_return_t TWI_repstart();
i2c_return_t TWI_stop();
i2c_return_t TWI_write_req(uint8_t address);
i2c_return_t TWI_read_req(uint8_t address);
i2c_return_t TWI_write_accept(void);
i2c_return_t TWI_read_accept(void);
i2c_return_t TWI_write(i2c_mode_t mode, uint8_t data);
i2c_return_t TWI_read(i2c_mode_t mode, uint8_t *buff);
i2c_return_t TWI_recieve_str(i2c_mode_t mode, ...);
i2c_return_t TWI_recieve_byte(i2c_mode_t mode, ...);
i2c_return_t TWI_send_str(i2c_mode_t mode, ...);
i2c_return_t TWI_send_byte(i2c_mode_t mode, ...);
// i2c_return_t TWI_printf(i2c_mode_t mode, char *format, ...);
#endif