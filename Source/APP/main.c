#include <string.h>
#include <stdio.h>  						

#include "dzx_maincfg.h"

#ifdef __BUILD_WITH_EXAMPLE__
#include "lpc12xx_libcfg.h"
#else
#include "lpc12xx_libcfg_default.h"
#endif /* __BUILD_WITH_EXAMPLE__ */


/*********************************************************************************************************
      MACRO DEFINE
*********************************************************************************************************/
#define UART_PORT      0                                                 /* define UART PORT           */
   
#if (UART_PORT == 0)
#define TEST_UART      LPC_UART0
#define TEST_UART_RXD  IOCON_UART_RXD0_LOC0
#define TEST_UART_TXD  IOCON_UART_TXD0_LOC0
   
#elif (UART_PORT == 1)
#define TEST_UART      (LPC_UART_TypeDef *)LPC_UART1
#define TEST_UART_RXD  IOCON_UART_RXD1_LOC0
#define TEST_UART_TXD  IOCON_UART_TXD1_LOC0
#endif
   
#define UART_BPS       115200                                             /*    baudrate  Bps              */
   
/*********************************************************************************************************
      Global variables 
*********************************************************************************************************/
__IO uint8_t GucRcvNew;									/*  uart receive flag  */															
uint8_t GucRcvBuf[10];								/*  uart receive buffer  */
uint8_t GulNum;											/*  uart receive Byte number  */  	
/*********************************************************************************************************
** Function name:       myDelay
** Descriptions:        software delay(ms)
** input parameters:    no
** output parameters:   no
** Returned value:      no
*********************************************************************************************************/
void myDelay (uint32_t ulTime)
{
    uint32_t i = 0;
   
    while (ulTime--)
			{
        for (i = 0; i < 500; i++);
    }
}

/*********************************************************************************************************
* Function Name:        UART_IntHandler
* Description:          UART Interrupt Service
* Input:                no
* Output:               no
* Return:               no
*********************************************************************************************************/
//#if (UART_PORT == 0)
//#define LPC_UART_TypeDef_TEST LPC_UART0_TypeDef
//#endif

//#if (UART_PORT == 1)
//#define LPC_UART_TypeDef_TEST LPC_UART1_TypeDef
//#endif

//void UART_IntHandler (LPC_UART_TypeDef_TEST *UARTx)
//{
//    uint32_t tmp;
//    uint16_t intsrc;
//	
//    intsrc = UART_GetINTStatus((LPC_UART_TypeDef *)UARTx);                                  /*                  */
//    tmp = intsrc & 0xE;                                                    

//    GulNum = 0;

//    if (tmp & (UART_INTSTAT_RX_DATA_AVAILABLE |
//                  UART_INTSTAT_RX_TIMEOUT) ) {
//        switch (tmp) {
//            case UART_INTSTAT_RX_DATA_AVAILABLE:                        /*                */
//                GucRcvNew = 1;                                          /*                */
//                                                                        /*                */
//                 GulNum = UART_Receive(TEST_UART, GucRcvBuf, 8, UART_BLOKING_TIMEOUT);             
//                 break;
//            
//             case UART_INTSTAT_RX_TIMEOUT:
//                 GucRcvNew = 1;                                          /*              */
//                 while (UARTx->LSR & UART_LS_RX_DATA_READY) {
//                     UART_Receive(TEST_UART, &GucRcvBuf[GulNum], 1, UART_NO_TIMEOUT);
//                     GulNum++;
//                 }
//                 break;
//            
//             default :
//                 break;
//         }
//     }
// }

// #if (UART_PORT == 0)
// void UART0_IRQHandler(void)
// {
//     UART_IntHandler(LPC_UART0);
// }
// #endif

// #if (UART_PORT == 1)
// void UART1_IRQHandler(void)
// {
//     UART_IntHandler(LPC_UART1);
// }
// #endif

 /*********************************************************************************************************
 ** Function name:       uartInit
 ** Descriptions:        串口初始化，设置为8位数据位，1位停止位，无奇偶校验，波特率为9600
 ** input parameters:    无
 ** output parameters:   无
 ** Returned value:      无
 *********************************************************************************************************/
 void uartInit (void)
 {
     UART_CFG_Type      UART_ConfigStruct;
     IOCON_PIO_CFG_Type PIO_mode;

     IOCON_StructInit(&PIO_mode);                                          /* init PIO_mode 设置引脚为TXD、RXD功能       */

     PIO_mode.type = TEST_UART_RXD;																				/* set type value for PIO0_1 to RXD0 */	 
     IOCON_SetFunc(&PIO_mode);																						/* Set IOCON register (type include address) */

     PIO_mode.type = TEST_UART_TXD;
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
    
     UART_Init(TEST_UART);                                               /* 使能UART                     */

     UART_GetConfig(TEST_UART, &UART_ConfigStruct);                       /* 将参数赋值给UARTConfigStruct */
     UART_ConfigStruct.baudrate = UART_BPS;                               /* 设置波特率                   */
//     UART_ConfigStruct.databits = UART_CFG_DATABIT_8;                     /* 设置为8位数据                */
//     UART_ConfigStruct.fifolevel = UART_CFG_FIFOTRG_8;                    /* 设置FIFO触发点为8            */

     UART_SetConfig(TEST_UART, &UART_ConfigStruct);                       /* 更新配置参数                 */
     UART_ConfigTXD(TEST_UART, ENABLE);                                  /* 使能发送功能                 */
//		 UART_ConfigTXD(TEST_UART, DISABLE);

     UART_ConfigInts(TEST_UART, UART_INTCFG_RBR, ENABLE);                /* 使能接收中断                 */

 #if (UART_PORT == 0)
     NVIC_EnableIRQ(UART0_IRQn);                                         /* 使能NVIC中断通道             */
 #endif
    
 #if (UART_PORT == 1)
     NVIC_EnableIRQ(UART1_IRQn);
 #endif  
 }

/*********************************************************************************************************
** Function name:       uartSendByte
** Descriptions:        向串口发送字节数据，并等待数据发送完成，使用查询方式
** input parameters:    ucDat:   要发送的数据
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void uartSendByte (uint8_t ucDat)
{
    UART_Send(TEST_UART, &ucDat, 1, UART_BLOKING_TIMEOUT);              /* 写入数据                     */
    while (!(UART_GetLineStatus(TEST_UART) & UART_LS_TX_EMPTY_ALL));    /* 等待数据发送完毕             */
}

/*********************************************************************************************************
** Function name:       uartSendStr
** Descriptions:        向串口发送字符串
** input parameters:    pucStr:  要发送的字符串指针
**                      ulNum:   要发送的数据个数
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void uartSendStr (uint8_t *pucStr, uint32_t ulNum)
{
    for (; ulNum > 0; ulNum--) {                                       /*  发送指定个字节数据          */
        uartSendByte(*pucStr++);
    }
}


/*********************************************************************************************************
** Function name:       main
** Descriptions:        主函数(函数入口)
**     串口参数：       UART波特率9600、8个数据位、1个停止位、无奇偶校验位
**     跳线连接：       P0.8(RXD1)、P0.9(TXD1)(若使用UART0则连接P0.1(RXD0)和P0.2(TXD0))通过232电平
**                      转换芯片分别连接到PC机串口的TXD、RXD；
**     操作方法：       打开串口调试软件，运行程序，向下位机发送n字节数据，观察显示窗口
**     现    象：       串口调试软件显示下位机返回的数据
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
int main (void)
{
    uint8_t  ucBuf[10];
 	  uint8_t  *AAA;
	  uint32_t n=10;
	  uint32_t m;
    uartInit();                                                         /*  串口初始化                  */
   
		
	  
	  while(n)
		{
			AAA = (uint8_t *)"abc";
			m= strlen((char *)AAA);
			
			sprintf((char *)ucBuf, "%d ", m);
			uartSendStr(ucBuf, 3);
			
			UART_Send(TEST_UART,AAA,m,UART_BLOKING_TIMEOUT);
			
			myDelay(100);
			n--;
		}
		
	  uartSendStr((uint8_t *)"\r\n", 2);
    sprintf((char *)ucBuf, "UART%d", UART_PORT);
		uartSendStr(ucBuf, 5); 
		
		uartSendStr((uint8_t *)"\r\n", 2);
                                                 /* 打印输出                     */
    uartSendStr((uint8_t *)"check way test\r\n", 14);
    myDelay(1);   

    while (1) { 
        if (1 == GucRcvNew) {                                           /*  判断是否有新数据            */
            GucRcvNew = 0;                                              /*  清除标志                    */
            uartSendStr(GucRcvBuf, GulNum);                             /*  向串口发送数据              */
        }
    } 
}

#ifdef  DEBUG
/*********************************************************************************************************
** Function name:       check_failed
** Descriptions:
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void check_failed (uint8_t *file, uint32_t line)
{
    while(1);                                                           /* Infinite loop                */
}

#endif

/*********************************************************************************************************
End Of File
***************************************************************/


/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */

