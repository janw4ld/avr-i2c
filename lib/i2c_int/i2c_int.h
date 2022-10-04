#ifndef _I2C_INT_H
#define _I2C_INT_H

#include "i2c_common.h"

void TWI_int(void (*on_recieve)(uint8_t), void (*on_request)());
void TWI_write(uint8_t data);

#endif