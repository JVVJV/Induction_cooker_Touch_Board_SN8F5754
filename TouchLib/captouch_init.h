//--------------------------------------------------------------------------
//Filename		: captouch_init.h
//Function		: 
//Description	: 
//--------------------------------------------------------------------------
#ifndef _CAPTOUCH_INIT_H_
#define _CAPTOUCH_INIT_H_
//-----------------------------------------------------//
#define TK0_EN_NUM	(TK_P02_EN+TK_P03_EN+TK_P04_EN+TK_P05_EN+TK_P06_EN+TK_P07_EN)
#define TK1_EN_NUM	(TK_P10_EN+TK_P11_EN+TK_P12_EN+TK_P13_EN+TK_P14_EN+TK_P15_EN+TK_P16_EN+TK_P17_EN)
#define TK2_EN_NUM	(TK_P20_EN+TK_P21_EN+TK_P22_EN+TK_P23_EN+TK_P24_EN)
#define TK3_EN_NUM	(TK_P30_EN+TK_P31_EN+TK_P32_EN+TK_P33_EN)
#define TK_EN_NUM		(TK0_EN_NUM+TK1_EN_NUM+TK2_EN_NUM+TK3_EN_NUM)
#define TK_EN_MAX		23

#define SCAN_P14	0x00
#define SCAN_P15	0x01
#define SCAN_P16	0x02
#define SCAN_P17	0x03
#define SCAN_P20	0x04
#define SCAN_P21	0x05
#define SCAN_P22	0x06
#define SCAN_P23	0x07

#define SCAN_P24	0x08
#define SCAN_P07	0x09
#define SCAN_P06	0x0A
#define SCAN_P33	0x0B
#define SCAN_P32	0x0C
#define SCAN_P31	0x0D
#define SCAN_P30	0x0E
#define SCAN_P05	0x0F

#define SCAN_P04	0x10
#define SCAN_P03	0x11
#define SCAN_P02	0x12
#define SCAN_P10	0x13
#define SCAN_P13	0x14
#define SCAN_P12	0x15
#define SCAN_P11	0x16

#define SCAN_DUMMY	0x17

//-----------------------------------------------------//
//	
//-----------------------------------------------------//
#define FRQ_NUM							2
#define FRQ_NUM_MAX					2
#define	DEBUG_FREQ					0

#define FRQ_TSWY0						8
#define FRQ_TSWY1						10
//-----------------------------------------------------//
//	(BASE_CNT_PLUS+BASE_CNT_MINUS)<256
//-----------------------------------------------------//
#define BASE_UPDATE_TIME					400		//BASE_UPDATE_TIME*MS
#define CHANNEL_TIME_NUMERATOR		(3*FRQ_NUM)			//
#define CHANNEL_TIME_DENOMINATOR	2			//Meas Time for each channel is CHANNEL_TIME_NUMERATOR/CHANNEL_TIME_DENOMINATOR ms

#define BASE_CNT						((BASE_UPDATE_TIME*CHANNEL_TIME_DENOMINATOR)/(CHANNEL_TIME_NUMERATOR*(TK_EN_NUM)))	//BASE_CNT<=125
#define BASE_CNT_MAX				255

#define	BASE_CNT_PLUS			BASE_CNT		//cnt for update plus base 
#define	BASE_CNT_MINUS		BASE_CNT		//cnt for update minus base
#define BASE_CNT_AVER			BASE_CNT		//cnt for update base
//---------------------------------------------------
#define DEBOUNCE_COUNT_STATE 0XFF

#define DEFAULT_DUMMY_COUNT	1500
//-----------------------------------------------------//
//	
//-----------------------------------------------------//
#define MEAS_TIME_SET				8			//MEAS_TIME_SET*0.5ms
//---------------------------------------------------
#define TOUCH_INTGND_2MS		4			//0.5ms * TOUCH_INTGND_2MS = 2ms
//-----------------------------------------------------//
#define TK_P1_SET		(TK_P10_EN*0X01+TK_P11_EN*0X02+TK_P12_EN*0X04+TK_P13_EN*0X08+TK_P14_EN*0X10+TK_P15_EN*0X20+TK_P16_EN*0X40+TK_P17_EN*0X80)
#define TK_P2_SET		(TK_P20_EN*0X01+TK_P21_EN*0X02+TK_P22_EN*0X04+TK_P23_EN*0X08+TK_P24_EN*0X10+0X20)
#define TK_P0_SET		(TK_P02_EN*0X04+TK_P03_EN*0X08+TK_P04_EN*0X10+TK_P05_EN*0X20+TK_P06_EN*0X40+TK_P07_EN*0X80)
#define TK_P3_SET		(TK_P30_EN*0X01+TK_P31_EN*0X02+TK_P32_EN*0X04+TK_P33_EN*0X08)
//-----------------------------------------------------//
//
//-----------------------------------------------------//
#define I2C_CLOCK_RATE_8	0X03		//Fhosc/8
#define I2C_CLOCK_RATE_4	0X02		//Fhosc/4
#define I2C_CLOCK_RATE_2	0X01		//Fhosc/2
#define I2C_CLOCK_RATE_1	0X00		//Fhosc/1

#define I2C_CLOCK_100K_8M		I2C_CLOCK_RATE_2
#define I2C_CLOCK_100K_16M	I2C_CLOCK_RATE_4
#define I2C_CLOCK_100K_32M	I2C_CLOCK_RATE_8
//-----------------------------------------------------//
#define UART_BR_8M					0x03fe
#define UART_BR_4M					0x03ff
//---------------------------------------------------
extern idata uint8_t g_cTouchIntgnd2ms;
extern bit f_bTouchIntgnd2ms;
//-----------------------------------------------------//
//
//-----------------------------------------------------//
#if DEBUG_MODE_UART0||DEBUG_MODE_UART1||DEBUG_MODE_I2C
extern xdata uint8_t g_cDebugData[2];
extern xdata uint8_t g_cDebugFreq;
#endif
extern idata uint8_t g_cCKfreqSelectPre;
//-----------------------------------------------------//
extern idata uint16_t g_iPressTime;
extern code uint8_t g_cMaxPressCnt;
//-----------------------------------------------------//
extern code uint8_t g_cMeasNumCnt;
//-----------------------------------------------------//
extern code uint8_t g_cBaseCntPlus;
extern code uint8_t g_cBaseCntMinus;
extern code uint8_t g_cBaseCntAver;
//-----------------------------------------------------//
extern code uint8_t g_cMaxDeltaSet;
extern code uint8_t g_cMinusDeltaSet;
//-----------------------------------------------------//
extern code uint8_t g_cMeasTimeSet;		//save MEAS_TIME_SET
extern xdata uint8_t g_cMeasTimeLimit;	//single channel meastime limit
//-----------------------------------------------------//
//
//-----------------------------------------------------//
extern bit f_bMeasBase;
extern bit f_bKeyStatusUpdate;	//update key in information
extern bit f_bStartMeas;

extern xdata uint16_t g_iChannelCnt;
extern idata uint8_t g_cMeasChannel;
extern xdata uint8_t g_cCKfreqSelect;
extern code uint16_t g_iLibVersion[];

extern code uint8_t g_cTabCTnBuf[];
extern code uint8_t g_cCmTcntPara[];
extern code uint16_t g_iCmFtPara[FRQ_NUM_MAX][TK_EN_MAX];
extern code uint16_t g_iCmNtPara[FRQ_NUM_MAX][TK_EN_MAX];
//-----------------------------------------------------//
//
//-----------------------------------------------------//
extern code uint8_t g_cKeyMakeDebounceCnt;			//** Key make time n * 20ms
extern code uint8_t g_cKeyBreakDebounceCnt;		//** Key break time n * 20ms

extern code uint16_t g_iDefaultDummyCount;

extern idata union FourByte g_lKeyStatus;						//
extern xdata uint8_t g_cDataStatus;

extern code uint8_t g_cFrqNumCnt;
extern code uint8_t g_cFrqTswSet[FRQ_NUM_MAX];
extern xdata union FourByte g_lKeyStatusBuf[FRQ_NUM];
//-------------------------------------------------------
//	registers for CM
//-------------------------------------------------------
union DataFormat
{
	uint8_t cMeasData[12];
	struct{
		uint16_t iAver;
		uint16_t iMeas;
		uint16_t iBase;
		uint8_t cSpecDownCnt;
		uint8_t cNormUpDownCnt;
		uint16_t iFT;
		uint16_t iNT;
	}MeasData;
};

extern xdata union DataFormat g_cCmMeasData[FRQ_NUM_MAX][TK_EN_MAX];
//-------------------------------------------------------
//	registers for CM
//-------------------------------------------------------
union KeyFormat      //** SZ define 
{
	uint8_t cKeyData[2];
	struct{
		uint8_t cDebounceStatus;
		uint8_t cDebounce;
	}KeyData;
};

extern xdata union KeyFormat g_cCmKeyData[];
//-------------------------------------------------------
//	registers for CM
//-------------------------------------------------------
union DumFormat      //** SZ define 
{
	uint8_t cDumData[8];
	struct{
		uint16_t iAver;
		uint16_t iBase;
    uint16_t iDummyUpCnt;
    uint16_t iDummyDownCnt;
	}DumData;
};

extern xdata union DumFormat g_cDumData[];
//-----------------------------------------------------//
//
//-----------------------------------------------------//
void init_touch_port(void);
void init_touch(void);
void init_debug_data(void);
void touch_keystatus_reset(void);
void touchkey_checkdebounce(void);
void captouch_intgnd(void);
void init_delay_sleep(void);

void debug_i2c_comm(void);
void debug_uart_comm(void);
//--------------------------------------------------------------------------
#endif	//#ifndef _CAPTOUCH_INIT_H_