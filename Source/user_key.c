//--------------------------------------------------------------------------
//Filename		: user_key.c
//Function		: 
//--------------------------------------------------------------------------
#include "captouch_main.h"
#include "app.h"
//------------------------------------------------//	
idata union FourByte g_lKeyOld;
#define g_cKeyOldL g_lKeyOld.uniByte[3]							//Low byte of KeyStatus after debounce
#define g_cKeyOldM g_lKeyOld.uniByte[2]							//Mid byte of KeyStatus after debounce
#define g_cKeyOldH g_lKeyOld.uniByte[1]							//High byte of KeyStatus after debounce
#define g_lKeyOldData g_lKeyOld.uniDWord

#define DEV_KEY_LONG		3000   //3s
#define DEV_KEY_CONTI   500

#define	TOUCH_KEY1	(g_cKeyCvtL & 0x01)		// P14
#define	TOUCH_KEY2	(g_cKeyCvtL & 0x08)		// P17
#define	TOUCH_KEY3	(g_cKeyCvtL & 0x10)		// P20
#define	TOUCH_KEY4	(g_cKeyCvtL & 0x20)		// P21
#define	TOUCH_KEY5	(g_cKeyCvtL & 0x40)		// P22
#define	TOUCH_KEY6	(g_cKeyCvtL & 0x80)		// P23

#define	I_KEY_L1					P10		//KEYA 
#define	I_KEY_L2					P11		//KEYB 

enum
{
	KEY_NUM1 = 1<<0,		
	KEY_NUM2 = 1<<1,					
	KEY_NUM3 = 1<<2,					
	KEY_NUM4 = 1<<3,			
	KEY_NUM5 = 1<<4,				
	KEY_NUM6 = 1<<5,			
	KEY_NUM7 = 1<<6,			
	KEY_NUM8 = 1<<7,		
};

uint8_t	key_inbuf;
uint8_t	key_chkbuf;
uint8_t	key_cvtbuf;
uint8_t	key_oldbuf;
uint8_t	key_debunc;
uint8_t	key_long_step;
uint16_t	Keylong;


uint8_t EncNow = 0;
uint8_t EncChk = 0;
uint8_t EncOld = 0;
bit	Enc1 = 0;

uint8_t tm_keychat = 0;             // debounce counter
uint16_t tm_keylong = 0;            // long press counter
volatile uint8_t tm_keydelay = 0;   // encoder delay counter

#define L_TM_KEYCHAT     100        // 100 * 1ms
#define L_TM_KEYLONG     2000       // x * 500us
#define L_TM_KEYDELAY    60         // 80 * 1ms

//--------------------------------------------------------------------------
//Subroutine: touch_key_cvt
//Function	: Sonix key de-bounce routine
//Input			: g_cKeyCvtL, g_cKeyCvtM, g_cKeyCvtH
//Output		: 
//							bit0 | bit1 | bit2 | bit3 | bit4 | bit5 | bit6 | bit7
//--------------------------------------------------------------------
//	g_cKeyCvtL	P1.4 | P1.5 | P1.6 | P1.7 | P2.0 | P2.1 | P2.2 | P2.3
//	g_cKeyCvtM	P2.4 | P0.7 | P0.6 | P3.3 | P3.2 | P3.1 | P3.0 | P0.5
//	g_cKeyCvtH	P0.4 | P0.3 | P0.2 | P1.0 | P1.3 | P1.2 | P1.1 |
//	=1, the key is on; =0, the key is off.
//--------------------------------------------------------------------------


void touch_key_cvt(void)
{
	if(key_debunc)
		key_debunc--;
	
//keyin--------------------------------
	key_inbuf = 0;

	if(TOUCH_KEY1)			key_inbuf |= KEY_NUM1;
	if(TOUCH_KEY2)			key_inbuf |= KEY_NUM2;
	if(TOUCH_KEY3)			key_inbuf |= KEY_NUM3;
	if(TOUCH_KEY4)			key_inbuf |= KEY_NUM4;	
	if(TOUCH_KEY5)			key_inbuf |= KEY_NUM5;
	if(TOUCH_KEY6)			key_inbuf |= KEY_NUM6;	
	

//keychk-------------------------------
	if(key_inbuf == key_chkbuf)
	{
		if(!key_debunc)
			key_cvtbuf = key_inbuf;
	}
	else
	{
		key_chkbuf = key_inbuf;
		key_debunc = 1;
	}	

//keycvt-------------------------------	
	if(key_cvtbuf != key_oldbuf)
	{
		key_inbuf = key_cvtbuf ^ key_oldbuf;
		
		if(key_inbuf & KEY_NUM1)				
		{
			if(key_cvtbuf & KEY_NUM1)			// button 1
			{			
			}
			else
			{
	      sw=~sw;          //power on	
				buzzerOn();	
			}
		}			
		
		if(key_inbuf & KEY_NUM2)				
		{
			if(key_cvtbuf & KEY_NUM2)			// button 2
			{
				if(sw==0xFF)
				{
					if(status!=erro)
						buzzerOn();
				}
        fifowrite(0x05);
			}
		}				

		if(key_inbuf & KEY_NUM3)				
		{
			if(key_cvtbuf & KEY_NUM3)			// button 3
			{
				if(sw==0xFF)
				{
					if(status!=erro)
						buzzerOn();
				}
        fifowrite(0x04);
			}
		}		

		if(key_inbuf & KEY_NUM4)				
		{
			if(key_cvtbuf & KEY_NUM4)			// button 4
			{
				if(sw==0xFF)
				{
					if(status!=erro)
						buzzerOn();
				}
        fifowrite(0x03);
			}
		}		

		if(key_inbuf & KEY_NUM5)				
		{
			if(key_cvtbuf & KEY_NUM5)			// button 5
			{		
				if(sw==0xFF)
				{
					if(status!=erro)
						buzzerOn();
				}
        fifowrite(0x02);
			}
		}		

		if(key_inbuf & KEY_NUM6)				
		{
			if(key_cvtbuf & KEY_NUM6)			// button 6
			{
				Keylong = DEV_KEY_LONG;
			}
			else
			{
				Keylong = 0;        
			}
		}		
		
		key_oldbuf = key_cvtbuf;			
	}
	
	
//keylong-------------------------------		
	
	if(keylong_1msF)
	{
		keylong_1msF=0;
		
		if(key_cvtbuf==KEY_NUM6)			
		{
			if(--Keylong == 0)
			{
				Keylong = DEV_KEY_CONTI; 	   //³¤°´°´¼ü6
				if(sw==0xFF)					
				  buzzerOn();
				childLockActive = !childLockActive;
				status=lock;			
			}
		}
	 }
	
	 
//----- encoder process --------------------------------------------------	
	
	EncNow = 0;			

	// Encoder state reference
  // A    B           A    B
  // 1    1           1    1
  // 1    0           0    1
  // 0    0           0    0
  // 0    1           1    0
  // 1    1           1    1
	
	if(!I_KEY_L2)		EncNow |= 0x01;
	if(!I_KEY_L1)		EncNow |= 0x02;
		
	if(EncNow == EncOld)
	{
		return;
	}	
	if(tm_keydelay != 0)			// delay in progress
	{
		return;
	}
	
	// 00 -> 01 or 11 -> 10 rotation check
	if(EncNow == 0x01 && EncOld == 0x00 || EncNow == 0x02 && EncOld == 0x03 )
	{
		EncChk = EncNow;
	}	
	// 00 -> 01 -> 11 or 11 -> 10 -> 00 clockwise confirmed
	if(EncNow == 0x03 && EncOld == 0x00 && EncChk == 0x01 || EncNow == 0x00 && EncOld == 0x03 && EncChk == 0x02 )
	{
		EncOld = EncNow;
		EncChk =0;

		if(Enc1 == 1)
		{
			Enc1 =0;
			tm_keydelay = L_TM_KEYDELAY; 		// start delay
//----------------------------
			
			if(status == open)
			{
       if(!knob_time)
			 {
				fifowrite(0x07);
				if(wat_level<8)
					wat_level++;  // increase power level
			 }					
			 if(knob_time)
			 {
				fifowrite(0x05);					 
				if(time_level<60)
					time_level++; // increase timer
			 }				
			}
//----------------------------
		}
		else
		{
			Enc1 = 1;
		}
	}
		
	// 00 -> 10 or 11 -> 01 rotation check
	if(EncNow == 0x02 && EncOld == 0x00 || EncNow == 0x01 && EncOld == 0x03 )
	{
		EncChk = EncNow;
	}
	// 00 -> 10 -> 11 or 11 -> 01 -> 00 counter-clockwise confirmed
	if(EncNow == 0x03 && EncOld == 0x00 && EncChk == 0x02 || EncNow == 0x00 && EncOld == 0x03 && EncChk == 0x01 )
	{
		EncOld = EncNow;
		EncChk =0;

		if(Enc1 == 1)
		{
			Enc1 =0;
			tm_keydelay = L_TM_KEYDELAY; 		// start delay
//----------------------------
			
			if(status == open)
			{	
       if(!knob_time)
			 {
				fifowrite(0x07);
				if(wat_level>=1)
					wat_level--;  // decrease power level
			 }					
			 if(knob_time)
			 {
				fifowrite(0x05);
				if(time_level>=1)
					time_level--; // decrease timer	
			 }
			}
//----------------------------
		}
		else
		{
			Enc1 = 1;
		}
		
	}			 
	 
	 
	 
}	
