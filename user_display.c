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
      LCDB[0] = LCD_TabNum[0];              // thousands digit
      LCDB[1] = 0x80;                       // hundreds digit with dot
      LCDB[1] |= LCD_TabNum[0];             // hundreds digit value
      LCDB[2] = LCD_TabNum[time_level/10];  // tens digit
      LCDB[3] = LCD_TabNum[time_level%10];  // ones digit
      LCDB[4] = 0x01;
    break;
		
		case sw_n:
			if(disp_chan_tm1 == 0)
			{
				disp_chan_tm2 = 2;
				disp_chan_tm1 = 0xFF;

        LCDB[0] = LCD_TabNum[0];                // thousands digit
        LCDB[1] = 0x80;                         // hundreds digit with dot
        LCDB[1] |= LCD_TabNum[0];               // hundreds digit value
        LCDB[2] = LCD_TabNum[time_level/10];    // tens digit
        LCDB[3] = LCD_TabNum[time_level%10];    // ones digit
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

typedef void (*ComOutFunc)(void);
static void com1_low(void){ COM1_OUT_LOW; }
static void com2_low(void){ COM2_OUT_LOW; }
static void com3_low(void){ COM3_OUT_LOW; }
static void com4_low(void){ COM4_OUT_LOW; }
static void com5_low(void){ COM5_OUT_LOW; }
static ComOutFunc com_funcs[LCD_SEG_NUM] = {com1_low, com2_low, com3_low, com4_low, com5_low};

static void set_segments(uint8_t seg)
{
    if(seg & 0x01) LED_SEGA_HIGH;
    if(seg & 0x02) LED_SEGB_HIGH;
    if(seg & 0x04) LED_SEGC_HIGH;
    if(seg & 0x08) LED_SEGD_HIGH;
    if(seg & 0x10) LED_SEGE_HIGH;
    if(seg & 0x20) LED_SEGF_HIGH;
    if(seg & 0x40) LED_SEGG_HIGH;
    if(seg & 0x80) LED_SEGDP_HIGH;
}

void display(void)
{
	COM_ALL_INPUT();                //ALL INPUT
	if( ++scan_num >= LCD_SEG_NUM ) //4 bits
		scan_num = 0;
  
	set_segments(LCDB[scan_num]);
  com_funcs[scan_num]();
}

