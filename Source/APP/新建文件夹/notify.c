#ifdef __BUILD_WITH_EXAMPLE__
#include "lpc12xx_libcfg.h"
#else
#include "lpc12xx_libcfg_default.h"
#endif /* __BUILD_WITH_EXAMPLE__ */

#include "notify.h"


void notifyInit(void) 
{
	IOCON_PIO_CFG_Type PIO_mode;

    // M0 ���� PIO0.24 �����ж�S3C2440���Ը�֪S3C2440�����¼�
    IOCON_StructInit(&PIO_mode);					/* ��ʼ���˿�ģʽ               */
    PIO_mode.type = IOCON_PIO_0_24;				
    IOCON_SetFunc(&PIO_mode); 					/* ����Notify����ΪGPIO����     */
    GPIO_SetDir(LPC_GPIO0, 24, GPIO_DIR_OUTPUT);		/* ����Notify����Ϊ���         */
}

/**
  * @brief  Coprocessor M0 notifies the CPU S3C2440   
  *
  * @param  None
  * @retval   None
**/
void Notify_S3C2440 (void)
{
	GPIO_SetLowLevel(LPC_GPIO0, 24, ENABLE);
	//az delete
	//SoftDelay(10);
	//GPIO_SetHighLevel(LPC_GPIO0, 24, ENABLE);	
}


/**
  * @brief  disable the notify pin   
  *
  * @param  None
  * @retval   None
**/
void Disable_Notify(void)
{
	GPIO_SetHighLevel(LPC_GPIO0, 24, ENABLE);
}



