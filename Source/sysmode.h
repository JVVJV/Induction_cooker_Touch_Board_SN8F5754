//--------------------------------------------------------------------------
//Filename		: sysmode.h
//Function		: 
//Description	: 
//--------------------------------------------------------------------------
#ifndef _SYSMODE_H_
#define _SYSMODE_H_
//---------------------------------------------------
extern bit f_bPowerSaving;
extern xdata uint16_t g_iPSDelayCnt;
extern xdata uint8_t g_cPSCTnMapBuf[];
extern xdata uint16_t g_iPSDummyBase[];
extern code uint8_t g_cPowerScanList[];
extern code uint8_t g_cPowerParam[];
extern xdata uint8_t g_cWakeUpMode;
//---------------------------------------------------
void init_sysmode(void);
void init_LPSM(void);
void init_LPSMCH(void);
void enter_LPSM(void);
void record_wakeup_source(uint8_t cWakeMode);
void init_wakeup_source(void);
void resume_wakeup_source(void);
void check_wakeup_source(void);
//---------------------------------------------------
#define DISABLE_WAKEUP	0
#define WAKEUP_ONCE			1
#define ENABLE_WAKEUP		2
#define WAKE_MODE				0x0F

enum wake_type
{
	IO_WAKE = 0x00,
	LPSM_WAKE = 0x10,
	TIMER0_WAKE = 0x20,
	ADC_WAKE = 0x40,
};
//-------------------------------------------------------
// <<< Use Configuration Wizard in Context Menu >>>\n
//-------------------------------------------------------
// <e> Power_Save_Enable
// 		<i> 1: enable Power Save function.
// 		<i> 0: disable Power Save function.
//---------------------------------------------------
#define POWER_SAVE				0				//=1, enable power save; =0, disable power save
//-------------------------------------------------------
// <h> Wakeup_Source_Setting

// 		<O> LPSM_WakeUp_Mode
// 		<i> Set LPSM WakeUp suorce.
// 			<0x10=>Disable wakeup
// 			<0x11=>enable wakeup once
// 			<0x12=>enable wakeup
#define LPSM_WAKEUP_MODE		16	

// 		<O> Timer0_WakeUp_Mode
// 		<i> Set Timer0 WakeUp suorce.
// 			<0x20=>Disable wakeup
// 			<0x21=>enable wakeup once
// 			<0x22=>enable wakeup
#define TIMER0_WAKEUP_MODE		32	

// 		<O> ADC_WakeUp_Mode
// 		<i> Set ADC WakeUp suorce.
// 			<0x40=>Disable wakeup
// 			<0x41=>enable wakeup once
// 			<0x42=>enable wakeup
#define ADC_WAKEUP_MODE		64

// 		<O> IO_WakeUp_Mode
// 		<i> Set P0/P1 WakeUp suorce.
// 			<0x00=>Disable wakeup
// 			<0x01=>enable wakeup once
// 			<0x02=>enable wakeup
#define IO_WAKEUP_MODE		0
// </h>
//---------------------------------------------------
// <h> Touch_channel_Setting
//		<O0>	Scan_List00
//		<i> From Scan_List00 to the first Scan_ListXX(XX=01,02,...22) is set to "SCAN_OFF".
//				<31=>SCAN_OFF
// 				<0=>SCAN_P14
//				<1=>SCAN_P15
//				<2=>SCAN_P16
//				<3=>SCAN_P17
//				<4=>SCAN_P20
//				<5=>SCAN_P21
//				<6=>SCAN_P22
//				<7=>SCAN_P23
// 				<8=>SCAN_P24
//				<9=>SCAN_P07
//				<10=>SCAN_P06
//				<11=>SCAN_P33
//				<12=>SCAN_P32
//				<13=>SCAN_P31
//				<14=>SCAN_P30
//				<15=>SCAN_P05
// 				<16=>SCAN_P04
//				<17=>SCAN_P03
//				<18=>SCAN_P02
//				<19=>SCAN_P10
//				<20=>SCAN_P13
//				<21=>SCAN_P12
//				<22=>SCAN_P11
//		<O1>	Scan_List01
//		<i> From Scan_List00 to the first Scan_ListXX(XX=01,02,...22) is set to "SCAN_OFF".
//				<31=>SCAN_OFF
// 				<0=>SCAN_P14
//				<1=>SCAN_P15
//				<2=>SCAN_P16
//				<3=>SCAN_P17
//				<4=>SCAN_P20
//				<5=>SCAN_P21
//				<6=>SCAN_P22
//				<7=>SCAN_P23
// 				<8=>SCAN_P24
//				<9=>SCAN_P07
//				<10=>SCAN_P06
//				<11=>SCAN_P33
//				<12=>SCAN_P32
//				<13=>SCAN_P31
//				<14=>SCAN_P30
//				<15=>SCAN_P05
// 				<16=>SCAN_P04
//				<17=>SCAN_P03
//				<18=>SCAN_P02
//				<19=>SCAN_P10
//				<20=>SCAN_P13
//				<21=>SCAN_P12
//				<22=>SCAN_P11
//		<O2>	Scan_List02
//		<i> From Scan_List00 to the first Scan_ListXX(XX=01,02,...22) is set to "SCAN_OFF".
//				<31=>SCAN_OFF
// 				<0=>SCAN_P14
//				<1=>SCAN_P15
//				<2=>SCAN_P16
//				<3=>SCAN_P17
//				<4=>SCAN_P20
//				<5=>SCAN_P21
//				<6=>SCAN_P22
//				<7=>SCAN_P23
// 				<8=>SCAN_P24
//				<9=>SCAN_P07
//				<10=>SCAN_P06
//				<11=>SCAN_P33
//				<12=>SCAN_P32
//				<13=>SCAN_P31
//				<14=>SCAN_P30
//				<15=>SCAN_P05
// 				<16=>SCAN_P04
//				<17=>SCAN_P03
//				<18=>SCAN_P02
//				<19=>SCAN_P10
//				<20=>SCAN_P13
//				<21=>SCAN_P12
//				<22=>SCAN_P11
//		<O3>	Scan_List03
//		<i> From Scan_List00 to the first Scan_ListXX(XX=01,02,...22) is set to "SCAN_OFF".
//				<31=>SCAN_OFF
// 				<0=>SCAN_P14
//				<1=>SCAN_P15
//				<2=>SCAN_P16
//				<3=>SCAN_P17
//				<4=>SCAN_P20
//				<5=>SCAN_P21
//				<6=>SCAN_P22
//				<7=>SCAN_P23
// 				<8=>SCAN_P24
//				<9=>SCAN_P07
//				<10=>SCAN_P06
//				<11=>SCAN_P33
//				<12=>SCAN_P32
//				<13=>SCAN_P31
//				<14=>SCAN_P30
//				<15=>SCAN_P05
// 				<16=>SCAN_P04
//				<17=>SCAN_P03
//				<18=>SCAN_P02
//				<19=>SCAN_P10
//				<20=>SCAN_P13
//				<21=>SCAN_P12
//				<22=>SCAN_P11
//		<O4>	Scan_List04
//		<i> From Scan_List00 to the first Scan_ListXX(XX=01,02,...22) is set to "SCAN_OFF".
//				<31=>SCAN_OFF
// 				<0=>SCAN_P14
//				<1=>SCAN_P15
//				<2=>SCAN_P16
//				<3=>SCAN_P17
//				<4=>SCAN_P20
//				<5=>SCAN_P21
//				<6=>SCAN_P22
//				<7=>SCAN_P23
// 				<8=>SCAN_P24
//				<9=>SCAN_P07
//				<10=>SCAN_P06
//				<11=>SCAN_P33
//				<12=>SCAN_P32
//				<13=>SCAN_P31
//				<14=>SCAN_P30
//				<15=>SCAN_P05
// 				<16=>SCAN_P04
//				<17=>SCAN_P03
//				<18=>SCAN_P02
//				<19=>SCAN_P10
//				<20=>SCAN_P13
//				<21=>SCAN_P12
//				<22=>SCAN_P11
//		<O5>	Scan_List05
//		<i> From Scan_List00 to the first Scan_ListXX(XX=01,02,...22) is set to "SCAN_OFF".
//				<31=>SCAN_OFF
// 				<0=>SCAN_P14
//				<1=>SCAN_P15
//				<2=>SCAN_P16
//				<3=>SCAN_P17
//				<4=>SCAN_P20
//				<5=>SCAN_P21
//				<6=>SCAN_P22
//				<7=>SCAN_P23
// 				<8=>SCAN_P24
//				<9=>SCAN_P07
//				<10=>SCAN_P06
//				<11=>SCAN_P33
//				<12=>SCAN_P32
//				<13=>SCAN_P31
//				<14=>SCAN_P30
//				<15=>SCAN_P05
// 				<16=>SCAN_P04
//				<17=>SCAN_P03
//				<18=>SCAN_P02
//				<19=>SCAN_P10
//				<20=>SCAN_P13
//				<21=>SCAN_P12
//				<22=>SCAN_P11
//		<O6>	Scan_List06
//		<i> From Scan_List00 to the first Scan_ListXX(XX=01,02,...22) is set to "SCAN_OFF".
//				<31=>SCAN_OFF
// 				<0=>SCAN_P14
//				<1=>SCAN_P15
//				<2=>SCAN_P16
//				<3=>SCAN_P17
//				<4=>SCAN_P20
//				<5=>SCAN_P21
//				<6=>SCAN_P22
//				<7=>SCAN_P23
// 				<8=>SCAN_P24
//				<9=>SCAN_P07
//				<10=>SCAN_P06
//				<11=>SCAN_P33
//				<12=>SCAN_P32
//				<13=>SCAN_P31
//				<14=>SCAN_P30
//				<15=>SCAN_P05
// 				<16=>SCAN_P04
//				<17=>SCAN_P03
//				<18=>SCAN_P02
//				<19=>SCAN_P10
//				<20=>SCAN_P13
//				<21=>SCAN_P12
//				<22=>SCAN_P11
//		<O7>	Scan_List07
//		<i> From Scan_List00 to the first Scan_ListXX(XX=01,02,...22) is set to "SCAN_OFF".
//				<31=>SCAN_OFF
// 				<0=>SCAN_P14
//				<1=>SCAN_P15
//				<2=>SCAN_P16
//				<3=>SCAN_P17
//				<4=>SCAN_P20
//				<5=>SCAN_P21
//				<6=>SCAN_P22
//				<7=>SCAN_P23
// 				<8=>SCAN_P24
//				<9=>SCAN_P07
//				<10=>SCAN_P06
//				<11=>SCAN_P33
//				<12=>SCAN_P32
//				<13=>SCAN_P31
//				<14=>SCAN_P30
//				<15=>SCAN_P05
// 				<16=>SCAN_P04
//				<17=>SCAN_P03
//				<18=>SCAN_P02
//				<19=>SCAN_P10
//				<20=>SCAN_P13
//				<21=>SCAN_P12
//				<22=>SCAN_P11
//		<O8>	Scan_List08
//		<i> From Scan_List00 to the first Scan_ListXX(XX=01,02,...22) is set to "SCAN_OFF".
//				<31=>SCAN_OFF
// 				<0=>SCAN_P14
//				<1=>SCAN_P15
//				<2=>SCAN_P16
//				<3=>SCAN_P17
//				<4=>SCAN_P20
//				<5=>SCAN_P21
//				<6=>SCAN_P22
//				<7=>SCAN_P23
// 				<8=>SCAN_P24
//				<9=>SCAN_P07
//				<10=>SCAN_P06
//				<11=>SCAN_P33
//				<12=>SCAN_P32
//				<13=>SCAN_P31
//				<14=>SCAN_P30
//				<15=>SCAN_P05
// 				<16=>SCAN_P04
//				<17=>SCAN_P03
//				<18=>SCAN_P02
//				<19=>SCAN_P10
//				<20=>SCAN_P13
//				<21=>SCAN_P12
//				<22=>SCAN_P11
//		<O9>	Scan_List09
//		<i> From Scan_List00 to the first Scan_ListXX(XX=01,02,...22) is set to "SCAN_OFF".
//				<31=>SCAN_OFF
// 				<0=>SCAN_P14
//				<1=>SCAN_P15
//				<2=>SCAN_P16
//				<3=>SCAN_P17
//				<4=>SCAN_P20
//				<5=>SCAN_P21
//				<6=>SCAN_P22
//				<7=>SCAN_P23
// 				<8=>SCAN_P24
//				<9=>SCAN_P07
//				<10=>SCAN_P06
//				<11=>SCAN_P33
//				<12=>SCAN_P32
//				<13=>SCAN_P31
//				<14=>SCAN_P30
//				<15=>SCAN_P05
// 				<16=>SCAN_P04
//				<17=>SCAN_P03
//				<18=>SCAN_P02
//				<19=>SCAN_P10
//				<20=>SCAN_P13
//				<21=>SCAN_P12
//				<22=>SCAN_P11
//		<O10>	Scan_List10
//		<i> From Scan_List00 to the first Scan_ListXX(XX=01,02,...22) is set to "SCAN_OFF".
//				<31=>SCAN_OFF
// 				<0=>SCAN_P14
//				<1=>SCAN_P15
//				<2=>SCAN_P16
//				<3=>SCAN_P17
//				<4=>SCAN_P20
//				<5=>SCAN_P21
//				<6=>SCAN_P22
//				<7=>SCAN_P23
// 				<8=>SCAN_P24
//				<9=>SCAN_P07
//				<10=>SCAN_P06
//				<11=>SCAN_P33
//				<12=>SCAN_P32
//				<13=>SCAN_P31
//				<14=>SCAN_P30
//				<15=>SCAN_P05
// 				<16=>SCAN_P04
//				<17=>SCAN_P03
//				<18=>SCAN_P02
//				<19=>SCAN_P10
//				<20=>SCAN_P13
//				<21=>SCAN_P12
//				<22=>SCAN_P11
//		<O11>	Scan_List11
//		<i> From Scan_List00 to the first Scan_ListXX(XX=01,02,...22) is set to "SCAN_OFF".
//				<31=>SCAN_OFF
// 				<0=>SCAN_P14
//				<1=>SCAN_P15
//				<2=>SCAN_P16
//				<3=>SCAN_P17
//				<4=>SCAN_P20
//				<5=>SCAN_P21
//				<6=>SCAN_P22
//				<7=>SCAN_P23
// 				<8=>SCAN_P24
//				<9=>SCAN_P07
//				<10=>SCAN_P06
//				<11=>SCAN_P33
//				<12=>SCAN_P32
//				<13=>SCAN_P31
//				<14=>SCAN_P30
//				<15=>SCAN_P05
// 				<16=>SCAN_P04
//				<17=>SCAN_P03
//				<18=>SCAN_P02
//				<19=>SCAN_P10
//				<20=>SCAN_P13
//				<21=>SCAN_P12
//				<22=>SCAN_P11
//		<O12>	Scan_List12
//		<i> From Scan_List00 to the first Scan_ListXX(XX=01,02,...22) is set to "SCAN_OFF".
//				<31=>SCAN_OFF
// 				<0=>SCAN_P14
//				<1=>SCAN_P15
//				<2=>SCAN_P16
//				<3=>SCAN_P17
//				<4=>SCAN_P20
//				<5=>SCAN_P21
//				<6=>SCAN_P22
//				<7=>SCAN_P23
// 				<8=>SCAN_P24
//				<9=>SCAN_P07
//				<10=>SCAN_P06
//				<11=>SCAN_P33
//				<12=>SCAN_P32
//				<13=>SCAN_P31
//				<14=>SCAN_P30
//				<15=>SCAN_P05
// 				<16=>SCAN_P04
//				<17=>SCAN_P03
//				<18=>SCAN_P02
//				<19=>SCAN_P10
//				<20=>SCAN_P13
//				<21=>SCAN_P12
//				<22=>SCAN_P11
//		<O13>	Scan_List13
//		<i> From Scan_List00 to the first Scan_ListXX(XX=01,02,...22) is set to "SCAN_OFF".
//				<31=>SCAN_OFF
// 				<0=>SCAN_P14
//				<1=>SCAN_P15
//				<2=>SCAN_P16
//				<3=>SCAN_P17
//				<4=>SCAN_P20
//				<5=>SCAN_P21
//				<6=>SCAN_P22
//				<7=>SCAN_P23
// 				<8=>SCAN_P24
//				<9=>SCAN_P07
//				<10=>SCAN_P06
//				<11=>SCAN_P33
//				<12=>SCAN_P32
//				<13=>SCAN_P31
//				<14=>SCAN_P30
//				<15=>SCAN_P05
// 				<16=>SCAN_P04
//				<17=>SCAN_P03
//				<18=>SCAN_P02
//				<19=>SCAN_P10
//				<20=>SCAN_P13
//				<21=>SCAN_P12
//				<22=>SCAN_P11
//		<O14>	Scan_List14
//		<i> From Scan_List00 to the first Scan_ListXX(XX=01,02,...22) is set to "SCAN_OFF".
//				<31=>SCAN_OFF
// 				<0=>SCAN_P14
//				<1=>SCAN_P15
//				<2=>SCAN_P16
//				<3=>SCAN_P17
//				<4=>SCAN_P20
//				<5=>SCAN_P21
//				<6=>SCAN_P22
//				<7=>SCAN_P23
// 				<8=>SCAN_P24
//				<9=>SCAN_P07
//				<10=>SCAN_P06
//				<11=>SCAN_P33
//				<12=>SCAN_P32
//				<13=>SCAN_P31
//				<14=>SCAN_P30
//				<15=>SCAN_P05
// 				<16=>SCAN_P04
//				<17=>SCAN_P03
//				<18=>SCAN_P02
//				<19=>SCAN_P10
//				<20=>SCAN_P13
//				<21=>SCAN_P12
//				<22=>SCAN_P11
//		<O15>	Scan_List15
//		<i> From Scan_List00 to the first Scan_ListXX(XX=01,02,...22) is set to "SCAN_OFF".
//				<31=>SCAN_OFF
// 				<0=>SCAN_P14
//				<1=>SCAN_P15
//				<2=>SCAN_P16
//				<3=>SCAN_P17
//				<4=>SCAN_P20
//				<5=>SCAN_P21
//				<6=>SCAN_P22
//				<7=>SCAN_P23
// 				<8=>SCAN_P24
//				<9=>SCAN_P07
//				<10=>SCAN_P06
//				<11=>SCAN_P33
//				<12=>SCAN_P32
//				<13=>SCAN_P31
//				<14=>SCAN_P30
//				<15=>SCAN_P05
// 				<16=>SCAN_P04
//				<17=>SCAN_P03
//				<18=>SCAN_P02
//				<19=>SCAN_P10
//				<20=>SCAN_P13
//				<21=>SCAN_P12
//				<22=>SCAN_P11
//		<O16>	Scan_List16
//		<i> From Scan_List00 to the first Scan_ListXX(XX=01,02,...22) is set to "SCAN_OFF".
//				<31=>SCAN_OFF
// 				<0=>SCAN_P14
//				<1=>SCAN_P15
//				<2=>SCAN_P16
//				<3=>SCAN_P17
//				<4=>SCAN_P20
//				<5=>SCAN_P21
//				<6=>SCAN_P22
//				<7=>SCAN_P23
// 				<8=>SCAN_P24
//				<9=>SCAN_P07
//				<10=>SCAN_P06
//				<11=>SCAN_P33
//				<12=>SCAN_P32
//				<13=>SCAN_P31
//				<14=>SCAN_P30
//				<15=>SCAN_P05
// 				<16=>SCAN_P04
//				<17=>SCAN_P03
//				<18=>SCAN_P02
//				<19=>SCAN_P10
//				<20=>SCAN_P13
//				<21=>SCAN_P12
//				<22=>SCAN_P11
//		<O17>	Scan_List17
//		<i> From Scan_List00 to the first Scan_ListXX(XX=01,02,...22) is set to "SCAN_OFF".
//				<31=>SCAN_OFF
// 				<0=>SCAN_P14
//				<1=>SCAN_P15
//				<2=>SCAN_P16
//				<3=>SCAN_P17
//				<4=>SCAN_P20
//				<5=>SCAN_P21
//				<6=>SCAN_P22
//				<7=>SCAN_P23
// 				<8=>SCAN_P24
//				<9=>SCAN_P07
//				<10=>SCAN_P06
//				<11=>SCAN_P33
//				<12=>SCAN_P32
//				<13=>SCAN_P31
//				<14=>SCAN_P30
//				<15=>SCAN_P05
// 				<16=>SCAN_P04
//				<17=>SCAN_P03
//				<18=>SCAN_P02
//				<19=>SCAN_P10
//				<20=>SCAN_P13
//				<21=>SCAN_P12
//				<22=>SCAN_P11
//		<O18>	Scan_List18
//		<i> From Scan_List00 to the first Scan_ListXX(XX=01,02,...22) is set to "SCAN_OFF".
//				<31=>SCAN_OFF
// 				<0=>SCAN_P14
//				<1=>SCAN_P15
//				<2=>SCAN_P16
//				<3=>SCAN_P17
//				<4=>SCAN_P20
//				<5=>SCAN_P21
//				<6=>SCAN_P22
//				<7=>SCAN_P23
// 				<8=>SCAN_P24
//				<9=>SCAN_P07
//				<10=>SCAN_P06
//				<11=>SCAN_P33
//				<12=>SCAN_P32
//				<13=>SCAN_P31
//				<14=>SCAN_P30
//				<15=>SCAN_P05
// 				<16=>SCAN_P04
//				<17=>SCAN_P03
//				<18=>SCAN_P02
//				<19=>SCAN_P10
//				<20=>SCAN_P13
//				<21=>SCAN_P12
//				<22=>SCAN_P11
//		<O19>	Scan_List19
//		<i> From Scan_List00 to the first Scan_ListXX(XX=01,02,...22) is set to "SCAN_OFF".
//				<31=>SCAN_OFF
// 				<0=>SCAN_P14
//				<1=>SCAN_P15
//				<2=>SCAN_P16
//				<3=>SCAN_P17
//				<4=>SCAN_P20
//				<5=>SCAN_P21
//				<6=>SCAN_P22
//				<7=>SCAN_P23
// 				<8=>SCAN_P24
//				<9=>SCAN_P07
//				<10=>SCAN_P06
//				<11=>SCAN_P33
//				<12=>SCAN_P32
//				<13=>SCAN_P31
//				<14=>SCAN_P30
//				<15=>SCAN_P05
// 				<16=>SCAN_P04
//				<17=>SCAN_P03
//				<18=>SCAN_P02
//				<19=>SCAN_P10
//				<20=>SCAN_P13
//				<21=>SCAN_P12
//				<22=>SCAN_P11
//		<O20>	Scan_List20
//		<i> From Scan_List00 to the first Scan_ListXX(XX=01,02,...22) is set to "SCAN_OFF".
//				<31=>SCAN_OFF
// 				<0=>SCAN_P14
//				<1=>SCAN_P15
//				<2=>SCAN_P16
//				<3=>SCAN_P17
//				<4=>SCAN_P20
//				<5=>SCAN_P21
//				<6=>SCAN_P22
//				<7=>SCAN_P23
// 				<8=>SCAN_P24
//				<9=>SCAN_P07
//				<10=>SCAN_P06
//				<11=>SCAN_P33
//				<12=>SCAN_P32
//				<13=>SCAN_P31
//				<14=>SCAN_P30
//				<15=>SCAN_P05
// 				<16=>SCAN_P04
//				<17=>SCAN_P03
//				<18=>SCAN_P02
//				<19=>SCAN_P10
//				<20=>SCAN_P13
//				<21=>SCAN_P12
//				<22=>SCAN_P11
//		<O21>	Scan_List21
//		<i> From Scan_List00 to the first Scan_ListXX(XX=01,02,...22) is set to "SCAN_OFF".
//				<31=>SCAN_OFF
// 				<0=>SCAN_P14
//				<1=>SCAN_P15
//				<2=>SCAN_P16
//				<3=>SCAN_P17
//				<4=>SCAN_P20
//				<5=>SCAN_P21
//				<6=>SCAN_P22
//				<7=>SCAN_P23
// 				<8=>SCAN_P24
//				<9=>SCAN_P07
//				<10=>SCAN_P06
//				<11=>SCAN_P33
//				<12=>SCAN_P32
//				<13=>SCAN_P31
//				<14=>SCAN_P30
//				<15=>SCAN_P05
// 				<16=>SCAN_P04
//				<17=>SCAN_P03
//				<18=>SCAN_P02
//				<19=>SCAN_P10
//				<20=>SCAN_P13
//				<21=>SCAN_P12
//				<22=>SCAN_P11
//		<O22>	Scan_List22
//		<i> From Scan_List00 to the first Scan_ListXX(XX=01,02,...22) is set to "SCAN_OFF".
//				<31=>SCAN_OFF
// 				<0=>SCAN_P14
//				<1=>SCAN_P15
//				<2=>SCAN_P16
//				<3=>SCAN_P17
//				<4=>SCAN_P20
//				<5=>SCAN_P21
//				<6=>SCAN_P22
//				<7=>SCAN_P23
// 				<8=>SCAN_P24
//				<9=>SCAN_P07
//				<10=>SCAN_P06
//				<11=>SCAN_P33
//				<12=>SCAN_P32
//				<13=>SCAN_P31
//				<14=>SCAN_P30
//				<15=>SCAN_P05
// 				<16=>SCAN_P04
//				<17=>SCAN_P03
//				<18=>SCAN_P02
//				<19=>SCAN_P10
//				<20=>SCAN_P13
//				<21=>SCAN_P12
//				<22=>SCAN_P11
//---------------------------------------------------
#define	SCAN_LIST00				0		//设置省电模式下的按键扫描顺序
#define	SCAN_LIST01				1
#define	SCAN_LIST02				2
#define	SCAN_LIST03				3
#define	SCAN_LIST04				31
#define	SCAN_LIST05				31

#define	SCAN_LIST06				31
#define	SCAN_LIST07				31
#define	SCAN_LIST08				31
#define	SCAN_LIST09				31
#define	SCAN_LIST10				31
#define	SCAN_LIST11				31

#define	SCAN_LIST12				31
#define	SCAN_LIST13				31
#define	SCAN_LIST14				31
#define	SCAN_LIST15				31
#define	SCAN_LIST16				31
#define	SCAN_LIST17				31

#define	SCAN_LIST18				31
#define	SCAN_LIST19				31
#define	SCAN_LIST20				31
#define	SCAN_LIST21				31
#define	SCAN_LIST22				31
// </h>
//---------------------------------------------------
// <h> Touch_Timer_Setting
//		<O>	Touch_Timer_Clock_Source_In_Power_Save_Mode
//		<i> Set this parameter according to the actual low-speed clock source(Flosc)
//				<16000ul=>Flosc_16kHz_ILRC
//				<32768ul=>External_32768_Crystal
#define TT_FLOSC_SOURCE		16000ul		//flosc
//---------------------------------------------------
//		<O>	Touch_Timer_Rate_In_Power_Save_Mode
//		<i> set the Touch Timer TTRATE In Power Save Mode.
//				<0x08=>TTRATE_128
//				<0x09=>TTRATE_64
//				<0x0A=>TTRATE_32
//				<0x0B=>TTRATE_16
//				<0x0C=>TTRATE_8
//				<0x0D=>TTRATE_4
//				<0x0E=>TTRATE_2
//				<0x0F=>TTRATE_1
#define TOUCH_TIMER_CLOCK_SET		0x09
//---------------------------------------------------
//   <o> Wakeup_Time_In_Power_Save_Mode(1~65535)_ms
//     	<i> Set the Touch Timer wakeup time In Power Save Mode
//     	<1-65535>
#define WAKE_TIMER		250
//---------------------------------------------------
//   <o> delay_time_of_Power_Save_mode(1~65535)_ms
//     	<i> delay time(ms) of delay enter Power Save mode when key press or power on
//     	<1-65535>
#define DELAY_TIME_SLEEP				3000
//---------------------------------------------------
//   <o> max_wakeup_once_time(1~127)_ms
//     	<i> maximum time when wakeup once
//     	<1-127>
#define MAX_WAKEUP_ONCE_TIME		5
// </h>
// </e>
//-----------------------------------------------------//
// <<< end of configuration section >>>
//-----------------------------------------------------//
#if SCAN_LIST00<23
	#if SCAN_LIST01<23
		#if SCAN_LIST02<23
			#if SCAN_LIST03<23
				#if SCAN_LIST04<23
					#if SCAN_LIST05<23
						#if SCAN_LIST06<23
							#if SCAN_LIST07<23
								#if SCAN_LIST08<23
									#if SCAN_LIST09<23
										#if SCAN_LIST10<23
											#if SCAN_LIST11<23
												#if SCAN_LIST12<23
													#if SCAN_LIST13<23
														#if SCAN_LIST14<23
															#if SCAN_LIST15<23
																#if SCAN_LIST16<23
																	#if SCAN_LIST17<23
																		#if SCAN_LIST18<23
																			#if SCAN_LIST19<23
																				#if SCAN_LIST20<23
																					#if SCAN_LIST21<23
																						#if SCAN_LIST22<23
																						#define PSTK_EN_NUM  		24
																						#else
																						#define PSTK_EN_NUM  		23
																						#endif
																					#else
																					#define PSTK_EN_NUM  		22
																					#endif
																				#else
																				#define PSTK_EN_NUM  		21
																				#endif
																			#else
																			#define PSTK_EN_NUM  		20
																			#endif
																		#else
																		#define PSTK_EN_NUM  		19
																		#endif
																	#else
																	#define PSTK_EN_NUM  		18
																	#endif
																#else
																#define PSTK_EN_NUM  		17
																#endif
															#else
															#define PSTK_EN_NUM  		16
															#endif
														#else
														#define PSTK_EN_NUM  		15
														#endif
													#else
													#define PSTK_EN_NUM  		14
													#endif
												#else
												#define PSTK_EN_NUM  		13
												#endif
											#else
											#define PSTK_EN_NUM  		12
											#endif
										#else
										#define PSTK_EN_NUM  		11
										#endif
									#else
									#define PSTK_EN_NUM  		10
									#endif
								#else
								#define PSTK_EN_NUM  		9
								#endif
							#else
							#define PSTK_EN_NUM  		8
							#endif
						#else
						#define PSTK_EN_NUM  		7
						#endif
					#else
					#define PSTK_EN_NUM  		6
					#endif
				#else
				#define PSTK_EN_NUM  		5
				#endif
			#else
			#define PSTK_EN_NUM  		4
			#endif
		#else
		#define PSTK_EN_NUM  		3
		#endif
	#else
	#define PSTK_EN_NUM  		2
	#endif
#else
#define PSTK_EN_NUM  			1
#endif

#define PSTK_EN_FREQ			(PSTK_EN_NUM/6)
#define PSTK_EN_REMAINDER	(PSTK_EN_NUM%6)

#if DELAY_TIME_SLEEP>1
	#define PSDELAY_INTGND_2MS				(DELAY_TIME_SLEEP/2)				//2ms intgnd, DELAY_TIME_SLEEP/2
#else
	#define PSDELAY_INTGND_2MS				1
#endif

#if TOUCH_TIMER_CLOCK_SET==0x08
	#define TTWAKE_TIMER_CNT  ((TT_FLOSC_SOURCE*WAKE_TIMER)/(128000ul))
#elif TOUCH_TIMER_CLOCK_SET==0x09
	#define TTWAKE_TIMER_CNT  ((TT_FLOSC_SOURCE*WAKE_TIMER)/(64000ul))
#elif TOUCH_TIMER_CLOCK_SET==0x0A
	#define TTWAKE_TIMER_CNT  ((TT_FLOSC_SOURCE*WAKE_TIMER)/(32000ul))
#elif TOUCH_TIMER_CLOCK_SET==0x0B
	#define TTWAKE_TIMER_CNT  ((TT_FLOSC_SOURCE*WAKE_TIMER)/(16000ul))
#elif TOUCH_TIMER_CLOCK_SET==0x0C
	#define TTWAKE_TIMER_CNT  ((TT_FLOSC_SOURCE*WAKE_TIMER)/(8000ul))
#elif TOUCH_TIMER_CLOCK_SET==0x0D
	#define TTWAKE_TIMER_CNT  ((TT_FLOSC_SOURCE*WAKE_TIMER)/(4000ul))
#elif TOUCH_TIMER_CLOCK_SET==0x0E
	#define TTWAKE_TIMER_CNT  ((TT_FLOSC_SOURCE*WAKE_TIMER)/(2000ul))
#else
	#define TTWAKE_TIMER_CNT  ((TT_FLOSC_SOURCE*WAKE_TIMER)/1000ul)
#endif

#if 		TTWAKE_TIMER_CNT>(255*(PSTK_EN_NUM+FRQ_NUM-1))
#define POWERSAVE_SCAN_INTGND  256
#elif 		TTWAKE_TIMER_CNT>(3*(PSTK_EN_NUM+FRQ_NUM-1))
#define POWERSAVE_SCAN_INTGND  (TTWAKE_TIMER_CNT/(PSTK_EN_NUM+FRQ_NUM-1))
#else
#define POWERSAVE_SCAN_INTGND		3
#endif
#define LPSM_SCAN_OFF			0X1F

#if WAKE_TIMER>200
#define BASE_CNT_SLEEP				2
#elif	WAKE_TIMER<27
#define BASE_CNT_SLEEP				15
#else
#define BASE_CNT_SLEEP				(400/WAKE_TIMER)
#endif
#define BASE_CNT_WAKE					5
#endif	//#ifndef _SYSMODE_H_
