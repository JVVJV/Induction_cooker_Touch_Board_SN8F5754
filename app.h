#ifndef _APP_H_
#define _APP_H_

#define buzOn  {P2M|= 0x10;P24 = 0;}
#define buzOff  {P2M&= ~0x10;P24 = 0;}

//#define	O_BUZ_ON		 PW1M |= 0x80;													
//#define	O_BUZ_OFF		PW1M &= ~0X80;

// Three-level menu, First level: Power Switch
typedef enum {
    APP_STATE_CLOSE,
    APP_STATE_STANDBY
} AppState;

// Three-level menu, Second level: Status
typedef enum {
    STATUS_OPEN  = 0x01,
    STATUS_LOCK  = 0x08,
    STATUS_ERROR = 0x06
} DeviceStatus;

// Three-level menu, Third level: Function
typedef enum {
    MODE_NOTASK = 0x00,
    MODE_HOTPOT = 0x02,
    MODE_COOK   = 0x03,
    MODE_BOIL   = 0x04,
    MODE_TIMER  = 0x05,
    MODE_ADJUST = 0x07
} WorkMode;

typedef enum {
    CMD_NONE   = 0x00,
    CMD_HOTPOT = 0x4C,
    CMD_COOK   = 0x4D,
    CMD_BOIL   = 0x4F
} I2CCommand;

typedef enum {
    ERROR_NONE = 0,
    ERROR_I2C,
    ERROR_MAIN
} ErrorType;

//
#define plus   0x09
#define minus  0x10


#define KEY_FIFO_SIZE 8

extern volatile unsigned char keylong_1ms;
extern volatile unsigned char keylong_1msF;

extern unsigned char key_fifo[KEY_FIFO_SIZE];

extern unsigned char read;
extern unsigned char write;

extern volatile AppState sw;
extern volatile unsigned char buztime_500msF;
extern unsigned char mode;
extern DeviceStatus status;
extern unsigned char err_num;
extern volatile ErrorType current_error;

//extern unsigned char bflag;
extern unsigned char childLockActive;	

extern unsigned char wat_level;
extern volatile unsigned char time_level;

extern const unsigned int code power_table[];
extern const unsigned char code power_cmd_table[];
	
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
