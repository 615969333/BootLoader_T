/**************************************************************************//**
 * $Id: hwTimer.c 2011-10-18 09:26:20 $
 *
 * @file     hwTimer.c
 * @brief    SAC-PDS hardware Timer
 * @version  1.0
 * @date     18 Oct. 2011
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

//#include "lpc12xx_libcfg.h"

#ifdef __BUILD_WITH_EXAMPLE__
#include "lpc12xx_libcfg.h"
#else
#include "lpc12xx_libcfg_default.h"
#endif /* __BUILD_WITH_EXAMPLE__ */


/*********************************************************************************************************
  ȫ�ֱ�������
*********************************************************************************************************/
TIM32_InitTypeDef         TIM32_InitStruct;
TIM32_MATCHTypeDef        TIM32_MatchConfigStruct ;
IOCON_PIO_CFG_Type        PIO_ConfigStructure; 

#define OVER_TIME	800
extern void TimerInit (void);
uint32_t time_cnt = 0;
volatile uint8_t time_over_flag = 0;

/**
 * @brief  initialize the motor hardware timer
 *
 * @param  none
 *
 *
 */	
void TimerInit (void)
{
    SYS_ConfigAHBCLK(SYS_AHBCLKCTRL_CT32B0, ENABLE);                    /* ʹ��32λ��ʱ��ʱ��ģ��       */

    /*
     *  ����Ԥ��Ƶʱ��Ϊ100us
     */
    TIM32_InitStruct.PrescaleOption = TIM32_PRESCALE_USVAL;
    TIM32_InitStruct.PrescaleValue = 100;

    TIM32_MatchConfigStruct.MatchChannel = TIM32_MATCH_CHANNEL0;
    TIM32_MatchConfigStruct.IntOnMatch   = TRUE;                        /* ƥ��ʱ�����ж�               */
    TIM32_MatchConfigStruct.ResetOnMatch = TRUE;                        /* ƥ��ʱMR0��λ                */
    TIM32_MatchConfigStruct.StopOnMatch = FALSE;                        /* ƥ���ֹͣMR0����          */
    TIM32_MatchConfigStruct.ExtMatchOutputType =TIM32_EXTMATCH_NOTHING;  /* ƥ��ʱ��ת�������           */
    TIM32_MatchConfigStruct.MatchValue = 100;                          /* ����ƥ��ֵΪ10ms            */
    TIM32_Init(LPC_TMR32B0, TIM32_MODE_TIMER,&TIM32_InitStruct);
    TIM32_ConfigMatch(LPC_TMR32B0,&TIM32_MatchConfigStruct);
    NVIC_SetPriority(TIMER_32_0_IRQn, ((0x01<<3) | 0x01));              /* �����ж����ȼ�               */
    NVIC_EnableIRQ(TIMER_32_0_IRQn);                                    /* ʹ�ܶ�ʱ���ж�               */
    TIM32_Cmd(LPC_TMR32B0, DISABLE);                                     /* �رն�ʱ��                   */
}



/*********************************************************************************************************
** Function name:       TIMER32_0_IRQHandler
** Descriptions:        32λ��ʱ���жϷ�����
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void TIMER32_0_IRQHandler (void)
{
    uint32_t  int_status_reg;

    int_status_reg = TIM32_GetIntStatusReg (LPC_TMR32B0);               /* ��ȡ�ж�״̬                 */
    if (int_status_reg & TIM32_INT_MR0) 
	{
        TIM32_ClearIntPendingBit(LPC_TMR32B0,TIM32_INT_MR0);            /* ����жϱ�־                 */
		if(time_cnt == OVER_TIME)
		{
			time_cnt = OVER_TIME;
			time_over_flag = 1;
		}
		else
		{
			time_cnt++; 
			time_over_flag = 0;
		}
    }
}
