$NOMOD51
;------------------------------------------------------------------------------
;
;  Copyright (c) 2021 SONiX Technology Co., Ltd.
;  Version 1.0 - SN8F5754, SN8F5753, SN8F5752. Add code option address for MP5
;  *** <<< Use Configuration Wizard in Context Menu >>> ***
;------------------------------------------------------------------------------
;
;  This preference, such as watchdog, external reset pin, and clock source, is preloaded 
;  during the microcontroller's power-on. It is strongly recommanded to use configuration 
;  wizard to set these parameters up appropriately.
;
;------------------------------------------------------------------------------
ROM_SIZE		EQU		0x4000
;
;	<o.0..1> Program Memory Security <0x03=> Security Disable <0x02=> Security Enable <0x00=> Security Configuration
		SECURITY_SET    EQU     0x02		;	{0x3FFF}
;   <i> Security Disable: all address ROM data can be accessed.	
;   <i> Security Enable: all address ROM data are protected.
;   <i> Security Configuration: all address ROM data are protected expect address 0x3F00 ~ 0x3FDF ROM data can be accessed.
;
;   <o.2> ISP Program Area  <0x01=> All Page <0x00=> Page 504~ Page 510
    ISP_EN_SET    EQU     0x04		;	{0x3FFF}
;   <i> All Page: all address can perform ISP function.
;   <i> Page 504 ~ Page 510: only address 0x3F00 ~ 0x3FDF can perform ISP function.

;   <h> CPU Clock
;   <o.2..4> CPU Clock Source <0x07=> IHRC 32 MHz <0x03=> IHRC 32 MHz with RTC  <0x02=> External Clock <0x01=> X'tal 12 MHz <0x00=> X'tal 4 MHz
    CLOCKSRC_SET    EQU     0x1C		;	{0x3FFB}
;   <i> IHRC 32 MHz: on-chip internal clock with or without Timer 0 real time clock.
;   <i> X'tal 12 MHz: off-chip crystal between 4 MHz and 16 MHz.
;   <i> X'tal 4 MHz: off-chip crystal between 1 MHz and 4 MHz.
;   <i> External Clock: external clock input from XIN pin.

;   <o.5..7> CPU Clock Rate for IHRC 32MHz  <0x00=> Fhosc/128 <0x01=> Fhosc/64 <0x02=> Fhosc/32 <0x03=> Fhosc/16 <0x04=> Fhosc/8 <0x05=> Fhosc/4
    IHRC32M_CLOCKRATE_SET    EQU     0xA0		;	{0x3FFB}
;   <i> FCPU for IHRC 32MHz is Fhosc/4~Fhosc/128.

;   <o.5..7> CPU Clock Rate for X'tal 12 MHz  <0x00=> Fhosc/128 <0x01=> Fhosc/64 <0x02=> Fhosc/32 <0x03=> Fhosc/16 <0x04=> Fhosc/8 <0x05=> Fhosc/4  <0x06=> Fhosc/2
    XTAL12M_CLOCKRATE_SET    EQU     0xC0		;	{0x3FFB}
;   <i> FCPU for X'tal 12 MHz is Fhosc/2~Fhosc/128.

;   <o.5..7> CPU Clock Rate for X'tal 4 MHz  <0x00=> Fhosc/128 <0x01=> Fhosc/64 <0x02=> Fhosc/32 <0x03=> Fhosc/16 <0x04=> Fhosc/8 <0x05=> Fhosc/4  <0x06=> Fhosc/2 <0x07=> Fhosc/1 
    XTAL4M_CLOCKRATE_SET    EQU     0xE0		;	{0x3FFB}
;   <i> FCPU for X'tal 4 MHz is Fhosc/1~Fhosc/128.

;   <o.5..7> CPU Clock Rate for External Clock  <0x00=> Fhosc/128 <0x01=> Fhosc/64 <0x02=> Fhosc/32 <0x03=> Fhosc/16 <0x04=> Fhosc/8 <0x05=> Fhosc/4  <0x06=> Fhosc/2 <0x07=> Fhosc/1 
    EXTERNAL_CLOCKRATE_SET    EQU     0xE0		;	{0x3FFB}
;   <i> FCPU for External Clock is Fhosc/1~Fhosc/128.
;   </h>

;   <o.0> Noise Filter <0x01=> Disable <0x00=> Enable
    NOISEFILT_EN_SET   EQU     0x00		;	{0x3FFC}	

;	<o.3> CK_Fine_Tuning <0x01=> Disable <0x00=> Enable
    CK_FINETUNING_EN   EQU     0x08		;	{0x3FFF}
;   <i> IHRC frequency fine tuning function.

;   <h> Reset Sources
;       <o.4..5> External Reset / GPIO Shared Pin <0x00=> Reset with De-bounce <0x02=> Reset without De-bounce <0x03=> GPIO
        RESETPIN_SET    EQU     0x30	;	{0x3FFC}
;       <i> Reset with De-bounce: Triggers reset if this pin is pulled low over 8 ms.
;       <i> Reset without De-bounce: Triggers reset immediately if this pin is pulled low.
;       <i> GPIO: The shared pin is reserved for general purpose input/output.
;       <i> The de-bounce period is based on Internal Low R-C Clock which has a gentle inaccuracy.
;
;       <o.4..7> Watchdog Reset <0x00=> Always <0x05=> Enable <0x0A=> Disable 
        WATCHDOG_SET    EQU     0x50	;	{0x3FFF}
;       <i> Always: Trun on watchdog function including Normal, IDLE, and STOP mode.
;       <i> Enable: Turn on watchdog function only in Normal mode.
;       <i> Disable: Turn off watchdog function.
;
;       <o.6..7> Watchdog Overflow Period <0x00=> 64 ms <0x01=> 128 ms <0x02=> 256 ms <0x03=> 512 ms
        WATCHCLK_SET    EQU     0xC0	;	{0x3FFC}
;       <i> The watchdog overflow period is based on Internal Low R-C Clock which has a gentle inaccuracy.


    CSEG    AT      0x3FF6
    DB      0xFF
    DB      0xFF
    DB      0xFF
    DB      0xFF
    DB      0xFE
	IF		(CLOCKSRC_SET==0x1C) || (CLOCKSRC_SET==0x0C)
    DB      IHRC32M_CLOCKRATE_SET + CLOCKSRC_SET + 0x03
	ENDIF
	IF		CLOCKSRC_SET==0x04
    DB      XTAL12M_CLOCKRATE_SET + CLOCKSRC_SET + 0x03
	ENDIF
	IF		CLOCKSRC_SET==0x00
    DB      XTAL4M_CLOCKRATE_SET + CLOCKSRC_SET + 0x03
	ENDIF
	IF		CLOCKSRC_SET==0x08
    DB      EXTERNAL_CLOCKRATE_SET + CLOCKSRC_SET + 0x03
	ENDIF
    DB      WATCHCLK_SET + RESETPIN_SET + 0x0E + NOISEFILT_EN_SET
    DB		0x5A
    DB		0xA5
    DB      WATCHDOG_SET + CK_FINETUNING_EN + ISP_EN_SET + SECURITY_SET

    END

