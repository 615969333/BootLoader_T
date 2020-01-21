/**************************************************************************//**
 * $Id: keyboard.c 2011-06-23 09:26:20 $
 *
 * @file     keyboard.c
 * @brief    SAC-PDS 6 keys and back-light
 * @version  1.0
 * @date     23. Jun. 2011
 * @author   Top
 *
 * @note
 * Copyright (C) 2011 SAC. All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * SAC assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. SAC ltd.
 * reserves the right to make changes in the software without
 * notification. SAC also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
 ******************************************************************************/

/**************************************************************************//**
 * $Mody Time: 2012-01-20 11:16:03 $
 *
 * @brief    	Use the port 2 back for the keyboard!!
 * @version  	v1.2
 * @date     	20. Jan. 2012
 * @Engineer   	Top@yuejia.net  
 ******************************************************************************/


#include "lpc12xx_iocon.h" 
#include "lpc12xx_gpio.h"
#include "keyboard.h"


static uint16_t GusGPIO1Port[7] ={/* GPIO1端口引脚类型            */
    IOCON_PIO_1_0,
    IOCON_PIO_1_1,
    IOCON_PIO_1_2,
    IOCON_PIO_1_3,
    IOCON_PIO_1_4,
    IOCON_PIO_1_5,
    IOCON_PIO_1_6,
};


#define KEY_PORT_PIN_ARRAY	GusGPIO1Port

#define EN_PWR_KEYBL_PORT		LPC_GPIO1
#define	EN_PWR_KEYBL_PIN_TYPE	IOCON_PIO_1_6
#define	EN_PWR_KEYBL_PIN			6






/**
  * @brief  Initialize the 6-keys keyboard Interrupt mode   
  *
  * @param  None.
  * @retval   None
**/
void KeyBoardINTInit (void)
{
    IOCON_PIO_CFG_Type PIO_mode;



	// 键盘背光电源控制
    IOCON_StructInit(&PIO_mode);/* 初始化端口模式               */
    PIO_mode.type = EN_PWR_KEYBL_PIN_TYPE;
    IOCON_SetFunc(&PIO_mode); /* 设置BL控制引脚为GPIO功能        */
    GPIO_SetDir(EN_PWR_KEYBL_PORT, EN_PWR_KEYBL_PIN, GPIO_DIR_OUTPUT); /* 设置BL控制引脚为输出            */


#if 1

	// KEY_ESC_PWR键的配置
    IOCON_StructInit(&PIO_mode);
    PIO_mode.type =  GusGPIO1Port[KEY_ESC_PWR];/* 配置KEY_ESC_PWR引脚为GPIO功能        */
    IOCON_SetFunc(&PIO_mode);
    GPIO_SetDir(KEY_PORT, KEY_ESC_PWR, GPIO_DIR_INPUT);			/* 配置为输入                   */
  //  GPIO_IntSetType(KEY_PORT, KEY_ESC_PWR, GPIO_INTERRUPT_FALLING);	/* 配置为下降沿触发 */
//    GPIO_IntSetMask(KEY_PORT, KEY_ESC_PWR, GPIO_MASK_MASKED);		/* 屏蔽中断 */
    
	// KEY_ENTER键的配置
    IOCON_StructInit(&PIO_mode);
    PIO_mode.type =  GusGPIO1Port[KEY_ENTER];/* 配置KEY_ENTER引脚为GPIO功能        */
    IOCON_SetFunc(&PIO_mode);
    GPIO_SetDir(KEY_PORT, KEY_ENTER, GPIO_DIR_INPUT);			/* 配置为输入                   */
  //  GPIO_IntSetType(KEY_PORT, KEY_ENTER, GPIO_INTERRUPT_FALLING);	/* 配置为下降沿触发 */
//    GPIO_IntSetMask(KEY_PORT, KEY_ENTER, GPIO_MASK_MASKED);		/* 屏蔽中断                   */
	// KEY_LEFT键的配置
    IOCON_StructInit(&PIO_mode);
    PIO_mode.type =  GusGPIO1Port[KEY_LEFT];/* 配置KEY_LEFT引脚为GPIO功能        */
    IOCON_SetFunc(&PIO_mode);
    GPIO_SetDir(KEY_PORT, KEY_LEFT, GPIO_DIR_INPUT);			/* 配置为输入                   */
   // GPIO_IntSetType(KEY_PORT, KEY_LEFT, GPIO_INTERRUPT_FALLING);	/* 配置为下降沿触发 */
	 #ifdef _GPIO_INT
    GPIO_IntSetMask(KEY_PORT, KEY_LEFT, GPIO_MASK_MASKED);		/* 屏蔽中断 */
   #endif
// KEY_RIGHT键的配置
    IOCON_StructInit(&PIO_mode);
    PIO_mode.type =  GusGPIO1Port[KEY_RIGHT];/* 配置KEY_RIGHT引脚为GPIO功能        */
    IOCON_SetFunc(&PIO_mode);
    GPIO_SetDir(KEY_PORT, KEY_RIGHT, GPIO_DIR_INPUT);			/* 配置为输入                   */
  //  GPIO_IntSetType(KEY_PORT, KEY_RIGHT, GPIO_INTERRUPT_FALLING);	/* 配置为下降沿触发 */
	#ifdef _GPIO_INT
    GPIO_IntSetMask(KEY_PORT, KEY_RIGHT, GPIO_MASK_MASKED);		/* 屏蔽中断 */
	#endif

	// KEY_UP键的配置
    IOCON_StructInit(&PIO_mode);
    PIO_mode.type =  GusGPIO1Port[KEY_UP];/* 配置KEY_UP引脚为GPIO功能        */
    IOCON_SetFunc(&PIO_mode);
    GPIO_SetDir(KEY_PORT, KEY_UP, GPIO_DIR_INPUT);			/* 配置为输入                   */
  //  GPIO_IntSetType(KEY_PORT, KEY_UP, GPIO_INTERRUPT_FALLING);	/* 配置为下降沿触发 */
	#ifdef _GPIO_INT
    GPIO_IntSetMask(KEY_PORT, KEY_UP, GPIO_MASK_MASKED);		/* 屏蔽中断 */
	#endif

	// KEY_DOWN键的配置
    IOCON_StructInit(&PIO_mode);
    PIO_mode.type =  GusGPIO1Port[KEY_DOWN];/* 配置KEY_DOWN引脚为GPIO功能        */
    IOCON_SetFunc(&PIO_mode);
    GPIO_SetDir(KEY_PORT, KEY_DOWN, GPIO_DIR_INPUT);			/* 配置为输入                   */
  //  GPIO_IntSetType(KEY_PORT, KEY_DOWN, GPIO_INTERRUPT_FALLING);	/* 配置为下降沿触发 */
	#ifdef _GPIO_INT
    GPIO_IntSetMask(KEY_PORT, KEY_DOWN, GPIO_MASK_MASKED);		/* 屏蔽中断 */
	#endif

#endif


   // NVIC_EnableIRQ(EINT1_IRQn);	/* 使能外部中断1中断 */
}

/**
  * @brief  control the keyboard backlight   
  *
  * @param  pwr_on  1 for power on; 0 for power off; others invalid.
  * @retval   None
**/
void KeyBacklightSW (int pwr_on)
{// PIO0_28
	if(POWER_ON==pwr_on){  /* Power-On */
		GPIO_SetHighLevel(EN_PWR_KEYBL_PORT, EN_PWR_KEYBL_PIN, ENABLE);
	}else if (POWER_OFF==pwr_on){	/* Power-off */
		GPIO_SetLowLevel(EN_PWR_KEYBL_PORT, EN_PWR_KEYBL_PIN, ENABLE);
	}else{ /* other values no effect */
	}
}



