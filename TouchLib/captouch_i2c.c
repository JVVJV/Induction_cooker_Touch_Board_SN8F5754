//--------------------------------------------------------------------------
//Filename		: captouch_i2c.c
//Function		: 
//--------------------------------------------------------------------------
#include "captouch_i2c.h"
#include <string.h>
#include "captouch_init.h"
//-----------------------------------------------------------------------------
// Global Variables 
//-----------------------------------------------------------------------------
#if	DEBUG_MODE_I2C
bit f_bI2cEnding;												//=1,I2C is busy; =0, I2C is idle
bit f_bI2cErr;													//i2c error flag
xdata uchar g_cI2cData[MAX_DATA_LEN];	//i2c DATA BUF
xdata uchar g_cI2cAddr;									//i2c slave address
xdata uchar g_cI2cLen;									//I2C RX/TX DATA LENTH
xdata uchar g_cI2cCnt;									//i2c data buf point
#endif
//-----------------------------------------------------------------------------
//Function:   void I2C_Init(void)
//Description:
//          SCL and SDA need to external pull high
//-----------------------------------------------------------------------------
#if	DEBUG_MODE_I2C
void i2c_master_init(void)
{
	P_SCL = 1;
	PM_SCL_IN;				//SCL as input
	P_SDA = 1;
	PM_SDA_IN;				//SDA as input
	I2CMX_SET;
	I2CCON = 0x40|(I2C_CLOCK_RATE&0x83);//0x45;//0x43;//0x40;//    //I2C enable (ENS1),Fclk = Fcpu/160 = 100K
	EI2C = 1;         // I2C interrupt enable
}
#endif
//-----------------------------------------------------------------------------
//  Function:   I2C interrupt
//  Description:      
//
//-----------------------------------------------------------------------------
#if	DEBUG_MODE_I2C
void isr_i2c(void) interrupt ISRI2c    				// Vector @  0x43
{
	f_bI2cErr = 0;
	switch (I2CSTA)
	{
			// tx mode
			case 0x08:
					I2CCON &= 0xDF;             				// START (STA) = 0
					I2CDAT = g_cI2cAddr;         				// Tx/Rx addr
					break;
			case 0x18:                      				// write first byte
					I2CDAT = g_cI2cData[g_cI2cCnt++];
					g_cI2cLen--;
					break;
			case 0x28:                      				// write n byte
					if(g_cI2cLen == 0)									// chk length if empty
					{        							
						I2CCON |= 0x10;         					// STOP (STO)
						f_bI2cEnding = 0;
						g_cI2cCnt = 0;
					}
					else
					{
						I2CDAT = g_cI2cData[g_cI2cCnt++];
						g_cI2cLen--;
					}
					break;		
					
			//    rx mode    
			case 0x40:                      				// get slave addr
					if(g_cI2cLen>1)											//read n byte
					{
						I2CCON |= 0x04;            				// AA = 1
					}
					else																//read one byte
					{
						I2CCON &= 0xFB;         					// AA = 0
					}
					break;
			case 0x50:                      				// read n byte
					g_cI2cData[g_cI2cCnt++] = I2CDAT; 
					if(g_cI2cCnt == (g_cI2cLen-1))
					{
						I2CCON &= 0xFB;         					// AA = 0
					}
					else
					{                
						I2CCON |= 0x04;        					// AA = 1
					}
					break;
			case 0x58:                      				// read last byte & stop
					g_cI2cData[g_cI2cCnt] = I2CDAT; 
					I2CCON |= 0x10;             				// STOP (STO)
					f_bI2cEnding = 0;
					break;
			
			default:
					I2CCON |= 0x10;             				// STOP (STO)
					f_bI2cErr = 1;
					f_bI2cEnding = 0;
	}

	I2CCON &= 0xF7;                     				// Clear I2C flag (SI)        
}
#endif
//--------------------------------------------------------------------------
//subroutine	: 
//Function		: 
//--------------------------------------------------------------------------
#if DEBUG_MODE_I2C
void start_debug_i2c(void)
{
	I2CCON |= 0x20;        // START (STA) = 1
}
#endif
#if DEBUG_MODE_I2C
void stop_debug_i2c(void)
{
	I2CCON |= 0x10;       // STOP (STO)
}
#endif
