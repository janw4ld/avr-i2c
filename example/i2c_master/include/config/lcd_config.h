#define _LCD_CONFIG_H

#define LCD_RS_PIN DIO_PD5
#define LCD_EN_PIN DIO_PD4

#define LCD_DATA_PINS \
    {                 \
        DIO_PB0,      \
        DIO_PB1,      \
        DIO_PB2,      \
        DIO_PB3,      \
        DIO_PC4,      \
        DIO_PC5,      \
        DIO_PC6,      \
        DIO_PC7       \
    }

#define LCD_MODE LCD_8BIT_2LINE_MODE

#define LCD_TRACK_POS  // uncomment this for more correct cursor movement
                         // not recommeded since it declares global variables

//#define LCD_DYNALLOC   // don't uncomment this please, thanks

#define LCD_LENGTH 24