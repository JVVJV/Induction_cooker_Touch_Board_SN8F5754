//--------------------------------------------------------------------------
//Filename		: main.c
//Function		: SONiX Touch key Library for Button key
//Description	: 
//Author			: SONIX-SA1
//Version			: SN8F5754 Touch Key lib V1.21
//Date				: 
//Version Record: single key
//------------------------------------------------------------------

//2024/09/20 V1.21
//Program Size: data=36.0 xdata=760 code=5669
//INI_Ver = V43
//EXE_Ver = V27
//CheckSum = 0x0FE4
//--------------------------------------------------------------------------
#define __XRAM_SFR_H__
#include "captouch_main.h"
#include "captouch_init.c"	//warning: user cann't modify this file!
#include "sysmode.h"
#include "app.h"
#include "disp.h"
#include "iic.h"
#include "user_isr.h"

/*
 * Version History
 * V1.0    2025/01/14  Initial version; IIC not integrated and buzzer unstable.
 * V2.1    2025/01/17  Added IIC protocol support; system boots successfully.
 * V2.2    2025/01/20  Power-on test completed; supports three power levels.
 * V2.3    2025/02/21  Added pot detection and child lock functions.
 * V2.4    2025/02/26  Added child lock and knob control; planning layered app design.
 * V2.5    2025/03/04  Fixed issues from version 2.4.
 * V2.6    2025/03/11  Added knob power control and 60-minute timer.
 * V2.7    2025/03/12  Improved timer display during adjustments.
 * V2.8    2025/03/13  Auto-scroll timer display after 4 seconds of idle.
 * V2.8.1  2025/03/13  Continues heating when pot is returned during alarm.
 * V2.8.2  2025/03/14  Added buzzer feedback on key press.
 * V3.0    2025/03/21  Code cleanup and feature restoration.
 */



void main(void)
{
	config_SWAT(SWAT_CMD);
	init_sys();				//user's initial code
//----------------------------------//	
	init_touch();			//user need to initial system before call init_touch()
//----------------------------------//	
	IIC_Init();       //iic initial
//----------------------------------//
	EAL = 1;
//----------------------------------//
	while(1)
	{
		WDTR = 0X5A;					//clear watch dog timer
    
    if(IntGnd.fTime1ms)
    {
      IntGnd.fTime1ms = 0;
      I2C_TimeoutTick();
    }
    
		scan_touch_key();			//touch key scan routine
		touch_key_cvt();


		I2C_DataCom();
	
/***************************************************************/
//	User Code Define Area
		#if POWER_SAVE
		init_sysmode();
		#endif
/***************************************************************/
		app();		
		lcd_bit();	
	
	
	}
}
