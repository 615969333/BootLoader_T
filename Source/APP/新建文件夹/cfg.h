#ifndef _CFG_H_
#define _CFG_H_

#define YES 	1
#define NO  	0

#define REMP_RAM		0x10000000			/* RAM区首地址,8KB空间*/
#define	APP_LOW			0x00007000			/* LOW区首地址,48KB空间*/
#define	APP_HIGH		0x00015000			/* HIGH区首地址,48KB空间*/
#define APP_INIT		0xFFFFFFFF			/* 默认区数值*/
/* 用户程序区定义4KB空间*/
#define IAPDATA_FLAG 			0x00006000 				/* IAP编程标志地址*/
#define APPLOW_LENGTH_FLAG		0x00006004				/* 低区用户程序的长度地址*/
#define APPLOW_CRC_FLAG			0x00006008				/* 低区用户程序的CRC校验值地址*/
#define APPLOW_SOFTVER_FLAG		0x0000600c				/* 低区用户程序的软件版本号地址*/

#define	USER_FLAG				0x00014000				/* 用户程序标志区地址*/
#define HARDVER_FLAG			0x00014004				/* 用户程序的硬件版本号地址*/
#define APPHIGH_LENGTH_FLAG		0x00014008				/* 高区用户程序的长度地址*/
#define APPHIGH_CRC_FLAG		0x0001400c				/* 高区用户程序的CRC校验值地址*/
#define APPHIGH_SOFTVER_FLAG	0x00014010				/* 高区用户程序的软件版本号地址*/

#define LOW_PAGE_ADDR			APP_LOW/512
#define HIGH_PAGE_ADDR			APP_HIGH/512
#define USER_PAGE_ADDR			USER_FLAG/512
#define IAPDATA_PAGE_ADDR   	IAPDATA_FLAG/512

#define DEBUG_UART

#define IAP_FLAG_CHECK			0x00000001
#define APP_DEFLENGTH			0x0000c000				/* 升级的数据长度为48Kbit*/

#define __BUILD_WITH_EXAMPLE__

#endif
