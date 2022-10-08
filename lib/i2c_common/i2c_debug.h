#ifndef _I2C_DEBUG_H
#define _I2C_DEBUG_H

#if !defined _I2C_COMMON_H
#warning "i2c_debug.h is included, but neither i2c_int.h nor i2c_poll.h are."
#elif !defined _LCD_H
#warning "i2c_debug.h is included, but lcd.h isn't."

#else

#include <stdint.h>

volatile i2c_return_t twi_return = 0;
uint8_t depth = 0;
#define _TWI_DEBUG  depth = __LINE__;   twi_return =
#define TWI_RET (twi_return & ~TWI_ERROR_MASK)
#define TWI_STA (twi_return & TWI_ERROR_MASK)
#define _TWI_LCD                                                \
    {                                                           \
        switch (TWI_STA) {                                      \
            case TWI_OK:                                        \
                lcd_printf(" L%d:ok:%2X ", depth, TWI_RET);     \
                break;                                          \
            case TWI_TIMEOUT:                                   \
                lcd_printf(" L%d:timeout:%2X ", depth, TWI_RET);\
                break;                                          \
            case TWI_ERR:                                       \
                lcd_printf(" L%d:error:%2X ", depth, TWI_RET);  \
                break;                                          \
            default:                                            \
                lcd_printf(" L%d:unknown%2X ", depth);          \
                break;                                          \
        }                                                       \
    }

#define _TWI_OK if (TWI_STA == TWI_OK)
#define _TWI_TIMEOUT if (TWI_STA == TWI_TIMEOUT)
#define _TWI_ERROR if (TWI_STA == TWI_ERR)

#endif


#endif