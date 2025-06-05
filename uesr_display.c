#include "disp.h"
#include "sn8f5754.h"
#include "captouch_main.h"
#include "app.h"

#define	LCD_SEG_NUM		5
uint8_t LCDB[LCD_SEG_NUM];

code uint8_t LCD_TabNum[] = {LED_0,LED_1,LED_2,LED_3,LED_4,LED_5,LED_6,LED_7,LED_8,LED_9,LED_E,LED_R,LED_O,LED_N};

volatile unsigned char scan_num=0;
unsigned char bit_number=close_n;
unsigned char LED_B=0;

void lcd_bit()
{
	switch(bit_number)
	{		
		case close_n:
			LCDB[0] = 0;
		  LCDB[1] = 0;
		  LCDB[2] = 0;
		  LCDB[3] = 0;		
		  LCDB[4] = 0x01;	
		break;		
		
		case standby_n:
			LCDB[0] = 0;
		  LCDB[1] = LCD_TabNum[12];
		  LCDB[2] = LCD_TabNum[13];
		  LCDB[3] = 0;		
		  LCDB[4] = 0x01;	
		break;
		
		case watt_n:
			LCDB[0] = LCD_TabNum[wat_tab[wat_level]/1000];
		  LCDB[1] = LCD_TabNum[wat_tab[wat_level]/100%10];
		  LCDB[2] = LCD_TabNum[0];
		  LCDB[3] = LCD_TabNum[0];		
		  LCDB[4] = LED_B;	
		break;	
		
		case lock_n:	
		  LCDB[4] = 0x03;	
		break;				
		
		case Ero_n:
			LCDB[0] = LCD_TabNum[10];               // Display 'E'
      // Display '1'~'8' for E1~E8, or '0' for E0
      LCDB[1] = LCD_TabNum[err_num];
      LCDB[2] = 0;
		  LCDB[3] = 0;	
		  LCDB[4] = 0x01;	
		break;	
		
		case time_n:
			LCDB[0] = LCD_TabNum[0];		              // 千位数
	   	LCDB[1] = 0x80;		                        //  ：
		  LCDB[1] |= LCD_TabNum[0];   	            // 百位数
		  LCDB[2] = LCD_TabNum[time_level/10];		  // 十位数
		  LCDB[3] = LCD_TabNum[time_level%10];	    // 个位数
      LCDB[4] = 0x01;
    break;
		
		case sw_n:
			if(disp_chan_tm1 == 0)
			{
				disp_chan_tm2 = 2;
				disp_chan_tm1 = 0xFF;
				
				LCDB[0] = LCD_TabNum[0];		              // 千位数
				LCDB[1] = 0x80;		                        //  ：
				LCDB[1] |= LCD_TabNum[0];   	            // 百位数
				LCDB[2] = LCD_TabNum[time_level/10];		  // 十位数
				LCDB[3] = LCD_TabNum[time_level%10];	    // 个位数				
			}
		
			if(disp_chan_tm2 == 0)
			{
				disp_chan_tm1 = 2;
				disp_chan_tm2 = 0xFF;
				
				LCDB[0] = LCD_TabNum[wat_tab[wat_level]/1000];
				LCDB[1] = LCD_TabNum[wat_tab[wat_level]/100%10];
				LCDB[2] = LCD_TabNum[0];
				LCDB[3] = LCD_TabNum[0];				
			}	
    break;
	}
	
}

void display()
{
	COM_ALL_INPUT();           //ALL INPUT
	if( ++scan_num >= 5 )      //4 bits
		scan_num = 0;	
	switch(scan_num)
	{	
		case 0:                    //bit 1
			  
				if(LCDB[0] & 0x01)	        {LED_SEGA_HIGH;}		// COM1
				if(LCDB[0] & 0x02)	        {LED_SEGB_HIGH;}						
				if(LCDB[0] & 0x04)	        {LED_SEGC_HIGH;}		
				if(LCDB[0] & 0x08)	        {LED_SEGD_HIGH;}		
				if(LCDB[0] & 0x10)	        {LED_SEGE_HIGH;}		
				if(LCDB[0] & 0x20)	        {LED_SEGF_HIGH;}		
				if(LCDB[0] & 0x40)	        {LED_SEGG_HIGH;}	
				if(LCDB[0] & 0x80)	        {LED_SEGDP_HIGH;}					
				COM1_OUT_LOW;
		break;
		
		case 1:                    //bit 2
			 
				if(LCDB[1] & 0x01)	        {LED_SEGA_HIGH;}		// COM2
				if(LCDB[1] & 0x02)	        {LED_SEGB_HIGH;}						
				if(LCDB[1] & 0x04)	        {LED_SEGC_HIGH;}		
				if(LCDB[1] & 0x08)	        {LED_SEGD_HIGH;}		
				if(LCDB[1] & 0x10)	        {LED_SEGE_HIGH;}		
				if(LCDB[1] & 0x20)	        {LED_SEGF_HIGH;}		
				if(LCDB[1] & 0x40)	        {LED_SEGG_HIGH;}	
				if(LCDB[1] & 0x80)	        {LED_SEGDP_HIGH;}						
			  COM2_OUT_LOW;
		break;

		case 2:                    //bit 3
			  
				if(LCDB[2] & 0x01)	        {LED_SEGA_HIGH;}		// COM3
				if(LCDB[2] & 0x02)	        {LED_SEGB_HIGH;}						
				if(LCDB[2] & 0x04)	        {LED_SEGC_HIGH;}		
				if(LCDB[2] & 0x08)	        {LED_SEGD_HIGH;}		
				if(LCDB[2] & 0x10)	        {LED_SEGE_HIGH;}		
				if(LCDB[2] & 0x20)	        {LED_SEGF_HIGH;}		
				if(LCDB[2] & 0x40)	        {LED_SEGG_HIGH;}	
				if(LCDB[2] & 0x80)	        {LED_SEGDP_HIGH;}						
				COM3_OUT_LOW;
		break;

		case 3:                    //bit 4
			  
				if(LCDB[3] & 0x01)	        {LED_SEGA_HIGH;}		// COM4
				if(LCDB[3] & 0x02)	        {LED_SEGB_HIGH;}						
				if(LCDB[3] & 0x04)	        {LED_SEGC_HIGH;}		
				if(LCDB[3] & 0x08)	        {LED_SEGD_HIGH;}		
				if(LCDB[3] & 0x10)	        {LED_SEGE_HIGH;}		
				if(LCDB[3] & 0x20)	        {LED_SEGF_HIGH;}		
				if(LCDB[3] & 0x40)	        {LED_SEGG_HIGH;}	
				if(LCDB[3] & 0x80)	        {LED_SEGDP_HIGH;}						
				COM4_OUT_LOW;
		break;	
		
		case 4:                    //模式标记

		    if(LCDB[4] & 0x01)	        {LED_SEGA_HIGH;}		// COM5			
				if(LCDB[4] & 0x02)	        {LED_SEGB_HIGH;}
				if(LCDB[4] & 0x04)	        {LED_SEGC_HIGH;}		
				if(LCDB[4] & 0x08)	        {LED_SEGD_HIGH;}		
				if(LCDB[4] & 0x10)	        {LED_SEGE_HIGH;}		
			  COM5_OUT_LOW;				
		break;			
  }
}

