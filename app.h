#ifndef _APP_H_
#define _APP_H_

#define buzOn  {P2M|= 0x10;P24 = 0;}
#define buzOff  {P2M&= ~0x10;P24 = 0;}

//#define	O_BUZ_ON		 PW1M |= 0x80;													
//#define	O_BUZ_OFF		PW1M &= ~0X80;

//三层菜单 第一层 开关
#define close   0x00           
#define standby 0xFF

//三层菜单 第二层 状态
#define open    0x01
#define lock    0x08
#define erro    0x06

//三层菜单 第三层 功能
#define notask  0x00
#define hotpot  0x02
#define cook    0x03
#define boil    0x04
#define timer   0x05
#define adjust  0x07

//
#define plus   0x09
#define minus  0x10


#define KEY_FIFO_SIZE 8

extern unsigned char keylong_1ms;
extern unsigned char keylong_1msF;

extern unsigned char fifobuf[KEY_FIFO_SIZE];
extern unsigned char keybuf;

extern unsigned char read;
extern unsigned char write;

extern volatile unsigned char sw;
extern volatile unsigned char buztime_500msF;
extern unsigned char mode;
extern unsigned char status;
extern unsigned char err_num;

extern unsigned char bflag;
extern unsigned char childLockActive;	

extern unsigned char wat_level;
extern volatile unsigned char time_level;

extern unsigned int wat_tab[];
	
extern volatile unsigned char knob_time;
extern volatile unsigned char disp_chan_tm1;
extern volatile unsigned char disp_chan_tm2;
extern volatile unsigned char disp_delay;

void buzzerOff();
void app();
void buzzerOn();
void fifowrite(unsigned char num); 
void disp_time();

#endif
