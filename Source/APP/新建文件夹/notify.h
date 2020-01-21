#ifndef __NOTIFY_H__
#define __NOTIFY_H__
//#include "lpc12xx_libcfg.h"

#ifdef __BUILD_WITH_EXAMPLE__
#include "lpc12xx_libcfg.h"
#else
#include "lpc12xx_libcfg_default.h"
#endif /* __BUILD_WITH_EXAMPLE__ */
											  
void notifyInit(void);
/**
  * @brief  Coprocessor M0 notifies the CPU S3C2440   
  *
  * @param  None
  * @retval   None
**/
void Notify_S3C2440 (void);


/**
  * @brief  disable the notify pin   
  *
  * @param  None
  * @retval   None
**/
void Disable_Notify(void);

#endif


