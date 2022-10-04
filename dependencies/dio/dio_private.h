#ifndef _DIO_PRIVATE_H
#define _DIO_PRIVATE_H

#define DDR_OFFSET -1
#define READ_OFFSET -2

#define _reg(address) ((volatile uint8_t*)(address))
#define REG_MASK      UINT8_MAX
#define _port(dio)    (*_reg(dio & DIO_PORT_MASK))
#define _ddr(dio)     (*_reg((&_port(dio)) + DDR_OFFSET))
#define _read(dio)    (*_reg((&_port(dio)) + READ_OFFSET))
#define _pin(dio)     (dio >> DIO_PIN_SHIFT)

#endif