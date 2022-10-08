#ifndef _DIO_H
#define _DIO_H

#include <stdint.h>

typedef enum {
    DIO_PORTA = 0x3B,
    DIO_PORTB = 0x38,
    DIO_PORTC = 0x35,
    DIO_PORTD = 0x32,
    DIO_PORT_MASK = 0x3F
} dio_port_t;
#define DIO_PORT_OFFSET -3  // the offset between each port address
#define DIO_PIN_SHIFT 6     // the bit width of the max port address

typedef enum {
    DIO_PIN0,
    DIO_PIN1,
    DIO_PIN2,
    DIO_PIN3,
    DIO_PIN4,
    DIO_PIN5,
    DIO_PIN6,
    DIO_PIN7,
    DIO_PIN_MASK = 0b111
} dio_pin_t;

#define _dio(address, pin) (address | (pin << DIO_PIN_SHIFT))
typedef enum {
    DIO_PA0 = _dio(DIO_PORTA, DIO_PIN0),
    DIO_PA1 = _dio(DIO_PORTA, DIO_PIN1),
    DIO_PA2 = _dio(DIO_PORTA, DIO_PIN2),
    DIO_PA3 = _dio(DIO_PORTA, DIO_PIN3),
    DIO_PA4 = _dio(DIO_PORTA, DIO_PIN4),
    DIO_PA5 = _dio(DIO_PORTA, DIO_PIN5),
    DIO_PA6 = _dio(DIO_PORTA, DIO_PIN6),
    DIO_PA7 = _dio(DIO_PORTA, DIO_PIN7),
    DIO_PB0 = _dio(DIO_PORTB, DIO_PIN0),
    DIO_PB1 = _dio(DIO_PORTB, DIO_PIN1),
    DIO_PB2 = _dio(DIO_PORTB, DIO_PIN2),
    DIO_PB3 = _dio(DIO_PORTB, DIO_PIN3),
    DIO_PB4 = _dio(DIO_PORTB, DIO_PIN4),
    DIO_PB5 = _dio(DIO_PORTB, DIO_PIN5),
    DIO_PB6 = _dio(DIO_PORTB, DIO_PIN6),
    DIO_PB7 = _dio(DIO_PORTB, DIO_PIN7),
    DIO_PC0 = _dio(DIO_PORTC, DIO_PIN0),
    DIO_PC1 = _dio(DIO_PORTC, DIO_PIN1),
    DIO_PC2 = _dio(DIO_PORTC, DIO_PIN2),
    DIO_PC3 = _dio(DIO_PORTC, DIO_PIN3),
    DIO_PC4 = _dio(DIO_PORTC, DIO_PIN4),
    DIO_PC5 = _dio(DIO_PORTC, DIO_PIN5),
    DIO_PC6 = _dio(DIO_PORTC, DIO_PIN6),
    DIO_PC7 = _dio(DIO_PORTC, DIO_PIN7),
    DIO_PD0 = _dio(DIO_PORTD, DIO_PIN0),
    DIO_PD1 = _dio(DIO_PORTD, DIO_PIN1),
    DIO_PD2 = _dio(DIO_PORTD, DIO_PIN2),
    DIO_PD3 = _dio(DIO_PORTD, DIO_PIN3),
    DIO_PD4 = _dio(DIO_PORTD, DIO_PIN4),
    DIO_PD5 = _dio(DIO_PORTD, DIO_PIN5),
    DIO_PD6 = _dio(DIO_PORTD, DIO_PIN6),
    DIO_PD7 = _dio(DIO_PORTD, DIO_PIN7)
} dio_t;
typedef enum {
    DIO_DIRECTION_INPUT = 0,
    DIO_DIRECTION_OUTPUT = 1
} dio_direction_t;
#define DIO_DIRECTION_OFF DIO_DIRECTION_INPUT

typedef enum {
    DIO_LEVEL_LOW = 0,
    DIO_LEVEL_HIGH = 1,
    DIO_LEVEL_ERROR = 2
} dio_level_t;
#define DIO_LEVEL_OFF DIO_LEVEL_LOW

void dio_set_direction(dio_t dio, dio_direction_t direction);
void dio_set_level(dio_t dio, dio_level_t value);
dio_level_t dio_get_level(dio_t dio);
void dio_set_port_direction(dio_port_t port, dio_direction_t direction);
void dio_set_port_level(dio_port_t port, dio_level_t value);
#define dio_toggle(dio) dio_set_level(dio, !dio_get_level(dio))
// only macro work; compiler is angy
#define dio_pulse(dio, delay) \
    dio_toggle(dio);          \
    _delay_us(delay);         \
    dio_toggle(dio)
void dio_off();

#endif

// typedef struct dio_t {
//     dio_port_t port;
//     dio_pin_t pin;
// } dio_t;

// #define _dio(address, pin_num)  (dio_t){.port = address, .pin = pin_num}

// #define DIO_PA0 _dio(DIO_PORTA, DIO_PIN0)
// #define DIO_PA1 _dio(DIO_PORTA, DIO_PIN1)
// #define DIO_PA2 _dio(DIO_PORTA, DIO_PIN2)
// #define DIO_PA3 _dio(DIO_PORTA, DIO_PIN3)
// #define DIO_PA4 _dio(DIO_PORTA, DIO_PIN4)
// #define DIO_PA5 _dio(DIO_PORTA, DIO_PIN5)
// #define DIO_PA6 _dio(DIO_PORTA, DIO_PIN6)
// #define DIO_PA7 _dio(DIO_PORTA, DIO_PIN7)
// #define DIO_PB0 _dio(DIO_PORTB, DIO_PIN0)
// #define DIO_PB1 _dio(DIO_PORTB, DIO_PIN1)
// #define DIO_PB2 _dio(DIO_PORTB, DIO_PIN2)
// #define DIO_PB3 _dio(DIO_PORTB, DIO_PIN3)
// #define DIO_PB4 _dio(DIO_PORTB, DIO_PIN4)
// #define DIO_PB5 _dio(DIO_PORTB, DIO_PIN5)
// #define DIO_PB6 _dio(DIO_PORTB, DIO_PIN6)
// #define DIO_PB7 _dio(DIO_PORTB, DIO_PIN7)
// #define DIO_PC0 _dio(DIO_PORTC, DIO_PIN0)
// #define DIO_PC1 _dio(DIO_PORTC, DIO_PIN1)
// #define DIO_PC2 _dio(DIO_PORTC, DIO_PIN2)
// #define DIO_PC3 _dio(DIO_PORTC, DIO_PIN3)
// #define DIO_PC4 _dio(DIO_PORTC, DIO_PIN4)
// #define DIO_PC5 _dio(DIO_PORTC, DIO_PIN5)
// #define DIO_PC6 _dio(DIO_PORTC, DIO_PIN6)
// #define DIO_PC7 _dio(DIO_PORTC, DIO_PIN7)
// #define DIO_PD0 _dio(DIO_PORTD, DIO_PIN0)
// #define DIO_PD1 _dio(DIO_PORTD, DIO_PIN1)
// #define DIO_PD2 _dio(DIO_PORTD, DIO_PIN2)
// #define DIO_PD3 _dio(DIO_PORTD, DIO_PIN3)
// #define DIO_PD4 _dio(DIO_PORTD, DIO_PIN4)
// #define DIO_PD5 _dio(DIO_PORTD, DIO_PIN5)
// #define DIO_PD6 _dio(DIO_PORTD, DIO_PIN6)
// #define DIO_PD7 _dio(DIO_PORTD, DIO_PIN7)