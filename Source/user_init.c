//--------------------------------------------------------------------------
//Filename		: user_init.c
//Function		: 
//--------------------------------------------------------------------------
#include "captouch_main.h"
#include "sn8f5754.h"
//--------------------------------------------------------------------------
//subroutine	: 
//Function		: 
//--------------------------------------------------------------------------
void init_sys(void)
{
	P0UR = 0X00;
	P0 = 0X00;
	P0M = 0XFF;
	
	P1UR = 0X67;
	P1 = 0X00;
	P1M = 0X08;
	
	P2UR = 0XE0;
	P2 = 0X00;
	P2M = 0X00;
	
	P3UR = 0XF0;
	P3 = 0X00;
	P3M = 0X0F;
	
	
//	P0UR = 0X00;
//	P0 = 0X00;
//	P0M = 0XFF;
//		
//	P1UR = 0X00;
//	P1 = 0X00;
//	P1M = 0XFF;
//	
//	P2UR = 0X00;
//	P2 = 0X00;
//	P2M = 0XFF;
//	
//	P3UR = 0X00;
//	P3 = 0X00;
//	P3M = 0XFF;
//----------------------------------//init_timer1
	TMOD |= 0x60;     // Mode 2 of Timer 1 as a 8-bit auto-reload Timer 
  TH1 = (256-125);		//500uS;
  TL1 = (256-125);		//500uS;

  TCON0 &= 0xf0;    // T1RATE is Fosc/128
  ET1 = 1;          // Timer 1 isr enable
  TR1 = 1;          // enable Timer 1 Run control
//----------------------------------//
	IP0 = 0x1D;					//if the I2C/UART bus fails to communicate properly, 
	IP1 = 0x17;					//the user can try to set its interrupt priority to the highest level.

//// PWM1_Initial
//  PW1YH = 0x7d;
//  PW1YL = 0x7d;
//  PW10DH = 0x3f;
//  PW10DL = 0x3f;
//// PWM1 enable, clock = Fosc/128, 
//  PW1M = 0x00;
//// PWM10 channel enable
//  PW1CH |= 0x08; 


	
}










