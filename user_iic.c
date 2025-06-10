#include "app.h"
#include "sn8f5754.h"
#include "captouch_main.h"
#include "iic.h"
#include "sonix_user.h"
#include "user_isr.h"

//Master
volatile unsigned char MasterBuf[I2C_MasterMax] = {0};
volatile unsigned char	fI2c_RecvOk  = 0;
volatile unsigned char MasterBufLen = 0;

//Slave
volatile unsigned char SlaveBuf[I2C_SlaveMax] = {0};
volatile unsigned char SlaveBufLen  = 0;

//App
unsigned char MainTemCode;
unsigned char MainMegCode;
unsigned char MainWatCode=0x00;
volatile unsigned char I2CErrorCode = I2C_ERR_NONE;
static unsigned int I2CTimeoutCnt = 0;

static uint8_t calc_checksum(const uint8_t *buf, uint8_t len)
{
    uint8_t i, sum = 0;

    for(i = 0; i < len; i++)
        sum += buf[i];

    return 0xFF - sum;
}

void IIC_Init()
{
	P1M  &= 0x9F;
	P1UR |= 0x60;      
	
	SMBSEL |= 0X00;    //P15 P16 input
	
	I2CCON |= 0xC0;    //configure I2C clock(T1)and enable I2C.               
	
	EI2C = 1;                     		// I2C Interrupt enable
	I2CADR = I2C_SLAVE_ADDR;     			// init slave addr	
	I2CCON |= 0x04;               		// AA = 1
}


void I2C_TimeoutTick(void)
{
  if(I2CTimeoutCnt < I2C_TIMEOUT_LIMIT)
    I2CTimeoutCnt++;
}


void I2C_DataCom(void)
{
	uint8_t i,CheckSum;
  
  if(!fI2c_RecvOk)
  {
    if(I2CTimeoutCnt > I2C_TIMEOUT_LIMIT)
    {
      I2CTimeoutCnt = 0;
      I2CErrorCode = I2C_ERR_TIMEOUT;
      I2CCON &= ~mskI2CCON_I2C_ENABLE;
      I2CCON |= mskI2CCON_I2C_ENABLE;
    }
    return;
  }

  I2CTimeoutCnt = 0;
  fI2c_RecvOk =0;
  
  // verify checksum
  CheckSum = calc_checksum(MasterBuf, I2C_MasterCs);

  if(CheckSum==MasterBuf[I2C_MasterCs])
  {
    MainMegCode = MasterBuf[I2C_Addr];
    MainTemCode = MasterBuf[I2C_Temp];
  }
      
  // prepare reply data
  for(i=0,CheckSum=0;i<=1;i++)  // two bytes
  {
    SlaveBuf[i] = MainWatCode;	
  }

  CheckSum = calc_checksum(SlaveBuf, I2C_SlaveCS);
  SlaveBuf[I2C_SlaveCS] = CheckSum;
  
}


/**
 * @brief  isr_i2c_slave
 * @param  none
 * @return none
 **/
void isr_i2c_slave (void) interrupt ISRI2c
{
	switch(I2CSTA)
	{     
		//Slave Transmit   
		case I2C_ST_SLA_ACK:
		{
			SlaveBufLen = 0;
			I2CDAT = SlaveBuf[SlaveBufLen++];	
			break;	
		}			
		case I2C_ST_DATA_ACK:		
    case I2C_ST_DATA_NACK:  
    case I2C_ST_LAST_DATA:
		{
			I2CDAT = SlaveBuf[SlaveBufLen++];	
			break;
		}
	
		//Slave Receive
		case I2C_SR_SLA_ACK:
		case I2C_SR_GCALL_ACK:
		{
			MasterBufLen = 0;	
			break;
		}
		case I2C_SR_DATA_ACK:
		case I2C_SR_GCALL_DATA_ACK:
		{
			MasterBuf[MasterBufLen++] = I2CDAT;
			if(MasterBufLen == I2C_MasterMax)
				fI2c_RecvOk = 1;
			break;
		}
    case I2C_SR_STOP:
    {
      MasterBufLen = 0;
      SlaveBufLen = 0;
      I2CCON &= 0xCF;     // Clear STA & STOP
      break;
    }
    
    default:
    {
      MasterBufLen = 0;
      SlaveBufLen = 0;
      I2CErrorCode = I2C_ERR_NO_RESP;
      I2CCON &= 0xCF;                   // Clear STA & STOP
      I2CCON &= ~mskI2CCON_I2C_ENABLE;
      I2CCON |= mskI2CCON_I2C_ENABLE;
      break;
    }
	}
	
	I2CCON |= 0x04; 													// AA = 1	
	I2CCON &= 0xF7;        										// Clear SI
}

