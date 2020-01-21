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


static uint16_t GusGPIO1Port[7] ={/* GPIO1�˿���������            */
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



	// ���̱����Դ����
    IOCON_StructInit(&PIO_mode);/* ��ʼ���˿�ģʽ               */
    PIO_mode.type = EN_PWR_KEYBL_PIN_TYPE;
    IOCON_SetFunc(&PIO_mode); /* ����BL��������ΪGPIO����        */
    GPIO_SetDir(EN_PWR_KEYBL_PORT, EN_PWR_KEYBL_PIN, GPIO_DIR_OUTPUT); /* ����BL��������Ϊ���            */


#if 1

	// KEY_ESC_PWR��������
    IOCON_StructInit(&PIO_mode);
    PIO_mode.type =  GusGPIO1Port[KEY_ESC_PWR];/* ����KEY_ESC_PWR����ΪGPIO����        */
    IOCON_SetFunc(&PIO_mode);
    GPIO_SetDir(KEY_PORT, KEY_ESC_PWR, GPIO_DIR_INPUT);			/* ����Ϊ����                   */
  //  GPIO_IntSetType(KEY_PORT, KEY_ESC_PWR, GPIO_INTERRUPT_FALLING);	/* ����Ϊ�½��ش��� */
//    GPIO_IntSetMask(KEY_PORT, KEY_ESC_PWR, GPIO_MASK_MASKED);		/* �����ж� */
    
	// KEY_ENTER��������
    IOCON_StructInit(&PIO_mode);
    PIO_mode.type =  GusGPIO1Port[KEY_ENTER];/* ����KEY_ENTER����ΪGPIO����        */
    IOCON_SetFunc(&PIO_mode);
    GPIO_SetDir(KEY_PORT, KEY_ENTER, GPIO_DIR_INPUT);			/* ����Ϊ����                   */
  //  GPIO_IntSetType(KEY_PORT, KEY_ENTER, GPIO_INTERRUPT_FALLING);	/* ����Ϊ�½��ش��� */
//    GPIO_IntSetMask(KEY_PORT, KEY_ENTER, GPIO_MASK_MASKED);		/* �����ж�                   */
	// KEY_LEFT��������
    IOCON_StructInit(&PIO_mode);
    PIO_mode.type =  GusGPIO1Port[KEY_LEFT];/* ����KEY_LEFT����ΪGPIO����        */
    IOCON_SetFunc(&PIO_mode);
    GPIO_SetDir(KEY_PORT, KEY_LEFT, GPIO_DIR_INPUT);			/* ����Ϊ����                   */
   // GPIO_IntSetType(KEY_PORT, KEY_LEFT, GPIO_INTERRUPT_FALLING);	/* ����Ϊ�½��ش��� */
	 #ifdef _GPIO_INT
    GPIO_IntSetMask(KEY_PORT, KEY_LEFT, GPIO_MASK_MASKED);		/* �����ж� */
   #endif
// KEY_RIGHT��������
    IOCON_StructInit(&PIO_mode);
    PIO_mode.type =  GusGPIO1Port[KEY_RIGHT];/* ����KEY_RIGHT����ΪGPIO����        */
    IOCON_SetFunc(&PIO_mode);
    GPIO_SetDir(KEY_PORT, KEY_RIGHT, GPIO_DIR_INPUT);			/* ����Ϊ����                   */
  //  GPIO_IntSetType(KEY_PORT, KEY_RIGHT, GPIO_INTERRUPT_FALLING);	/* ����Ϊ�½��ش��� */
	#ifdef _GPIO_INT
    GPIO_IntSetMask(KEY_PORT, KEY_RIGHT, GPIO_MASK_MASKED);		/* �����ж� */
	#endif

	// KEY_UP��������
    IOCON_StructInit(&PIO_mode);
    PIO_mode.type =  GusGPIO1Port[KEY_UP];/* ����KEY_UP����ΪGPIO����        */
    IOCON_SetFunc(&PIO_mode);
    GPIO_SetDir(KEY_PORT, KEY_UP, GPIO_DIR_INPUT);			/* ����Ϊ����                   */
  //  GPIO_IntSetType(KEY_PORT, KEY_UP, GPIO_INTERRUPT_FALLING);	/* ����Ϊ�½��ش��� */
	#ifdef _GPIO_INT
    GPIO_IntSetMask(KEY_PORT, KEY_UP, GPIO_MASK_MASKED);		/* �����ж� */
	#endif

	// KEY_DOWN��������
    IOCON_StructInit(&PIO_mode);
    PIO_mode.type =  GusGPIO1Port[KEY_DOWN];/* ����KEY_DOWN����ΪGPIO����        */
    IOCON_SetFunc(&PIO_mode);
    GPIO_SetDir(KEY_PORT, KEY_DOWN, GPIO_DIR_INPUT);			/* ����Ϊ����                   */
  //  GPIO_IntSetType(KEY_PORT, KEY_DOWN, GPIO_INTERRUPT_FALLING);	/* ����Ϊ�½��ش��� */
	#ifdef _GPIO_INT
    GPIO_IntSetMask(KEY_PORT, KEY_DOWN, GPIO_MASK_MASKED);		/* �����ж� */
	#endif

#endif


   // NVIC_EnableIRQ(EINT1_IRQn);	/* ʹ���ⲿ�ж�1�ж� */
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



