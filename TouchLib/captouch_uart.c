//--------------------------------------------------------------------------
//Filename		: captouch_uart.c
//Function		: 
//--------------------------------------------------------------------------
#include "captouch_uart.h"
#include "captouch_init.h"

#if DEBUG_MODE_UART0||DEBUG_MODE_UART1
xdata uchar g_cUartTxData[MAX_TXDATA_LEN];	//uart TX DATA BUF
xdata uchar g_cUartRxData[MAX_RXDATA_LEN];	//uart TX DATA BUF
xdata uchar g_cUartTxCnt;
xdata uchar g_cUartRxCnt;
bit f_bUartTxEnding = 1;
bit f_bUartRxEnding;
xdata uchar g_cUartRxSync = UART_URX_SYNC;
xdata uchar g_cUartRxBuf[MAX_RXDATA_LEN];
#endif

//-----------------------------------------------------------------------------
//Function		: void init_uart(void)
//Description	: init UART
//-----------------------------------------------------------------------------
#if DEBUG_MODE_UART0||DEBUG_MODE_UART1
void init_uart(void)
{
	P_UTX_HIGH;                		// UTX pin set high
	PM_UTX_OUT;            				// UTX is output, URX is input
	P_URX_HIGH;
	PM_URX_IN;										//URX初始化输入模式
	PUR_URX_ON;
	UART_SMODMX_SET;
	
	UART_CON = 0x50;									//使能接收功能,模式1
	S0CON2 |= ( UART_BDEN | UART_TEN );
	UART_REL = UART_REL_125000;		//波特率设置
	SMODCAL |= UART_SMODCAL;

	IEN1 |= (IEN_URX|IEN_UTX);	//使能UART中断
}
#endif
//--------------------------------------------------------------------------
//subroutine	: isr_uart0tx
//Function		: UART0 TX interrupt service routine
//--------------------------------------------------------------------------
#if DEBUG_MODE_UART0||DEBUG_MODE_UART1
void isr_debug_utx(void) interrupt ISRDebugUtx
{
	if(g_cUartTxCnt<MAX_TXDATA_LEN)
	{
		UART_BUF = g_cUartTxData[g_cUartTxCnt++];
		f_bUartTxEnding = 0;
	}
	else
	{
		f_bUartTxEnding = 1;
	}
	UART_CON &= ~mskUART_TI; //clear TI
}
//--------------------------------------------------------------------------
//subroutine	: isr_uart0rx
//Function		: UART0 RX interrupt service routine
//--------------------------------------------------------------------------
void isr_debug_urx(void) interrupt ISRDebugUrx
{
	g_cUartRxBuf[g_cUartRxCnt] = UART_BUF;
	g_cUartRxSync = UART_URX_SYNC;
	if(g_cUartRxCnt<MAX_RXDATA_LEN)
	{
		if(g_cUartRxCnt==0)
		{
			if(g_cUartRxBuf[0]==UART_LOAD_DATA)
			{
				g_cUartRxCnt++;
			}
		}
		else
		{
			g_cUartRxCnt++;
		}
	}
	if(g_cUartRxCnt==MAX_RXDATA_LEN)
	{
		f_bUartRxEnding = 1;
		for(g_cUartRxCnt=0;g_cUartRxCnt<MAX_RXDATA_LEN;g_cUartRxCnt++)
		{
			g_cUartRxData[g_cUartRxCnt] = g_cUartRxBuf[g_cUartRxCnt];
		}
		g_cUartRxCnt = 0;
	}
	else
	{
		f_bUartRxEnding = 0;
	}
	UART_CON &= ~mskUART_RI; //clear RI
}
#endif
//--------------------------------------------------------------------------
//subroutine	: 
//Function		: 
//--------------------------------------------------------------------------
#if DEBUG_MODE_UART0||DEBUG_MODE_UART1
void write_uart_buf(uchar cUartBuf)
{
	UART_BUF = cUartBuf;
}
#endif
//--------------------------------------------------------------------------
//subroutine	: 
//Function		: 
//--------------------------------------------------------------------------
#if DEBUG_MODE_UART0||DEBUG_MODE_UART1
void enable_debug_uart(void)
{
	UART_CON |= mskUART_REN;
}
#endif
#if DEBUG_MODE_UART0||DEBUG_MODE_UART1
void disable_debug_uart(void)
{
	UART_CON &= ~mskUART_REN;
}
#endif