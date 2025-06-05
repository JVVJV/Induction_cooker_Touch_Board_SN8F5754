#ifndef  _DISP_H_
#define  _DISP_H_

#define COM_ALL_INPUT()   { P0M &= 0X00; P1M &= 0XF7;P3M &= 0XF0; }

#define COM3_OUT_LOW      { P0M |= 0X01; P00 = 0; }
#define COM2_OUT_LOW      { P0M |= 0X02; P01 = 0; }
#define COM1_OUT_LOW      { P0M |= 0X04; P02 = 0; }
#define COM4_OUT_LOW      { P0M |= 0X08; P03 = 0; }
#define COM5_OUT_LOW      { P1M |= 0X08; P13 = 0; }


#define 	LED_SEGA_HIGH		{ P04 = 1;P0M |= 0x10; }
#define 	LED_SEGF_HIGH		{ P05 = 1;P0M |= 0x20; }
#define 	LED_SEGB_HIGH		{ P30 = 1;P3M |= 0x01; }
#define 	LED_SEGE_HIGH		{ P31 = 1;P3M |= 0x02; }
#define 	LED_SEGD_HIGH		{ P32 = 1;P3M |= 0x04; }
#define 	LED_SEGDP_HIGH	{ P33 = 1;P3M |= 0x08; }
#define 	LED_SEGC_HIGH		{ P06 = 1;P0M |= 0x40; }
#define 	LED_SEGG_HIGH	  { P07 = 1;P0M |= 0x80; }

#define 	bLED_6_HIGH     { P31 = 1;P3M |= 0x02; }
#define 	bLED_7_HIGH	   	{ P32 = 1;P3M |= 0x04; }
#define 	bLED_8_HIGH	    { P33 = 1;P3M |= 0x08; }
#define 	bLED_9_HIGH		  { P06 = 1;P0M |= 0x40; }
#define 	bLED_10_HIGH	  { P07 = 1;P0M |= 0x80; }


#define standby_n    0x00
#define watt_n       0x0c
#define time_n       0x0d
#define lock_n       0x04
#define close_n      0x05
#define Ero_n        0x06
#define sw_n         0x07

extern unsigned char LED_B;
extern unsigned char bit_number;
extern unsigned char watt;

void display();
void lcd_bit();

// LEDÊý×Ö
typedef enum 
{
	LED_SEGA = 1<<0,			//  SegA
	LED_SEGB = 1<<1,			//  SegB
	LED_SEGC = 1<<2,			//  SegC
	LED_SEGD = 1<<3,			//  SegD
	LED_SEGE = 1<<4,			//  SegE
	LED_SEGF = 1<<5,			//  SegF
	LED_SEGG = 1<<6,			//  SegG
	LED_SEGP = 1<<7,			//  SegP	

	LED_0 = (LED_SEGA|LED_SEGB|LED_SEGC|LED_SEGD|LED_SEGE|LED_SEGF),				//  LED 0
	LED_1 = (LED_SEGB|LED_SEGC),																						//  LED 1
	LED_2 = (LED_SEGA|LED_SEGB|LED_SEGD|LED_SEGE|LED_SEGG),									//  LED 2
	LED_3 = (LED_SEGA|LED_SEGB|LED_SEGC|LED_SEGD|LED_SEGG),									//  LED 3
	LED_4 = (LED_SEGB|LED_SEGC|LED_SEGF|LED_SEGG),													//  LED 4
	LED_5 = (LED_SEGA|LED_SEGC|LED_SEGD|LED_SEGF|LED_SEGG),									//  LED 5
	LED_6 = (LED_SEGA|LED_SEGC|LED_SEGD|LED_SEGE|LED_SEGF|LED_SEGG),				//  LED 6
	LED_7 = (LED_SEGA|LED_SEGB|LED_SEGC),																		//  LED 7
	LED_8 = (LED_SEGA|LED_SEGB|LED_SEGC|LED_SEGD|LED_SEGE|LED_SEGF|LED_SEGG),//  LED 8
	LED_9 = (LED_SEGA|LED_SEGB|LED_SEGC|LED_SEGD|LED_SEGF|LED_SEGG),				//  LED 9		
	LED_E	=	(LED_SEGA|LED_SEGD|LED_SEGE|LED_SEGF|LED_SEGG),									//  LED E	
	LED_R	=	(LED_SEGA|LED_SEGB|LED_SEGC|LED_SEGE|LED_SEGF|LED_SEGG),			  //  LED R
	LED_P	=	(LED_SEGA|LED_SEGB|LED_SEGE|LED_SEGF|LED_SEGG),									//  LED P	
	LED_S	=	(LED_SEGA|LED_SEGC|LED_SEGD|LED_SEGF|LED_SEGG),									//  LED S	
	LED_L	=	(LED_SEGD|LED_SEGE|LED_SEGF),																		//  LED L		
	LED_U	=	(LED_SEGB|LED_SEGC|LED_SEGD|LED_SEGE|LED_SEGF),									//  LED U			
	LED_F	=	(LED_SEGA|LED_SEGE|LED_SEGF|LED_SEGG),													//  LED F		
	LED_A	=	(LED_SEGA|LED_SEGB|LED_SEGC|LED_SEGE|LED_SEGF|LED_SEGG),				//  LED A		
	LED_H	=	(LED_SEGB|LED_SEGC|LED_SEGE|LED_SEGF|LED_SEGG),									//  LED H		
	LED_T	=	(LED_SEGE|LED_SEGF|LED_SEGG),																		//  LED T	
	LED_d	=	(LED_SEGB|LED_SEGC|LED_SEGD|LED_SEGE|LED_SEGG),									//  LED d	
	LED_b	=	(LED_SEGC|LED_SEGD|LED_SEGE|LED_SEGF|LED_SEGG),									//  LED b	
	LED_C	=	(LED_SEGA|LED_SEGD|LED_SEGE|LED_SEGF),													//  LED C	
	LED_O	=	(LED_SEGA|LED_SEGB|LED_SEGC|LED_SEGD|LED_SEGE|LED_SEGF),			  //  LED O		
	LED_c	=	(LED_SEGD|LED_SEGE|LED_SEGG),																		//  LED c			
	LED_Y	=	(LED_SEGB|LED_SEGC|LED_SEGD|LED_SEGF|LED_SEGG),									//  LED Y		
	LED_i	=	(LED_SEGC),																											//  LED i			
	LED_N	=	(LED_SEGA|LED_SEGB|LED_SEGC|LED_SEGE|LED_SEGF),				          //  LED N	
	

};

#endif