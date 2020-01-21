#include "IAP.h"

/*定义系统时钟CCLK值大小，单位为KHz*/
#define		IAP_FCCLK		24000

#define 	IAP_ENTER_ADR   0x1fff1ff1              // IAP入口地址定义

typedef void (*IAP) (uint32_t [], uint32_t []);
IAP IAP_Enter =(IAP) IAP_ENTER_ADR;

uint32_t	paramin[5];		                            // IAP入口参数缓冲区
uint32_t	paramout[5];	                            // IAP出口参数缓冲区

/*********************************************************************************************************
**函数名称：SelSector
**函数功能：IAP操作缓冲区选择，代码为50
**入口参数：sec1	起始扇区
**			sec2	终止扇区
**出口参数：IAP 操作状态码
**			IAP返回值（paramout缓冲区）
********************************************************************************************************/
uint32_t	SelSector(uint32_t sec1, uint32_t sec2)
{
	paramin[0] = IAP_SELECTOR;	                    //设置命令字
	paramin[1] = sec1;			                    //设置参数
	paramin[2] = sec2;
	IAP_Enter(paramin,paramout);	//调用IAP服务程序
	return(paramout[0]);	                        //返回状态码
}
/*********************************************************************************************************
**函数名称：RamToFlash
**函数功能：复制RAM的数据到FLASH，命令代码51
**入口参数：dst		目标地址，即FLASH起始地址，以4字节为分界
**			src		源地址，即RAM地址，地址必须字对其
**			no		复制字节个数，必须为4的倍数
**出口参数：IAP 操作状态码
**			IAP返回值（paramout缓冲区）
********************************************************************************************************/
uint32_t	RamToFlash(uint32_t dst, uint32_t src, uint32_t no)
{
	paramin[0] = IAP_RAMTOFLASH;	                //设置命令字
	paramin[1] = dst;				                //设置参数
	paramin[2] = src;
	paramin[3] = no;
	paramin[4] = IAP_FCCLK;
	IAP_Enter(paramin,paramout);	//调用IAP服务程序
	return(paramout[0]);			                //返回状态码
}
/*********************************************************************************************************
**函数名称：EraseSector
**函数功能：擦除扇区，命令代码52
**入口参数：sec1	起始扇区
**			sec2	终止扇区
**出口参数：IAP 操作状态码
**			IAP返回值（paramout缓冲区）
********************************************************************************************************/
uint32_t	EraseSector(uint32_t sec1, uint32_t sec2)
{
	paramin[0] = IAP_ERASESECTOR;	                //设置命令字
	paramin[1] = sec1;				                //设置参数
	paramin[2] = sec2;
	paramin[3] = IAP_FCCLK;
	IAP_Enter(paramin,paramout);	//调用IAP服务程序
	return(paramout[0]);			                //返回状态码
}
/*********************************************************************************************************
**函数名称：BlankCHK
**函数功能：查空扇区，命令代码53
**入口参数：sec1	起始扇区
**			sec2	终止扇区
**出口参数：IAP 操作状态码
**			IAP返回值（paramout缓冲区）
********************************************************************************************************/
uint32_t	BlankCHK(uint32_t	sec1, uint32_t sec2)
{
	paramin[0] = IAP_BLANKCHK;	//设置命令字
	paramin[1] = sec1;				                //设置参数
	paramin[2] = sec2;
	IAP_Enter(paramin,paramout);	//调用IAP服务程序
	return(paramout[0]);			                //返回状态码
}
/*********************************************************************************************************
**函数名称：ReadParID
**函数功能：读器件ID，命令代码54
**入口参数：器件ID地址指针
**出口参数：IAP 操作状态码
**			IAP返回值（paramout缓冲区）
********************************************************************************************************/
uint32_t	ReadParID(uint32_t *Device_ID)
{
	paramin[0] = IAP_READPARTID;	                //设置命令字
	IAP_Enter(paramin,paramout);	//调用IAP服务程序
	*Device_ID = paramout[1];
	return(paramout[0]);			                //返回状态码
}
/*********************************************************************************************************
**函数名称：BootCodeID
**函数功能：读boot代码ID，命令代码55
**入口参数：boot代码ID地址指针
**出口参数：IAP 操作状态码
**			IAP返回值（paramout缓冲区）
********************************************************************************************************/
uint32_t	BootCodeID(uint32_t *Boot_ID)	
{
	paramin[0] = IAP_BOOTCODEID;	                //设置命令字
	IAP_Enter(paramin,paramout);	//调用IAP服务程序
	*Boot_ID = paramout[1];
	
	return(paramout[0]);			                //返回状态码
}
/*********************************************************************************************************
**函数名称：Compare
**函数功能：校验数据，命令代码56
**入口参数：dst		目标地址，即RAM/FLASH起始地址，地址必须字对齐
**			src		源地址，即RAM/RAM地址，地址必须字对齐
**			no		比较字节个数，必须能被4整除
**出口参数：IAP 操作状态码
**			IAP返回值（paramout缓冲区）
********************************************************************************************************/
uint32_t	Compare(uint32_t	dst,uint32_t	src,uint32_t	no)
{
	paramin[0] = IAP_COMPARE;	                        //设置命令字
	paramin[1] = dst;				                    //设置参数
	paramin[2] = src;
	paramin[3] = no;
	IAP_Enter(paramin,paramout);	//调用IAP服务程序
	return(paramout[0]);			                    //返回状态码
}
/*********************************************************************************************************
**函数名称：Reinvoke_ISP
**函数功能：重新调用ISP，命令代码57。
**入口参数：无
**出口参数：无
********************************************************************************************************/
void  Reinvoke_ISP(void)
{
	paramin[0] = IAP_REINVOKE_ISP;					    // 设置命令字
	IAP_Enter(paramin,paramout);	//调用IAP服务程序
} 
/*********************************************************************************************************
**函数名称：ReadUID
**函数功能：读取唯一的ID，命令代码58。
**入口参数：Unique ID地址指针
**出口参数：无
********************************************************************************************************/
uint32_t  ReadUID(uint32_t *Unique_ID)
{
	paramin[0] = IAP_READUID;					    	// 设置命令字
	IAP_Enter(paramin,paramout);	//调用IAP服务程序
	*Unique_ID = paramout[1];
	*(Unique_ID+1) = paramout[2];
	*(Unique_ID+2) = paramout[3];
	*(Unique_ID+3) = paramout[4];
	return(paramout[0]);			                    //返回状态码
}
/*********************************************************************************************************
**函数名称：ErasePage
**函数功能：擦除页，命令代码59
**入口参数：sec1	起始页
**			sec2	终止页
**出口参数：IAP 操作状态码
**			IAP返回值（paramout缓冲区）
********************************************************************************************************/
uint32_t	ErasePage(uint32_t sec1, uint32_t sec2)
{
	paramin[0] = IAP_ERASEPAGE;	                	//设置命令字
	paramin[1] = sec1;				                //设置参数
	paramin[2] = sec2;
	paramin[3] = IAP_FCCLK;
	IAP_Enter(paramin,paramout);	//调用IAP服务程序
	return(paramout[0]);			                //返回状态码
}
/*********************************************************************************************************
**函数名称：EraseInfoPage
**函数功能：擦除信息页，命令代码60
**入口参数：sec1	起始信息页
**			sec2	终止信息页
**出口参数：IAP 操作状态码
**			IAP返回值（paramout缓冲区）
********************************************************************************************************/
uint32_t	EraseInfoPage(uint32_t sec1, uint32_t sec2)
{
	paramin[0] = IAP_ERASEINFOPAGE;	                //设置命令字
	paramin[1] = sec1;				                //设置参数
	paramin[2] = sec2;
	paramin[3] = IAP_FCCLK;
	IAP_Enter(paramin,paramout);	//调用IAP服务程序
	return(paramout[0]);			                //返回状态码
} 
/*********************************************************************************************************
**函数名称：WriteFlash
**函数功能：向FLASH中写入数据
**入口参数：dst		目标地址，即FLASH起始地址，地址必须以4字节对齐，即地址的低2位必须为0
**			src		源地址，即RAM地址，地址必须字对齐，即地址的低两位必须为0
**			no		写入字节数，必须为4的倍数
**出口参数：Compare的返回值，操作成功正确返回0
********************************************************************************************************/
uint8_t	WriteFlash(uint32_t dst, uint32_t src, uint32_t no)
{
	SelSector((dst/0x1000),(dst+no)/0x1000);	        //选择扇区
	EraseSector((dst/0x1000),(dst+no)/0x1000);	        //擦除扇区
	BlankCHK((dst/0x1000),(dst+no)/0x1000);		        //查空扇区
	
	SelSector((dst/0x1000),(dst+no)/0x1000);	        //选择扇区
	
	RamToFlash(dst,src,no);			                    //写数据到FLASH
	return(Compare(dst,src,no));	                    //比较数据
}
