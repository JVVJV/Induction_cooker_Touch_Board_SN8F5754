//--------------------------------------------------------------------------
//Filename		: captouch_uart.h
//Function		: 
//--------------------------------------------------------------------------
#include "captouch_init.h"

#ifndef		_CAPTOUCH_UART_H_
#define		_CAPTOUCH_UART_H_
//--------------------------------------------------------------------------
#if DEBUG_MODE_UART0	//UARTΩ≈Œª≈‰÷√
	#if (PFGA_UART_UTXD0==1)
			#define P_UTX_HIGH	P12=1
			#define PM_UTX_OUT	P1M |= 0X04
			#define P_URX_HIGH	_nop_()
			#define PM_URX_IN		_nop_()
			#define PUR_URX_ON	_nop_()
			#define UART_SMODMX_SET SMODMX=(SMODMX&(~0X03))|0X02
	#else
			#define P_UTX_HIGH	P03=1
			#define PM_UTX_OUT	P0M |= 0X08
			#define P_URX_HIGH	P02=1
			#define PM_URX_IN		P0M &= (~0X04)
			#define PUR_URX_ON	P0UR |= 0X04
			#define UART_SMODMX_SET SMODMX&=(~0X03)
	#endif
	#if UART_S0REL_125000==0
			#define UART_REL_125000		UART_BR_8M
	#else
			#define UART_REL_125000		UART_BR_4M
	#endif
	
	#define UART_CON			S0CON
	#define UART_BUF			S0BUF
	#define UART_REL			S0REL
	#define UART_SMODCAL	(0x01U<<5)
	#define UART_BDEN			(0x01U<<5)
	#define UART_TEN			(0x01U<<0)
	#define IEN_URX				(0x01U<<3)
	#define IEN_UTX				(0x01U<<2)
	
	#define ISRDebugUtx 	ISRUart0tx
	#define ISRDebugUrx 	ISRUart0rx
//--------------------------------------------------------------------------
#elif DEBUG_MODE_UART1
	#if PFGA_UART_URXD1==1
			#define P_UTX_HIGH	P20=1
			#define PM_UTX_OUT	P2M |= 0X01
			#define P_URX_HIGH	P21=1
			#define PM_URX_IN		P2M &= (~0X02)
			#define PUR_URX_ON	P2UR |= 0X02
			#define UART_SMODMX_SET SMODMX=(SMODMX&(~0X0c))|0X04
	#else
			#define P_UTX_HIGH	P32=1
			#define PM_UTX_OUT	P3M |= 0X04
			#define P_URX_HIGH	P33=1
			#define PM_URX_IN		P3M &= (~0X08)
			#define PUR_URX_ON	P3UR |= 0X08
			#define UART_SMODMX_SET SMODMX&=(~0X0c)
	#endif
	#if UART_S1REL_125000==0
			#define UART_REL_125000		UART_BR_8M
	#else
			#define UART_REL_125000		UART_BR_4M
	#endif
	
	#define UART_CON			S1CON
	#define UART_BUF			S1BUF
	#define UART_REL			S1REL
	#define UART_SMODCAL	(0x01U<<6)
	#define UART_BDEN			(0x01U<<6)
	#define UART_TEN			(0x01U<<1)
	#define IEN_URX				(0x01U<<5)
	#define IEN_UTX				(0x01U<<4)
	
	#define ISRDebugUtx 	ISRUart1tx
	#define ISRDebugUrx 	ISRUart1rx
#endif
//-----------------------------------------------------------------------------
// Register mask
//-----------------------------------------------------------------------------
#define mskUART_REN  	(0x01U<<4)	
#define mskUART_TI  	(0x01U<<1)	
#define mskUART_RI  	(0x01U<<0)	
//-----------------------------------------------------//
#define MAX_RXDATA_LEN  10		//data buf lenth
#define MAX_TXDATA_LEN  10		//data buf lenth
#define UART_LOAD_DATA	0x5a
#define UART_URX_SYNC		10
#define UART_UTX_TIME		10000
#define UART_URX_TIME		10000
//-----------------------------------------------------------------------------
// Global Variables 
//-----------------------------------------------------------------------------
#if	DEBUG_MODE_UART0||DEBUG_MODE_UART1
extern xdata uint8_t g_cUartTxData[MAX_TXDATA_LEN];	//uart TX DATA BUF
extern xdata uint8_t g_cUartRxData[MAX_RXDATA_LEN];	//uart TX DATA BUF
extern xdata uint8_t g_cUartTxCnt;
extern xdata uint8_t g_cUartRxCnt;
extern bit f_bUartTxEnding;
extern bit f_bUartRxEnding;
extern xdata uint8_t g_cUartRxSync;
#endif
//-----------------------------------------------------------------------------
// FUNTION
//-----------------------------------------------------------------------------
#if	DEBUG_MODE_UART0||DEBUG_MODE_UART1
void init_uart(void);
void write_uart_buf(uchar cUartBuf);
void enable_debug_uart(void);
void disable_debug_uart(void);
#endif
//----------------------------------------------------------------
#endif	//#ifndef		_CAPTOUCH_UART_H_