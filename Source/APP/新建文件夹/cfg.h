#ifndef _CFG_H_
#define _CFG_H_

#define YES 	1
#define NO  	0

#define REMP_RAM		0x10000000			/* RAM���׵�ַ,8KB�ռ�*/
#define	APP_LOW			0x00007000			/* LOW���׵�ַ,48KB�ռ�*/
#define	APP_HIGH		0x00015000			/* HIGH���׵�ַ,48KB�ռ�*/
#define APP_INIT		0xFFFFFFFF			/* Ĭ������ֵ*/
/* �û�����������4KB�ռ�*/
#define IAPDATA_FLAG 			0x00006000 				/* IAP��̱�־��ַ*/
#define APPLOW_LENGTH_FLAG		0x00006004				/* �����û�����ĳ��ȵ�ַ*/
#define APPLOW_CRC_FLAG			0x00006008				/* �����û������CRCУ��ֵ��ַ*/
#define APPLOW_SOFTVER_FLAG		0x0000600c				/* �����û����������汾�ŵ�ַ*/

#define	USER_FLAG				0x00014000				/* �û������־����ַ*/
#define HARDVER_FLAG			0x00014004				/* �û������Ӳ���汾�ŵ�ַ*/
#define APPHIGH_LENGTH_FLAG		0x00014008				/* �����û�����ĳ��ȵ�ַ*/
#define APPHIGH_CRC_FLAG		0x0001400c				/* �����û������CRCУ��ֵ��ַ*/
#define APPHIGH_SOFTVER_FLAG	0x00014010				/* �����û����������汾�ŵ�ַ*/

#define LOW_PAGE_ADDR			APP_LOW/512
#define HIGH_PAGE_ADDR			APP_HIGH/512
#define USER_PAGE_ADDR			USER_FLAG/512
#define IAPDATA_PAGE_ADDR   	IAPDATA_FLAG/512

#define DEBUG_UART

#define IAP_FLAG_CHECK			0x00000001
#define APP_DEFLENGTH			0x0000c000				/* ���������ݳ���Ϊ48Kbit*/

#define __BUILD_WITH_EXAMPLE__

#endif
