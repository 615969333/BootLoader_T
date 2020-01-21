/**************************************************************************//**
 * $Id: SPISlave.c 2011-06-23 09:26:20 $
 *
 * @file     SPISlave.c
 * @brief    SAC-PDS SPI Slave protocol
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
 
#include "debugSerial.h"

/*********************************************************************************************************
  ���Դ���
*********************************************************************************************************/
#define UART_PORT      0   // PIO0_1(RXD0) PIO0_2(TXD0)		/* ����ʹ�õ�UART�˿�           */

#if (UART_PORT == 0)
#define DBG_UART      LPC_UART0
#define DBG_UART_RXD  IOCON_UART_RXD0_LOC0
#define DBG_UART_TXD  IOCON_UART_TXD0_LOC0

#elif (UART_PORT == 1)
#define DBG_UART      LPC_UART1
#define DBG_UART_RXD  IOCON_UART_RXD1_LOC0
#define DBG_UART_TXD  IOCON_UART_TXD1_LOC0
#endif


#define UART_BPS       9600                                             /*  ����ͨ�Ų�����              */

/*  dzx
extern void UART_IntHandler (LPC_UART_TypeDef *UARTx);
extern void uartInit (void);
extern void uartSendStr (uint8_t *pucStr, uint32_t ulNum);
*/



/*********************************************************************************************************
  ȫ�ֱ�������
*********************************************************************************************************/
__IO uint8_t GucUartRcvNew;                                                 /*  ���ڽ��������ݵı�־        */
uint8_t      GucUartRcvBuf[16];                                             /*  ���ڽ������ݻ�����          */
uint8_t      GulNum;                                                    /*  ���ڽ������ݵĸ���          */



/*********************************************************************************************************
* Function Name:        UART_IntHandler
* Description:          UART�жϷ�����
* Input:                ��
* Output:               ��
* Return:               ��
*********************************************************************************************************/
void UART_IntHandler (LPC_UART_TypeDef *UARTx)
{
    uint32_t tmp;
    uint16_t intsrc;

    intsrc = UART_GetINTStatus(UARTx);                                  /* ��ȡ�ж�״̬                 */
    tmp = intsrc & 0xE;                                                     

    GulNum = 0;

    if (tmp & (UART_INTSTAT_RX_DATA_AVAILABLE | 
                  UART_INTSTAT_RX_TIMEOUT) ) {
        switch (tmp) {
            case UART_INTSTAT_RX_DATA_AVAILABLE:                        /*  ���������ж�                */
                GucUartRcvNew = 1;                                          /*  �ý��������ݱ�־            */
                                                                        /*  ��������8���ֽ�             */
                GulNum = UART_Receive(DBG_UART, GucUartRcvBuf, 8, UART_BLOKING_TIMEOUT);              
                break;
            
            case UART_INTSTAT_RX_TIMEOUT:
                GucUartRcvNew = 1;                                          /*  �ж������Ƿ�������        */
                while (UARTx->LSR & UART_LS_RX_DATA_READY) { 
                    UART_Receive(DBG_UART, &GucUartRcvBuf[GulNum], 1, UART_NO_TIMEOUT);
                    GulNum++;
                }
                break;
            
            default :
                break;
        }
    }
}


/*********************************************************************************************************
** Function name:       uartInit
** Descriptions:        ���ڳ�ʼ��������Ϊ8λ����λ��1λֹͣλ������żУ�飬������Ϊ9600
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void uartInit (void)
{
    UART_CFG_Type      UARTConfigStruct;
    IOCON_PIO_CFG_Type PIO_mode;

    IOCON_StructInit(&PIO_mode);          					            /* ��������ΪTXD��RXD����       */

    PIO_mode.type = DBG_UART_RXD;
    IOCON_SetFunc(&PIO_mode);

    PIO_mode.type = DBG_UART_TXD;
    IOCON_SetFunc(&PIO_mode);
        
#if (UART_PORT == 0)                                                    /* ��UARTʱ��ģ��             */
    SYS_ResetPeripheral(SYS_PRESETCTRL_UART0_RST,DISABLE);
    SYS_ConfigAHBCLK(SYS_AHBCLKCTRL_UART0, ENABLE); 
    SYS_SetUART0ClockDiv(1);                                            /* ���÷�Ƶϵ��                 */
#endif

#if (UART_PORT == 1)
    SYS_ResetPeripheral(SYS_PRESETCTRL_UART1_RST,DISABLE);
    SYS_ConfigAHBCLK(SYS_AHBCLKCTRL_UART1, ENABLE); 
    SYS_SetUART1ClockDiv(1);
#endif
    
    UART_Init(DBG_UART);                                               /* ʹ��UART                     */

    UART_GetConfig(DBG_UART, &UARTConfigStruct);                       /* ��������ֵ��UARTConfigStruct */
    UARTConfigStruct.baudrate = UART_BPS;                               /* ���ò�����                   */
    UARTConfigStruct.databits = UART_CFG_DATABIT_8;                     /* ����Ϊ8λ����                */
    UARTConfigStruct.fifolevel = UART_CFG_FIFOTRG_8;                    /* ����FIFO������Ϊ8            */

    UART_SetConfig(DBG_UART, &UARTConfigStruct);                       /* �������ò���                 */
    UART_ConfigTXD(DBG_UART, ENABLE);                                  /* ʹ�ܷ��͹���                 */

    UART_ConfigInts(DBG_UART, UART_INTCFG_RBR, ENABLE);                /* ʹ�ܽ����ж�                 */

#if (UART_PORT == 0)
    NVIC_EnableIRQ(UART0_IRQn);                                         /* ʹ��NVIC�ж�ͨ��             */
#endif
    
#if (UART_PORT == 1)
    NVIC_EnableIRQ(UART1_IRQn);
#endif   
}

/**
  * @brief  Send Byte to the RFID module
  *
  * @param  None
  * @retval   None
**/
void uartSendByte (uint8_t ucDat)
{
    UART_Send(DBG_UART, &ucDat, 1, UART_BLOKING_TIMEOUT);              /* д������                     */
    while (!(UART_GetLineStatus(DBG_UART) & UART_LS_TX_EMPTY_ALL));    /* �ȴ����ݷ������             */
}

/**
  * @brief  Coprocessor M0 notifies the CPU S3C2440   
  *
  * @param  None
  * @retval   None
**/
void uartSendStr (uint8_t *pucStr, uint32_t ulNum)
{
    for (; ulNum > 0; ulNum--) {                                       /*  ����ָ�����ֽ�����          */
        uartSendByte(*pucStr++);
    }
}

void UART0_IRQHandler(void)
{
	UART_IntHandler(LPC_UART0);	
}
