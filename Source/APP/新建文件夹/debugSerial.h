#ifndef __debugSerial_H
#define __debugSerial_H

#ifdef __BUILD_WITH_EXAMPLE__
#include "lpc12xx_libcfg.h"
#else
#include "lpc12xx_libcfg_default.h"
#endif /* __BUILD_WITH_EXAMPLE__ */


void uartInit (void);
void uartSendStr (uint8_t *pucStr, uint32_t ulNum);

#endif /* debugSerial.h */
