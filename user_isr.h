#ifndef _ISR_H_
#define _ISR_H_


typedef struct{
		uint8_t 	fTime1ms:1,
	            count1ms;
		uint8_t 	fTime100ms:1,
							count100ms;
		uint8_t 	fTime1s:1,
							count1s;
		uint8_t 	fTime1min:1,
							count1min;	
		uint8_t 	fTime1h:1,
							count1h;		
}IntGnd_s;	

extern volatile IntGnd_s IntGnd; 

extern volatile unsigned char set_time;
extern volatile unsigned char tm_keydelay;

#endif
