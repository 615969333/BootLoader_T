//#include "lpc12xx_libcfg.h"

#ifdef __BUILD_WITH_EXAMPLE__
#include "lpc12xx_libcfg.h"
#else
#include "lpc12xx_libcfg_default.h"
#endif /* __BUILD_WITH_EXAMPLE__ */

uint16_t data_check_sum(uint8_t *data,uint16_t data_length);
