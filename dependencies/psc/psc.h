#ifndef _PSC_H
#define _PSC_H
#include <stdint.h>

typedef enum psc_mode {
    PSC0,  // timer{0,1}
    PSC1,  // timer2
    PSCA,  // adc prescaler
    SCK,   // spi prescaler
    SCL    // i2c prescaler
} psc_mode;

typedef enum psc_scale {
    PSC_OFF = 0,
    PSC_1 = 1,
    PSC_2 = 2,
    PSC_4 = 4,
    PSC_8 = 8,
    PSC_16 = 16,
    PSC_32 = 32,
    PSC_64 = 64,
    PSC_128 = 128,
    PSC_256 = 256,
    PSC_1024 = 1024,
    psc_mask = 0b111
} psc_scale;

/* prescaler scales ordered by their corresponding values */
#define psc0 \
    { PSC_OFF, PSC_1, PSC_8, PSC_64, PSC_256, PSC_1024 }
#define psc0_max 6

#define psc1 \
    { PSC_OFF, PSC_1, PSC_8, PSC_32, PSC_64, PSC_128, PSC_256, PSC_1024 }
#define psc1_max 8
// adc prescaler
#define psca \
    { PSC_2, PSC_2, PSC_4, PSC_8, PSC_16, PSC_32, PSC_64, PSC_128 }
#define psca_max 8
// spi prescaler
#define pscs \
    { PSC_4, PSC_16, PSC_64, PSC_128, PSC_2, PSC_8, PSC_32 }
#define pscs_max 7
// i2c prescaler
#define psci \
    { PSC_1, PSC_4, PSC_16, PSC_64 }
#define psci_max 4

uint8_t psc_select(psc_scale scale, psc_mode mode);

#endif