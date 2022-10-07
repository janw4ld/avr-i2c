#include "psc.h"

uint8_t psc_select(psc_scale scale, psc_mode mode) {
    // it looks like trash to avoid dynamic allocation
    switch (mode) {
        case PSC0: {
            const psc_scale psc[psc0_max] = psc0;
            const uint8_t max = psc0_max;
            for (uint8_t prescaler = 0; prescaler < max; prescaler++) {
                if (psc[prescaler] == scale)
                    return prescaler;
            }
            break;
        }
        case PSC1: {
            const psc_scale psc[psc1_max] = psc1;
            const uint8_t max = psc1_max;
            for (uint8_t prescaler = 0; prescaler < max; prescaler++) {
                if (psc[prescaler] == scale)
                    return prescaler;
            }  
            break;
        }
        case PSCA: {
            const psc_scale psc[psca_max] = psca;
            const uint8_t max = psca_max;
            for (uint8_t prescaler = 0; prescaler < max; prescaler++) {
                if (psc[prescaler] == scale)
                    return prescaler;
            }
            break;
        }
        case SCK: {
            const psc_scale psc[pscs_max] = pscs;
            const uint8_t max = pscs_max;
            for (uint8_t prescaler = 0; prescaler < max; prescaler++) {
                if (psc[prescaler] == scale)
                    return prescaler;
            }
            break;
        }
        case SCL: {
            const psc_scale psc[psci_max] = psci;
            const uint8_t max = psci_max;
            for (uint8_t prescaler = 0; prescaler < max; prescaler++) {
                if (psc[prescaler] == scale)
                    return prescaler;
            }
            break;
        }
        default:
            break;
    }
}
/* const psc_t psc = psc_construct(mode);
uint8_t max = psc.max;
psc_scale trash[max] = (psc.available_scales);
uint8_t prescaler;
for (prescaler = 0; prescaler < max; prescaler++) {
    if (trash[prescaler] == scale)
        return prescaler;
}
} */
/*
  uint8_t value = 0;
  switch (mode) {
      case PSC0: {
          psc_scale psc[] = {0, 1, 8, 64, 256, 1024};
          for (value = PSC0_OFF; value <= PSC0_1024; value++) {
              if (scale == psc[value])
                  break;
          }
          break;
      }
      case PSC1: {
          psc_scale psc[] = {0, 1, 8, 32, 64, 128, 256, 1024};
          for (value = PSC1_OFF; value <= PSC1_1024; value++) {
              if (scale == psc[value])
                  break;
          }
          break;
      }
      case PSCA: {
          psc_scale psc[] = {2, 2, 4, 8, 16, 32, 64, 128};
          for (value = PSCA_DEF; value <= PSCA_128; value++) {
              if (scale == psc[value])
                  break;
          }
          break;
      }
      case SCK: {
          psc_scale psc[] = {4, 16, 64, 128, 2, 8, 32};
          for (value = SCK_4; value <= SCK_32; value++) {
              if (scale == psc[value])
                  break;
          }
          break;
      }
      case SCL: {
          psc_scale psc[] = {1, 4, 16, 64};
          for (value = SCL_1; value <= SCL_64; value++) {
              if (scale == psc[value])
                  break;
          }
          break;
      }
      default:
          break;
  }
  return value;
}  */
/*
    psc_t psc_construct(psc_mode mode) {
        switch (mode) {
            case PSC0: {
                const psc_t psc = {
                    .available_scales = (psc_scale[psc0_max])psc0,
                    .max = psc0_max};
                return psc;
                break;
            }
            case PSC1: {
                const psc_t psc = {
                    .available_scales = (psc_scale[psc1_max])psc1,
                    .max = psc1_max};
                return psc;
                break;
            }
            case PSCA: {
                const psc_t psc = {
                    .available_scales = (psc_scale[psca_max])psca,
                    .max = psca_max};
                return psc;
                break;
            }
            case SCK: {
                const psc_t psc = {
                    .available_scales = (psc_scale[pscs_max])pscs,
                    .max = pscs_max};
                return psc;
                break;
            }
            case SCL: {
                const psc_t psc = {
                    .max = psci_max,
                    .available_scales = (psc_scale[psci_max])psci};
                return psc;
                break;
            }
            default:
                break;
        }
    } */