/*****************************************************************************************
Filename	: captouch_main.h
Function	: 
*****************************************************************************************/
#ifndef		_CAPTOUCH_MAIN_H_
#define		_CAPTOUCH_MAIN_H_

#include <SN8F5754.h>

#define uchar	unsigned char 
#define uint	unsigned int	
#define ulong	unsigned long
	
#define u8	unsigned char 
#define u16	unsigned int
#define u32	unsigned long
//-------------------------------------------------------
//
//-------------------------------------------------------



union TwoByte
{
	uint16_t uniWord;
	uint8_t uniByte[2];
};

union FourByte
{
	uint32_t uniDWord;
	uint16_t uniWord[2];
	uint8_t uniByte[4];
};
//-----------------------------------------------------//
//	
//-----------------------------------------------------//
extern idata union FourByte g_lKeyCvt;
#define g_cKeyCvtL g_lKeyCvt.uniByte[3]							//Low byte of KeyStatus after debounce
#define g_cKeyCvtM g_lKeyCvt.uniByte[2]							//Mid byte of KeyStatus after debounce
#define g_cKeyCvtH g_lKeyCvt.uniByte[1]							//High byte of KeyStatus after debounce
#define g_lKeyCvtData g_lKeyCvt.uniDWord

extern idata union FourByte g_lKeyOld;
#define g_cKeyOldL g_lKeyOld.uniByte[3]							//Low byte of KeyStatus after debounce
#define g_cKeyOldM g_lKeyOld.uniByte[2]							//Mid byte of KeyStatus after debounce
#define g_cKeyOldH g_lKeyOld.uniByte[1]							//High byte of KeyStatus after debounce
#define g_lKeyOldData g_lKeyOld.uniDWord

extern bit f_bMultiKey;			//multi key flag
//-------------------------------------------------------
// <<< Use Configuration Wizard in Context Menu >>>\n
//-------------------------------------------------------
//-----------------------------------------------------//
// <h> Touch_Channel_Select
// 		<e0> P14_Touch_Enable
// 		<i> this is enable P14 touch key function 
// 		</e>
// 		<e1> P15_Touch_Enable
// 		<i> this is enable P15 touch key function 
// 		</e>
// 		<e2> P16_Touch_Enable
// 		<i> this is enable P16 touch key function 
// 		</e>
// 		<e3> P17_Touch_Enable
//		<i> this is enable P17 touch key function 
// 		</e>
// 		<e4> P20_Touch_Enable
// 		<i> this is enable P20 touch key function 
//		</e>
// 		<e5> P21_Touch_Enable
// 		<i> this is enable P21 touch key function 
// 		</e>
// 		<e6> P22_Touch_Enable
// 		<i> this is enable P22 touch key function 
// 		</e>
// 		<e7> P23_Touch_Enable
// 		<i> this is enable P23 touch key function 
// 		</e>
// 		<e8> P24_Touch_Enable
// 		<i> this is enable P24 touch key function 
// 		</e>
// 		<e9> P07_Touch_Enable
// 		<i> this is enable P07 touch key function 
// 		</e>
// 		<e10> P06_Touch_Enable
// 		<i> this is enable P06 touch key function 
// 		</e>
// 		<e11> P33_Touch_Enable
// 		<i> this is enable P33 touch key function 
// 		</e>
// 		<e12> P32_Touch_Enable
// 		<i> this is enable P32 touch key function 
// 		</e>
// 		<e13> P31_Touch_Enable
// 		<i> this is enable P31 touch key function 
// 		</e>
// 		<e14> P30_Touch_Enable
// 		<i> this is enable P30 touch key function 
// 		</e>
// 		<e15> P05_Touch_Enable
// 		<i> this is enable P05 touch key function 
// 		</e>
// 		<e16> P04_Touch_Enable
// 		<i> this is enable P04 touch key function 
// 		</e>
// 		<e17> P03_Touch_Enable
// 		<i> this is enable P03 touch key function 
// 		</e>
// 		<e18> P02_Touch_Enable
// 		<i> this is enable P02 touch key function 
// 		</e>
// 		<e19> P10_Touch_Enable
// 		<i> this is enable P10 touch key function 
// 		</e>
// 		<e20> P13_Touch_Enable
// 		<i> this is enable P13 touch key function 
// 		</e>
// 		<e21> P12_Touch_Enable
// 		<i> this is enable P12 touch key function, share with SWAT Pin 
// 		</e>
// 		<e22> P11_Touch_Enable
// 		<i> this is enable P11 touch key function 
// 		</e>
//----------------------------------------------------------------------------------------//
//	Sensing Pins setting
//	If the pins are enable the touch key function,
//	please make sure disable the pull-up register of the pins.
//----------------------------------------------------------------------------------------//
#define	TK_P14_EN		1
#define	TK_P15_EN		0
#define	TK_P16_EN		0
#define	TK_P17_EN		1
#define	TK_P20_EN		1
#define	TK_P21_EN		1
#define	TK_P22_EN		1
#define	TK_P23_EN		1

#define	TK_P24_EN		0
#define	TK_P07_EN		0
#define	TK_P06_EN		0
#define	TK_P33_EN		0
#define	TK_P32_EN		0
#define	TK_P31_EN		0
#define	TK_P30_EN		0
#define	TK_P05_EN		0

#define	TK_P04_EN		0
#define	TK_P03_EN		0
#define	TK_P02_EN		0
#define	TK_P10_EN		0
#define	TK_P13_EN		0
#define	TK_P12_EN		0
#define	TK_P11_EN		0
// </h>
//-----------------------------------------------------//
//	Note:
//	1. Use Debug Mode to debug the CapSensing parameter CapSensing sensitivity.
//	2. If enable Debug_Mode via I2C, SCL, SDA will be used by touch library for I2C master communication.
//	3. If enable Debug_Mode via UART, UTX, URX will be used by touch library for UART communication.
//	4. 建議在PCB layout時, 將VDD, P33&P32, VSS留出接口, 以便方便Debug使用.
//	5. 用戶可選擇硬件I2C或者UART來實現Debug Mode,只能選擇其中之一.
//-----------------------------------------------------//
// <h> Debug_Mode_Setting
// <i> enable Debug_Mode via UART or I2C Bus
//			<e0>	DEBUG_MODE_UART0
// 						<i> DEBUG_MODE_UART0 is enable Debug_Mode via UART0 Bus
//						<O1>	PFGA_UART_URXD0
// 						<i> When P02 is used as URX function, its touch key function needs to be turned off.
// 								<0=>URXD0_P02
//						<O2>	PFGA_UART_UTXD0
// 						<i> When P03 is used as UTX function, its touch key function needs to be turned off.
// 						<i> When P12 is used as UTX function, UART0 use as half duplex UTX function, its touch key and SWAT function needs to be turned off.
// 								<0=>UTXD0_P03
// 								<1=>UTXD0_P12
//						<O3>	UART_S0REL_125000
// 						<i> Set UART_S0REL_125000 according to Fcpu, The Debug Mode UART baudrate fixed as 125000
// 								<0=>UART_BR_8M
// 								<1=>UART_BR_4M
// 			</e>
//			<e4>	DEBUG_MODE_UART1
// 						<i> DEBUG_MODE_UART1 is enable Debug_Mode via UART1 Bus
//						<O5>	PFGA_UART_URXD1
// 						<i> When P33 is used as URX function, its touch key function needs to be turned off.
// 						<i> When P21 is used as URX function, its touch key function needs to be turned off.
// 								<0=>URXD1_P33
// 								<1=>URXD1_P21
//						<O6>	PFGA_UART_UTXD1
// 						<i> When P32 is used as UTX function, its touch key function needs to be turned off.
// 						<i> When P20 is used as UTX function, its touch key function needs to be turned off.
// 								<0=>UTXD1_P32
// 								<1=>UTXD1_P20
//						<O7>	UART_S1REL_125000
// 						<i> Set UART_S1REL_125000 according to Fcpu, The Debug Mode UART baudrate fixed as 125000
// 								<0=>UART_BR_8M
// 								<1=>UART_BR_4M
// 			</e>
//			<e8>	DEBUG_MODE_I2C
// 						<i> DEBUG_MODE_I2C is enable Debug_Mode via I2C Bus
//						<O9>	PFGA_I2C_SCL
// 						<i> When P15 is used as SCL function, its touch key function needs to be turned off.
// 						<i> When P32 is used as SCL function, its touch key function needs to be turned off.
// 								<0=>SCL_P15
// 								<1=>SCL_P32
//						<O10>	PFGA_I2C_SDA
// 						<i> When P16 is used as SDA function, its touch key function needs to be turned off.
// 						<i> When P33 is used as SDA function, its touch key function needs to be turned off.
// 								<0=>SDA_P16
// 								<1=>SDA_P33
//						<O11>	MASTER_I2C_CLOCK
// 						<i> 根据Fhosc设置为100Khz,不能超过200k
// 								<0=>I2C_CLOCK_100K_32M
// 								<1=>I2C_CLOCK_100K_16M
// 								<2=>I2C_CLOCK_100K_8M
// 			</e>
//-----------------------------------------------------//
//	Debug Mode下UART baudrate固定为125000
//-----------------------------------------------------//
#define DEBUG_MODE_UART0	1
#define PFGA_UART_URXD0	0
#define PFGA_UART_UTXD0	1
#define UART_S0REL_125000	0

#define DEBUG_MODE_UART1	0
#define PFGA_UART_URXD1	0
#define PFGA_UART_UTXD1	0
#define UART_S1REL_125000	0

#define DEBUG_MODE_I2C	0
#define PFGA_I2C_SCL	0
#define PFGA_I2C_SDA	0
#define MASTER_I2C_CLOCK 0
// </h>
//-----------------------------------------------------//
//	key press time limit function
//-----------------------------------------------------//
// <e0> Press_Time_Limit
// 		<i> this is enable key press time limit function 
//   	<o1> Max_valid_Press_Key_Count(1~23)
//   		<i> this is max valid press key in the same time
//   		<1-23>
//   	<o2> Press_time_for_invalid_Keys(1~65535)
//   		<i> the press time for invalid multi keys is input number *2ms 
//   		<1-65535>
//   	<o3> Press_time_for_all_Keys(1~65535)
//   		<i> the press time for all keys is input number *2ms 
//   		<1-65535>
#define TIME_LIMIT				1			//=1,enable key press Time limit function; =0,disable key press Time limit function;
#define MAX_PRESS_KEY_CNT	2			//Up to MAX_PRESS_KEY_CNT valid key presses can be identified
#define PRESS_MULTI_CNT		500		//for multi key pressed
#define PRESS_TIME_CNT		2500		//1~65535,key press Time max = PRESS_TIME_CNT*2ms
// </e>
//-----------------------------------------------------//
//
//-----------------------------------------------------//
// <h> Topping_Treatment
// 		<i> this is Topping Treatment for touch sensitivity
//   	<o0> Max_Delta_Setting(1~255)
//   		<i> the max delta is the input number *FT
//   		<1-255>
//   	<o1> Minus_Delta_Setting(1~255)
//   		<i> the max minus delta is the input number *FT
//   		<1-255>
#define MAX_DELAT_SET			3			//MAX_DELAT=FT*MAX_DELAT_SET
#define MINUS_DELAT_SET	  16		//MINUS_DELAT=FT*MINUS_DELAT_SET
// </h>
//-------------------------------------------------------
//
//-------------------------------------------------------
// <h> Debounce_Time_Setting
// 		<i> this is the software Debounce Time Setting for touch key
//  	<o0> Make_Debounce_Time(1~255)
//   		<i> the touch key Debounce Time is the input number *2ms
//  		<1-255>
//   	<o1> Break_Debounce_Time(1~255)
//   		<i> the touch key Debounce Time is the input number *2ms
//   		<1-255>
#define	KB_MAKE_DEBOUNCE_COUNT		30		//1~255, Key make time n * 2ms
#define	KB_BREAK_DEBOUNCE_COUNT		30		//1~255, Key break time n * 2ms
// </h>
//-----------------------------------------------------//
// <h> TCNT_Setting
// 	 	<i> this is TCNT setting 
//  	<o0> P14_TCNT_Setting(4~16) 	<4-16>
//  	<o1> P15_TCNT_Setting(4~16) 	<4-16>
//		<o2> P16_TCNT_Setting(4~16) 	<4-16>
//		<o3> P17_TCNT_Setting(4~16)  	<4-16>
//   	<o4> P20_TCNT_Setting(4~16)  	<4-16>
//   	<o5> P21_TCNT_Setting(4~16)	  <4-16>
//   	<o6> P22_TCNT_Setting(4~16)   <4-16>
//   	<o7> P23_TCNT_Setting(4~16)  	<4-16>
//   	<o8> P24_TCNT_Setting(4~16)  	<4-16>
//   	<o9> P07_TCNT_Setting(4~16)  	<4-16>
//   	<o10> P06_TCNT_Setting(4~16) 	<4-16>
//   	<o11> P33_TCNT_Setting(4~16) 	<4-16>
//   	<o12> P32_TCNT_Setting(4~16) 	<4-16>
//   	<o13> P31_TCNT_Setting(4~16) 	<4-16>
//   	<o14> P30_TCNT_Setting(4~16) 	<4-16>
//   	<o15> P05_TCNT_Setting(4~16) 	<4-16>
//   	<o16> P04_TCNT_Setting(4~16)	<4-16>
//   	<o17> P03_TCNT_Setting(4~16)	<4-16>
//   	<o18> P02_TCNT_Setting(4~16)	<4-16>
//   	<o19> P10_TCNT_Setting(4~16) 	<4-16>
//   	<o20> P13_TCNT_Setting(4~16) 	<4-16>
//   	<o21> P12_TCNT_Setting(4~16) 	<4-16>
//   	<o22> P11_TCNT_Setting(4~16) 	<4-16>
#define	P14_TCNT		6 			//4~16
#define	P15_TCNT		6 			//4~16
#define	P16_TCNT		6 			//4~16
#define	P17_TCNT		6 			//4~16
#define	P20_TCNT		6 			//4~16
#define	P21_TCNT		6 			//4~16
#define	P22_TCNT		6 			//4~16
#define	P23_TCNT		6 			//4~16
//-------------------------------------------------//
#define	P24_TCNT		6 			//4~16
#define	P07_TCNT		6 			//4~16
#define	P06_TCNT		6 			//4~16
#define	P33_TCNT		6 			//4~16
#define	P32_TCNT		6 			//4~16
#define	P31_TCNT		6 			//4~16
#define	P30_TCNT		6 			//4~16
#define	P05_TCNT		6 			//4~16
//-------------------------------------------------//
#define	P04_TCNT		6 			//4~16
#define	P03_TCNT		6 			//4~16
#define	P02_TCNT		6 			//4~16
#define	P10_TCNT		6 			//4~16
#define	P13_TCNT		6 			//4~16
#define	P12_TCNT		6 			//4~16
#define	P11_TCNT		6 			//4~16
// </h>
//-----------------------------------------------------//
// <h> Touch_Init_Setting
// 		<i> this is touch initial setting 
//   	<o0> Touch_Init_For_PowerOn(1~65535)
//     	<i> After power on, discard the set number of measurement times and wait for the system to stabilize
//    	<1-65535>
//   <o1> Touch_Init_For_Working(1~65535)
//     	<i> When the touch key needs to be reset during operation, discard the set number of measurement times and wait for the system to stabilize
//     	<1-65535>
#define	TK_BASE_RESET			250		//1~65535
#define TK_BASE_INIT			1			//1~65535
// </h>
//-----------------------------------------------------//
// <<< end of configuration section >>>
//-----------------------------------------------------//
// <e> SWAT_Pin_Select
// 		<i> 1: enable SWAT function.(P1.2 acts as SWAT pin and internal pull-up is enabled) 
// 		<i> 0: disable SWAT function.(P1.2 acts as GPIO pin and internal pull-up is disabled) 
#define SWAT_CMD				0
// </e>

#define config_SWAT(SWAT_CMD)	DEGCMD=(SWAT_CMD==0)?0X00:0XA5

void switch_channel(void);		//for touch key library
void touch_meas_reset(unsigned int iBaseReset);	//for touch key library
void pre_touch(void);											//for touch key library
void scan_touch_key(void);								//for touch key library
void touchkey_checkdebounce(void);
void touch_isr_timer(void);
void init_sys(void);
void touch_key_cvt(void);
//----------------------------------------------------------------------------------------//
//
//----------------------------------------------------------------------------------------//
#endif