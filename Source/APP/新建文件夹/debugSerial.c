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
  调试串口
*********************************************************************************************************/
#define UART_PORT      0   // PIO0_1(RXD0) PIO0_2(TXD0)		/* 定义使用的UART端口           */

#if (UART_PORT == 0)
#define DBG_UART      LPC_UART0
#define DBG_UART_RXD  IOCON_UART_RXD0_LOC0
#define DBG_UART_TXD  IOCON_UART_TXD0_LOC0

#elif (UART_PORT == 1)
#define DBG_UART      LPC_UART1
#define DBG_UART_RXD  IOCON_UART_RXD1_LOC0
#define DBG_UART_TXD  IOCON_UART_TXD1_LOC0
#endif


#define UART_BPS       9600                                             /*  串口通信波特率              */

/*  dzx
extern void UART_IntHandler (LPC_UART_TypeDef *UARTx);
extern void uartInit (void);
extern void uartSendStr (uint8_t *pucStr, uint32_t ulNum);
*/



/*********************************************************************************************************
  全局变量定义
*********************************************************************************************************/
__IO uint8_t GucUartRcvNew;                                                 /*  串口接收新数据的标志        */
uint8_t      GucUartRcvBuf[16];                                             /*  串口接收数据缓冲区          */
uint8_t      GulNum;                                                    /*  串口接收数据的个数          */



/*********************************************************************************************************
* Function Name:        UART_IntHandler
* Description:          UART中断服务函数
* Input:                无
* Output:               无
* Return:               无
*********************************************************************************************************/
void UART_IntHandler (LPC_UART_TypeDef *UARTx)
{
    uint32_t tmp;
    uint16_t intsrc;

    intsrc = UART_GetINTStatus(UARTx);                                  /* 读取中断状态                 */
    tmp = intsrc & 0xE;                                                     

    GulNum = 0;

    if (tmp & (UART_INTSTAT_RX_DATA_AVAILABLE | 
                  UART_INTSTAT_RX_TIMEOUT) ) {
        switch (tmp) {
            case UART_INTSTAT_RX_DATA_AVAILABLE:                        /*  接收数据中断                */
                GucUartRcvNew = 1;                                          /*  置接收新数据标志            */
                                                                        /*  连续接收8个字节             */
                GulNum = UART_Receive(DBG_UART, GucUartRcvBuf, 8, UART_BLOKING_TIMEOUT);              
                break;
            
            case UART_INTSTAT_RX_TIMEOUT:
                GucUartRcvNew = 1;                                          /*  判断数据是否接收完毕        */
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
** Descriptions:        串口初始化，设置为8位数据位，1位停止位，无奇偶校验，波特率为9600
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void uartInit (void)
{
    UART_CFG_Type      UARTConfigStruct;
    IOCON_PIO_CFG_Type PIO_mode;

    IOCON_StructInit(&PIO_mode);          					            /* 设置引脚为TXD、RXD功能       */

    PIO_mode.type = DBG_UART_RXD;
    IOCON_SetFunc(&PIO_mode);

    PIO_mode.type = DBG_UART_TXD;
    IOCON_SetFunc(&PIO_mode);
        
#if (UART_PORT == 0)                                                    /* 打开UART时钟模块             */
    SYS_ResetPeripheral(SYS_PRESETCTRL_UART0_RST,DISABLE);
    SYS_ConfigAHBCLK(SYS_AHBCLKCTRL_UART0, ENABLE); 
    SYS_SetUART0ClockDiv(1);                                            /* 设置分频系数                 */
#endif

#if (UART_PORT == 1)
    SYS_ResetPeripheral(SYS_PRESETCTRL_UART1_RST,DISABLE);
    SYS_ConfigAHBCLK(SYS_AHBCLKCTRL_UART1, ENABLE); 
    SYS_SetUART1ClockDiv(1);
#endif
    
    UART_Init(DBG_UART);                                               /* 使能UART                     */

    UART_GetConfig(DBG_UART, &UARTConfigStruct);                       /* 将参数赋值给UARTConfigStruct */
    UARTConfigStruct.baudrate = UART_BPS;                               /* 设置波特率                   */
    UARTConfigStruct.databits = UART_CFG_DATABIT_8;                     /* 设置为8位数据                */
    UARTConfigStruct.fifolevel = UART_CFG_FIFOTRG_8;                    /* 设置FIFO触发点为8            */

    UART_SetConfig(DBG_UART, &UARTConfigStruct);                       /* 更新配置参数                 */
    UART_ConfigTXD(DBG_UART, ENABLE);                                  /* 使能发送功能                 */

    UART_ConfigInts(DBG_UART, UART_INTCFG_RBR, ENABLE);                /* 使能接收中断                 */

#if (UART_PORT == 0)
    NVIC_EnableIRQ(UART0_IRQn);                                         /* 使能NVIC中断通道             */
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
    UART_Send(DBG_UART, &ucDat, 1, UART_BLOKING_TIMEOUT);              /* 写入数据                     */
    while (!(UART_GetLineStatus(DBG_UART) & UART_LS_TX_EMPTY_ALL));    /* 等待数据发送完毕             */
}

/**
  * @brief  Coprocessor M0 notifies the CPU S3C2440   
  *
  * @param  None
  * @retval   None
**/
void uartSendStr (uint8_t *pucStr, uint32_t ulNum)
{
    for (; ulNum > 0; ulNum--) {                                       /*  发送指定个字节数据          */
        uartSendByte(*pucStr++);
    }
}

void UART0_IRQHandler(void)
{
	UART_IntHandler(LPC_UART0);	
}
