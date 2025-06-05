//--------------------------------------------------------------------------
//Filename		: init.c
//Function		: 
//--------------------------------------------------------------------------
#include "captouch_main.h"
#include "captouch_init.h"
#include "captouch_equ.h"
#include "captouch_equ1.h"
#include "sysmode.h"
//-------------------------------------------------------
#if	DEBUG_MODE_I2C
	#include "captouch_i2c.c"
#endif
#if	DEBUG_MODE_UART0||DEBUG_MODE_UART1
	#include "captouch_uart.c"
#endif
//-------------------------------------------------------
//
//-------------------------------------------------------
#if DEBUG_MODE_UART0||DEBUG_MODE_UART1||DEBUG_MODE_I2C
xdata uint8_t g_cDebugData[2];
xdata uint8_t g_cDebugFreq = DEBUG_FREQ;
#endif
idata uint16_t g_iPressTime;			//press time cnt
code uint8_t g_cMaxPressCnt = MAX_PRESS_KEY_CNT;

code uint8_t g_cMeasNumCnt = TK_EN_NUM;
//-------------------------------------------------------
#if (BASE_CNT_MINUS + BASE_CNT_PLUS)>BASE_CNT_MAX
code uint8_t g_cBaseCntPlus = BASE_CNT_MAX;		//plus base update cnt
#else
code uint8_t g_cBaseCntPlus = BASE_CNT_MINUS + BASE_CNT_PLUS;		//plus base update cnt
#endif
#if (BASE_CNT_MINUS)>(BASE_CNT_MAX/2)
code uint8_t g_cBaseCntMinus = (BASE_CNT_MAX/2);		//plus base update cnt
#else
code uint8_t g_cBaseCntMinus = BASE_CNT_MINUS;
#endif
#if (BASE_CNT_AVER)>BASE_CNT_MAX
code uint8_t g_cBaseCntAver = BASE_CNT_MAX;		//plus base update cnt
#else
code uint8_t g_cBaseCntAver = BASE_CNT_AVER;
#endif
//-------------------------------------------------------
code uint8_t g_cMaxDeltaSet = MAX_DELAT_SET;
code uint8_t g_cMinusDeltaSet = MINUS_DELAT_SET;
//------------------------------------------------------
code uint8_t g_cMeasTimeSet = MEAS_TIME_SET;		//save MEAS_TIME_SET
xdata uint8_t g_cMeasTimeLimit = MEAS_TIME_SET;	//single channel meastime limit
//-------------------------------------------------------
//	registers for CM
//-------------------------------------------------------
code uint8_t g_cFrqNumCnt = FRQ_NUM;
code uint8_t g_cFrqTswSet[FRQ_NUM_MAX]={FRQ_TSWY0,FRQ_TSWY1};
xdata union DataFormat g_cCmMeasData[FRQ_NUM_MAX][TK_EN_MAX];	//TK_EN_MAX
xdata union KeyFormat g_cCmKeyData[TK_EN_NUM];
xdata union DumFormat g_cDumData[FRQ_NUM];
xdata union FourByte g_lKeyStatusBuf[FRQ_NUM];
//-------------------------------------------------------
//
//-------------------------------------------------------
#if KB_MAKE_DEBOUNCE_COUNT>DEBOUNCE_COUNT_STATE
code uint8_t g_cKeyMakeDebounceCnt =	DEBOUNCE_COUNT_STATE;
#else
code uint8_t g_cKeyMakeDebounceCnt =	KB_MAKE_DEBOUNCE_COUNT;			//** Key make time n * 20ms
#endif
#if KB_BREAK_DEBOUNCE_COUNT>DEBOUNCE_COUNT_STATE
code uint8_t g_cKeyBreakDebounceCnt =	DEBOUNCE_COUNT_STATE;
#else
code uint8_t g_cKeyBreakDebounceCnt =	KB_BREAK_DEBOUNCE_COUNT;		//** Key break time n * 20ms
#endif

code uint16_t g_iDefaultDummyCount = DEFAULT_DUMMY_COUNT;
//------------------------------------------------//	
idata uint8_t g_cTouchIntgnd2ms = TOUCH_INTGND_2MS;
bit f_bTouchIntgnd2ms;
//--------------------------------------------------------------------------
//subroutine	: touch_isr_timer
//Function		: Timer interrupt service routine for touch
//--------------------------------------------------------------------------
void touch_isr_timer(void)
{
	if(g_cMeasTimeLimit>0)	//for touch library
	{
		g_cMeasTimeLimit--;
	}
//------------------------------------//
	if((--g_cTouchIntgnd2ms)==0)
	{
		g_cTouchIntgnd2ms = TOUCH_INTGND_2MS;
		f_bTouchIntgnd2ms = 1;
	}
//------------------------------------//
	#if DEBUG_MODE_UART0||DEBUG_MODE_UART1
	if((--g_cUartRxSync)==0)
	{
		g_cUartRxCnt = 0;
		g_cUartRxSync = UART_URX_SYNC;
	}
	#endif
}
//-------------------------------------------------------------------------------------
//Subroutine	: captouch_intgnd
//Function		: touch 2ms intgnd
//Input			: 
//Output		: 
//Stack Layer	: 
//-------------------------------------------------------------------------------------
void captouch_intgnd(void)
{
	#if TIME_LIMIT
		if(g_lKeyStatus.uniDWord>0)
		{
			if(f_bMultiKey)
			{
				if(g_iPressTime<(PRESS_TIME_CNT-PRESS_MULTI_CNT))
				{
					g_iPressTime = PRESS_TIME_CNT-PRESS_MULTI_CNT;
				}
			}
			g_iPressTime++;
			if(g_iPressTime==PRESS_TIME_CNT) //** over 5s reset Base
			{
				touch_meas_reset(TK_BASE_INIT);
			}
		}
		else
		{
			g_iPressTime = 0;	//reset press time cnt
		}
	#endif
//----------------------------------------------//
	#if POWER_SAVE
  if((--g_iPSDelayCnt)==0)
  {
    init_delay_sleep();
    f_bPowerSaving = 1;      
  }
	#endif
}
//--------------------------------------------------------------------------
//subroutine	: 
//Function		: 
//--------------------------------------------------------------------------
void init_delay_sleep(void)
{
	#if POWER_SAVE
	f_bPowerSaving = 0;
	g_iPSDelayCnt = PSDELAY_INTGND_2MS;
	#endif
}
//**************************************************************************************
//Subroutine	: 
//Function		: //switch Touch key channel to output low
//Input			: 
//Output		: 
//Stack Layer	: 
//**************************************************************************************
void	init_touch_port(void)
{
	#if	TK_P0_SET>0
	P0UR &= (TK_P0_SET^0XFF);	//make sure disable the pull-up register when enable the touch key function
	P0M |= TK_P0_SET;
//	P0 &= (TK_P0_SET^0XFF);		//output low
	P0 |= TK_P0_SET;		//output high
	P0CON |= TK_P0_SET;
	#endif
	
	#if	TK_P1_SET>0
	P1UR &= (TK_P1_SET^0XFF);	//make sure disable the pull-up register when enable the touch key function
	P1M |= TK_P1_SET;
//	P1 &= (TK_P1_SET^0XFF);		//output low
	P1 |= TK_P1_SET;		//output high
	P1CON |= TK_P1_SET;
	#endif

	#if	TK_P2_SET>0
	P2UR &= (TK_P2_SET^0XFF);	//make sure disable the pull-up register when enable the touch key function
	P2M |= TK_P2_SET;
//	P2 &= (TK_P2_SET^0XFF);		//output low
	P2 |= TK_P2_SET;		//output high
	P2CON |= TK_P2_SET;
	#endif

	#if	TK_P3_SET>0
	P3UR &= (TK_P3_SET^0XFF);	//make sure disable the pull-up register when enable the touch key function
	P3M |= TK_P3_SET;
//	P3 &= (TK_P3_SET^0XFF);		//output low
	P3 |= TK_P3_SET;		//output high
	P3CON |= TK_P3_SET;
	#endif
}
//--------------------------------------------------------------------------
//subroutine	: 
//Function		: 
//--------------------------------------------------------------------------
void init_touch(void)
{
	init_touch_port();				//set Touch key channel to output high
	#if DEBUG_MODE_I2C
	i2c_master_init();
	#endif
	#if DEBUG_MODE_UART0||DEBUG_MODE_UART1
	init_uart();
	#endif
//-------------------------------------------------//
	pre_touch();
	touch_meas_reset(TK_BASE_RESET);	//reset measment system
 //-------------------------------------------------// 
	#if POWER_SAVE
	init_LPSM();
	#endif  
}
//--------------------------------------------------------------------------
//subroutine	: 
//Function		: 
//--------------------------------------------------------------------------
void init_debug_data(void)
{
	#if DEBUG_MODE_UART0||DEBUG_MODE_UART1||DEBUG_MODE_I2C
	if(g_cDebugFreq==g_cCKfreqSelectPre)
	{
		g_cDebugData[0] = g_iLibVersion[0]/0X100;	//for test
		g_cDebugData[1] = g_iLibVersion[0]%0X100; //for test
		#if DEBUG_MODE_I2C
			debug_i2c_comm();
		#endif
		#if DEBUG_MODE_UART0||DEBUG_MODE_UART1
			debug_uart_comm();
		#endif
	}
	#endif
}
//------------------------------------------------------ 
code uint8_t g_cTabCTnBuf[] = {
#if TK_P14_EN
SCAN_P14,
#endif
#if TK_P15_EN
SCAN_P15,
#endif
#if TK_P16_EN
SCAN_P16,
#endif
#if TK_P17_EN
SCAN_P17,
#endif
#if TK_P20_EN
SCAN_P20,
#endif
#if TK_P21_EN
SCAN_P21,
#endif
#if TK_P22_EN
SCAN_P22,
#endif
#if TK_P23_EN
SCAN_P23,
#endif
#if TK_P24_EN
SCAN_P24,
#endif
#if TK_P07_EN
SCAN_P07,
#endif
#if TK_P06_EN
SCAN_P06,
#endif
#if TK_P33_EN
SCAN_P33,
#endif
#if TK_P32_EN
SCAN_P32,
#endif
#if TK_P31_EN
SCAN_P31,
#endif
#if TK_P30_EN
SCAN_P30,
#endif
#if TK_P05_EN
SCAN_P05,
#endif
#if TK_P04_EN
SCAN_P04,
#endif
#if TK_P03_EN
SCAN_P03,
#endif
#if TK_P02_EN
SCAN_P02,
#endif
#if TK_P10_EN
SCAN_P10,
#endif
#if TK_P13_EN
SCAN_P13,
#endif
#if TK_P12_EN
SCAN_P12,
#endif
#if TK_P11_EN
SCAN_P11,
#endif
};
//------------------------------------------------------
code uint8_t g_cCmTcntPara[] = 
{
#if TK_P14_EN
P14_TCNT,
#endif
#if TK_P15_EN
P15_TCNT,
#endif
#if TK_P16_EN
P16_TCNT,
#endif
#if TK_P17_EN
P17_TCNT,
#endif
#if TK_P20_EN
P20_TCNT,
#endif
#if TK_P21_EN
P21_TCNT,
#endif
#if TK_P22_EN
P22_TCNT,
#endif
#if TK_P23_EN
P23_TCNT,
#endif
#if TK_P24_EN
P24_TCNT,
#endif
#if TK_P07_EN
P07_TCNT,
#endif
#if TK_P06_EN
P06_TCNT,
#endif
#if TK_P33_EN
P33_TCNT,
#endif
#if TK_P32_EN
P32_TCNT,
#endif
#if TK_P31_EN
P31_TCNT,
#endif
#if TK_P30_EN
P30_TCNT,
#endif
#if TK_P05_EN
P05_TCNT,
#endif
#if TK_P04_EN
P04_TCNT,
#endif
#if TK_P03_EN
P03_TCNT,
#endif
#if TK_P02_EN
P02_TCNT,
#endif
#if TK_P10_EN
P10_TCNT,
#endif
#if TK_P13_EN
P13_TCNT,
#endif
#if TK_P12_EN
P12_TCNT,
#endif
#if TK_P11_EN
P11_TCNT,
#endif
};
//------------------------------------------------------
code uint16_t g_iCmFtPara[FRQ_NUM_MAX][TK_EN_MAX] = 
{
P14_FT,
P15_FT,
P16_FT,
P17_FT,
P20_FT,
P21_FT,
P22_FT,
P23_FT,
P24_FT,
P07_FT,
P06_FT,
P33_FT,
P32_FT,
P31_FT,
P30_FT,
P05_FT,
P04_FT,
P03_FT,
P02_FT,
P10_FT,
P13_FT,
P12_FT,
P11_FT,

P14_FT1,
P15_FT1,
P16_FT1,
P17_FT1,
P20_FT1,
P21_FT1,
P22_FT1,
P23_FT1,
P24_FT1,
P07_FT1,
P06_FT1,
P33_FT1,
P32_FT1,
P31_FT1,
P30_FT1,
P05_FT1,
P04_FT1,
P03_FT1,
P02_FT1,
P10_FT1,
P13_FT1,
P12_FT1,
P11_FT1,
};
//------------------------------------------------------
code uint16_t g_iCmNtPara[FRQ_NUM_MAX][TK_EN_MAX] = 
{
P14_NT,
P15_NT,
P16_NT,
P17_NT,
P20_NT,
P21_NT,
P22_NT,
P23_NT,
P24_NT,
P07_NT,
P06_NT,
P33_NT,
P32_NT,
P31_NT,
P30_NT,
P05_NT,
P04_NT,
P03_NT,
P02_NT,
P10_NT,
P13_NT,
P12_NT,
P11_NT,

P14_NT1,
P15_NT1,
P16_NT1,
P17_NT1,
P20_NT1,
P21_NT1,
P22_NT1,
P23_NT1,
P24_NT1,
P07_NT1,
P06_NT1,
P33_NT1,
P32_NT1,
P31_NT1,
P30_NT1,
P05_NT1,
P04_NT1,
P03_NT1,
P02_NT1,
P10_NT1,
P13_NT1,
P12_NT1,
P11_NT1,
};
//-------------------------------------------------------
//
//-------------------------------------------------------
