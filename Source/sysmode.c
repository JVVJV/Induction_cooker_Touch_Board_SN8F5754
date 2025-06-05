//--------------------------------------------------------------------------
//Filename		: sysmode.c
//Function		: 
//--------------------------------------------------------------------------
#include "captouch_main.h"
#include "captouch_init.h"
#include "sysmode.h"

//------------------------------------------------//	
#if POWER_SAVE                            
bit f_bPowerSaving;
xdata uint16_t g_iPSDelayCnt;
xdata uint8_t g_cPSCTnMapBuf[PSTK_EN_NUM];
xdata uint16_t g_iPSDummyBase[FRQ_NUM];
xdata uint8_t g_cWakeUpMode;

bit f_bTR0Stack;	//ADM Stack
xdata uint8_t g_cADMStack;	//ADM Stack
#endif
//--------------------------------------------------------------------------
//subroutine	: 
//Function		: 
//--------------------------------------------------------------------------
#if POWER_SAVE
void init_sysmode(void)
{ 
	if(g_lKeyStatus.uniDWord==0)
	{
		if(f_bPowerSaving==1)
		{
			init_wakeup_source();		//init T0/ADC
			enter_LPSM();						//low power sysmode
			resume_wakeup_source();	//resume T0/ADC
		}
	}
	else
	{
		init_delay_sleep();
	}
}
#endif
//--------------------------------------------------------------------------
//subroutine	: 
//Function		: 
//--------------------------------------------------------------------------
#if POWER_SAVE
void record_wakeup_source(uint8_t cWakeMode)
{
	if((g_cWakeUpMode&WAKE_MODE) <= (cWakeMode&WAKE_MODE))
	{
		g_cWakeUpMode = cWakeMode;
	}
}
#endif
//--------------------------------------------------------------------------
//subroutine	: 
//Function		: 
//--------------------------------------------------------------------------
#if POWER_SAVE
void init_wakeup_source(void)
{
	#if (TIMER0_WAKEUP_MODE&WAKE_MODE)==DISABLE_WAKEUP
		f_bTR0Stack = TR0;
		TR0 = 0;
	#endif
	#if (ADC_WAKEUP_MODE&WAKE_MODE)==DISABLE_WAKEUP
		g_cADMStack = ADM;
		ADM = 0;
	#endif
}
#endif
//--------------------------------------------------------------------------
//subroutine	: 
//Function		: 
//--------------------------------------------------------------------------
#if POWER_SAVE
void resume_wakeup_source(void)
{
	#if (TIMER0_WAKEUP_MODE&WAKE_MODE)==DISABLE_WAKEUP
		TR0 = f_bTR0Stack;
	#endif
	#if (ADC_WAKEUP_MODE&WAKE_MODE)==DISABLE_WAKEUP
		ADM = g_cADMStack;
	#endif
}
#endif
//--------------------------------------------------------------------------
//subroutine	: 
//Function		: 
//--------------------------------------------------------------------------
#if POWER_SAVE
void check_wakeup_source(void)
{
	#if IO_WAKEUP_MODE
	if(g_cWakeUpMode==DISABLE_WAKEUP)		//check if IO wakeup
	{
		record_wakeup_source(IO_WAKEUP_MODE);
	}
	else if((g_cWakeUpMode&WAKE_MODE)==DISABLE_WAKEUP)
	{
		record_wakeup_source(LPSM_WAKE);
	}
	#else
	if((g_cWakeUpMode&WAKE_MODE)==DISABLE_WAKEUP)
	{
		record_wakeup_source(LPSM_WAKE);
	}
	#endif
}
#endif
//--------------------------------------------------------------------------
//subroutine	: 
//Function		: 
//--------------------------------------------------------------------------
#if POWER_SAVE
code uint8_t g_cPowerScanList[]=
{
	SCAN_DUMMY,
	SCAN_LIST00,
	SCAN_LIST01,
	SCAN_LIST02,  
	SCAN_LIST03,
	SCAN_LIST04,
	SCAN_LIST05,
	SCAN_LIST06,
	SCAN_LIST07,
	SCAN_LIST08,
	SCAN_LIST09,
	SCAN_LIST10,
	SCAN_LIST11,
	SCAN_LIST12,
	SCAN_LIST13,
	SCAN_LIST14,
	SCAN_LIST15,
	SCAN_LIST16,
	SCAN_LIST17,
	SCAN_LIST18,
	SCAN_LIST19,
	SCAN_LIST20,
	SCAN_LIST21,
	SCAN_LIST22,
};
#endif
//--------------------------------------------------------------------------
//subroutine	: isr_lpsm
//Function		: Touch low power sensing mode interrupt service routine
//--------------------------------------------------------------------------
#if POWER_SAVE
code uint8_t g_cPowerParam[]=
{
	LPSM_WAKEUP_MODE,
	PSTK_EN_NUM,
	PSTK_EN_FREQ,
	PSTK_EN_REMAINDER,
	TOUCH_TIMER_CLOCK_SET,
	POWERSAVE_SCAN_INTGND,
	BASE_CNT_SLEEP,
	BASE_CNT_WAKE,
	(MAX_WAKEUP_ONCE_TIME*2),
};
#endif
