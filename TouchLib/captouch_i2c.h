//--------------------------------------------------------------------------
//Filename		: captouch_i2c.h
//Function		: 
//Description	: 
//--------------------------------------------------------------------------
#include "captouch_init.h"

#ifndef _CAPTOUCH_I2C_H_
#define _CAPTOUCH_I2C_H_
//-----------------------------------------------------//
#if DEBUG_MODE_I2C	//I2CΩ≈Œª≈‰÷√
	#if PFGA_I2C_SCL==0
			#define P_SCL	P15
			#define P_SDA	P16
			#define PM_SCL_IN	P1M&=(~0x20)
			#define PM_SDA_IN	P1M&=(~0x40)
			#define I2CMX_SET SMBSEL&=(~0X08)
	#else
			#define P_SCL	P32
			#define P_SDA	P33
			#define PM_SCL_IN	P3M&=(~0x04)
			#define PM_SDA_IN	P3M&=(~0x08)
			#define I2CMX_SET SMBSEL|=0X08
	#endif
	#if MASTER_I2C_CLOCK==0
			#define I2C_CLOCK_RATE		I2C_CLOCK_100K_32M
	#elif MASTER_I2C_CLOCK==1
			#define I2C_CLOCK_RATE		I2C_CLOCK_100K_16M
	#else
			#define I2C_CLOCK_RATE		I2C_CLOCK_100K_8M
	#endif
#endif
//-----------------------------------------------------//
#define MAX_DATA_LEN  12		//data buf lenth
#define I2C_BUS_DELAY_CNT		1000		//according to Fcpu
//-----------------------------------------------------//
#if	DEBUG_MODE_I2C
extern bit f_bI2cEnding;											//=1,I2C is busy; =0, I2C is idle
extern bit f_bI2cErr;													//i2c error flag
extern xdata uint8_t g_cI2cData[MAX_DATA_LEN];	//i2c DATA BUF
extern xdata uint8_t g_cI2cAddr;								//i2c slave address
extern xdata uint8_t g_cI2cLen;									//I2C RX/TX DATA LENTH
extern xdata uint8_t g_cI2cCnt;									//i2c data buf point
#endif
//-----------------------------------------------------//
#if	DEBUG_MODE_I2C
void i2c_master_init(void);
void start_debug_i2c(void);
void stop_debug_i2c(void);
#endif
//--------------------------------------------------------------------------
#endif	//#ifndef _CAPTOUCH_I2C_H_