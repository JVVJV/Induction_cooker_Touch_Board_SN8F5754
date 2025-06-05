/*--------------------------------------------------------------------------
SN8F5754.H

Header file for SNOiX SN8F5754 microcontroller.
Copyright (c) 2020 SONiX Technology Co., Ltd.

Version 1.0    2020-08-12
--------------------------------------------------------------------------*/

#ifndef __SN8F5754_H__
#define __SN8F5754_H__

#define DEFINE_SFR(Register ,Address) \
				sfr Register = Address;

#ifdef __C51__  //** Compiler: C51
		#ifdef __XRAM_SFR_H__
			#define DEFINE_XSFR(Register ,Address) \
							volatile unsigned char xdata Register	_at_	Address;
		#else
			#define DEFINE_XSFR(Register ,Address) \
							extern volatile unsigned char xdata Register;
		#endif //for C51 __XRAM_SFR_H__ 
#else    //** Compiler: A51
		#ifdef __XRAM_SFR_H__
			#define DEFINE_XSFR(Register ,Address) \
							Register xdata Address; \
							PUBLIC Register
		#else
			#define DEFINE_XSFR(Register ,Address) \
							EXTRN xdata (Register)
		#endif //for C51 __XRAM_SFR_H__
#endif 

// --------------------------- //
//    8051 SFR Registers  		 //
// --------------------------- //
	DEFINE_SFR(P0			,0x80)
	DEFINE_SFR(SP 		,0x81)
	DEFINE_SFR(DPL 		,0x82)
	DEFINE_SFR(DPH 		,0x83)
	DEFINE_SFR(DPL1 	,0x84)
	DEFINE_SFR(DPH1 	,0x85)
	DEFINE_SFR(WDTR 	,0x86)
	DEFINE_SFR(PCON 	,0x87)
	DEFINE_SFR(TCON		,0x88)
	DEFINE_SFR(TMOD		,0x89)
	DEFINE_SFR(TL0 		,0x8A)
	DEFINE_SFR(TL1 		,0x8B)
	DEFINE_SFR(TH0		,0x8C)
	DEFINE_SFR(TH1 		,0x8D)
	DEFINE_SFR(TCON0	,0x8E)
	DEFINE_SFR(PEDGE	,0x8F)

	DEFINE_SFR(P1			,0x90)
	DEFINE_SFR(DPS		,0x92)
	DEFINE_SFR(DPC 		,0x93)
	DEFINE_SFR(SMODMX	,0x94)
	DEFINE_SFR(SMODCAL,0x95)
	DEFINE_SFR(S0CON2 ,0x96)
	DEFINE_SFR(S0CON 	,0x97)
	DEFINE_SFR(IEN3 	,0x98)
	DEFINE_SFR(S0BUF	,0x99)
	DEFINE_SFR(S0RELL	,0x9A)
	DEFINE_SFR(S0RELH	,0x9B)
	DEFINE_SFR(S1CON	,0x9C)
	DEFINE_SFR(S1BUF	,0x9D)
	DEFINE_SFR(S1RELL ,0x9E)
	DEFINE_SFR(S1RELH	,0x9F)

	DEFINE_SFR(P2			,0xA0)
	DEFINE_SFR(IRCON	,0xA5)
	DEFINE_SFR(IRCON2 ,0xA6)
	DEFINE_SFR(IRCON3	,0xA7)
	DEFINE_SFR(IEN0 	,0xA8)
	DEFINE_SFR(IP0		,0xA9)
	DEFINE_SFR(FRQL		,0xAA)
	DEFINE_SFR(FRQH		,0xAB)
	DEFINE_SFR(FRQCMD	,0xAC)
	DEFINE_SFR(LFRQL	,0xAD)
	DEFINE_SFR(LFRQH 	,0xAE)
	DEFINE_SFR(CLKCAL	,0xAF)

	DEFINE_SFR(P3			,0xB0)
	DEFINE_SFR(T3M 		,0xB1)
	DEFINE_SFR(T3CL 	,0xB2)
	DEFINE_SFR(T3CH 	,0xB3)
	DEFINE_SFR(T3RL 	,0xB4)
	DEFINE_SFR(T3RH 	,0xB5)
	DEFINE_SFR(IEN1		,0xB8)
	DEFINE_SFR(IP1		,0xB9)
	DEFINE_SFR(PECMD 	,0xBA)
	DEFINE_SFR(PEROML ,0xBB)
	DEFINE_SFR(PEROMH ,0xBC)
	DEFINE_SFR(PERAM 	,0xBD)
	DEFINE_SFR(DEGCMD	,0xBF)

	DEFINE_SFR(CSCON 	,0xC3)
	DEFINE_SFR(CSCON4 ,0xC4)
	DEFINE_SFR(CSCAVGL,0xC5)
	DEFINE_SFR(CSCAVGH,0xC6)
	DEFINE_SFR(IEN2		,0xC8)
	DEFINE_SFR(PW1M		,0xC9)
	DEFINE_SFR(PW1CH 	,0xCA)
	DEFINE_SFR(PW2M 	,0xCB)
	DEFINE_SFR(PW2CH 	,0xCC)

	DEFINE_SFR(PSW		,0xD0)
	DEFINE_SFR(ADT 		,0xD1)
	DEFINE_SFR(ADM 		,0xD2)
	DEFINE_SFR(ADB 		,0xD3)
	DEFINE_SFR(ADR	 	,0xD4)
	DEFINE_SFR(VREFH 	,0xD5)
	DEFINE_SFR(BIASCTL,0xD6)
	DEFINE_SFR(COMCTL	,0xD7)
	DEFINE_SFR(BZM		,0xD9)
	DEFINE_SFR(I2CDAT	,0xDA)
	DEFINE_SFR(I2CADR	,0xDB)
	DEFINE_SFR(I2CCON	,0xDC)
	DEFINE_SFR(I2CSTA	,0xDD)
	DEFINE_SFR(SMBSEL	,0xDE)
	DEFINE_SFR(SMBDST	,0xDF)

	DEFINE_SFR(ACC		,0xE0)
	DEFINE_SFR(B			,0xF0)
	DEFINE_SFR(CRCM 	,0xF1)
	DEFINE_SFR(CRCDATL,0xF2)
	DEFINE_SFR(CRCDATH,0xF3)
	DEFINE_SFR(SYSMOD ,0xF4)
	DEFINE_SFR(SRST 	,0xF7)
	DEFINE_SFR(P0M		,0xF9)
	DEFINE_SFR(P1M 		,0xFA)
	DEFINE_SFR(P2M 		,0xFB)
	DEFINE_SFR(P3M 		,0xFC)
	DEFINE_SFR(PFLAG	,0xFF)

// --------------------------- //
//    8051 16bit SFR 			 		 //
// --------------------------- //
	sfr16	S0REL		= 0x9A;
	sfr16	S1REL		= 0x9E;
	sfr16	FRQ			= 0xAA;
	sfr16	LFRQ		= 0xAD;
	sfr16	T3C			= 0xB2;
	sfr16	T3R			= 0xB4;
	sfr16	PEROM		= 0xBB;
	sfr16	CSCAVG	= 0xC5;
	sfr16	CRCDAT	= 0xF2;

// --------------------------- //
//    8051 BIT SFR 	  		 		 //
// --------------------------- //
	/*	P0	*/
	sbit	P07	= P0^7;
	sbit	P06	= P0^6;
	sbit	P05	= P0^5;
	sbit	P04	= P0^4;
	sbit	P03	= P0^3;
	sbit	P02	= P0^2;
	sbit	P01	= P0^1;
	sbit	P00	= P0^0;
	/*	P1	*/
	sbit	P17	= P1^7;
	sbit	P16	= P1^6;
	sbit	P15	= P1^5;
	sbit	P14	= P1^4;
	sbit	P13	= P1^3;
	sbit	P12	= P1^2;
	sbit	P11	= P1^1;
	sbit	P10	= P1^0;
	/*	P2	*/
	sbit	P24	= P2^4;
	sbit	P23	= P2^3;
	sbit	P22	= P2^2;
	sbit	P21	= P2^1;
	sbit	P20	= P2^0;
	/*	P3	*/
	sbit	P33	= P3^3;
	sbit	P32	= P3^2;
	sbit	P31	= P3^1;
	sbit	P30	= P3^0;

	/*	TCON	*/
	sbit	TF1	= TCON^7;
	sbit	TR1	= TCON^6;
	sbit	TF0	= TCON^5;
	sbit	TR0	= TCON^4;
	sbit	IE1	= TCON^3;
	sbit	IE0	= TCON^1;

	/*	IEN0	*/
	sbit	EAL	= IEN0^7;
	sbit	EX2	= IEN0^4;
	sbit	ET1	= IEN0^3;
	sbit	EX1	= IEN0^2;
	sbit	ET0	= IEN0^1;
	sbit	EX0	= IEN0^0;
	/*	IEN1	*/
	sbit	EU1RX	= IEN1^5;
	sbit	EU1TX	= IEN1^4;
	sbit	EU0RX	= IEN1^3;
	sbit	EU0TX	= IEN1^2;
	sbit	EI2C	= IEN1^0;
	/*	IEN2	*/
	sbit	ET3		= IEN2^5;
	sbit	EPW2	= IEN2^3;
	sbit	EPW1	= IEN2^2;
	sbit	ECS		= IEN2^1;
	sbit	EADC	= IEN2^0;
	/*	IEN3	*/
	sbit	ETT		= IEN3^1;
	sbit	ELPSM	= IEN3^0;

	/*	PSW	*/
	sbit  CY	= PSW^7;
	sbit  AC	= PSW^6;
	sbit  F0	= PSW^5;
	sbit  RS1	= PSW^4;
	sbit  RS0	= PSW^3;
	sbit  OV	= PSW^2;
	sbit  F1	= PSW^1;
	sbit  P		= PSW^0;

// ------------------------------- //
//    8051 XRAM SFR Registers  		 //
// ------------------------------- //
	DEFINE_XSFR(P0UR		,0xF000)
	DEFINE_XSFR(P1UR		,0xF001)
	DEFINE_XSFR(P2UR		,0xF002)
	DEFINE_XSFR(P3UR		,0xF003)
	DEFINE_XSFR(P1W 		,0xF011)

	DEFINE_XSFR(P0CON 	,0xF018)
	DEFINE_XSFR(P1CON 	,0xF019)
	DEFINE_XSFR(P2CON 	,0xF01A)
	DEFINE_XSFR(P3CON 	,0xF01B)

	DEFINE_XSFR(P0OC		,0xF020)
	DEFINE_XSFR(P1OC 		,0xF021)
	DEFINE_XSFR(P2OC		,0xF022)
	DEFINE_XSFR(P3OC 		,0xF023)

	DEFINE_XSFR(CSCON1 	,0xF038)
	DEFINE_XSFR(CSCON2 	,0xF039)
	DEFINE_XSFR(CSCON3 	,0xF03A)

	DEFINE_XSFR(CCAL 		,0xF03B)
	DEFINE_XSFR(CSCL 		,0xF03C)
	DEFINE_XSFR(CSCH 		,0xF03D)
	DEFINE_XSFR(TSWY 		,0xF03E)
	DEFINE_XSFR(TSWD 		,0xF03F)
	DEFINE_XSFR(LPSMCON ,0xF040)
	DEFINE_XSFR(MAXCS0L ,0xF041)
	DEFINE_XSFR(MAXCS0H ,0xF042)
	DEFINE_XSFR(MINCS0L ,0xF043)
	DEFINE_XSFR(MINCS0H ,0xF044)

	DEFINE_XSFR(TTCON 	,0xF045)
	DEFINE_XSFR(TTL 		,0xF046)
	DEFINE_XSFR(TTH 		,0xF047)

	DEFINE_XSFR(PW1YL 	,0xF070)
	DEFINE_XSFR(PW1YH 	,0xF071)
	DEFINE_XSFR(PW2YL 	,0xF072)
	DEFINE_XSFR(PW2YH 	,0xF073)

	DEFINE_XSFR(PW10DL 	,0xF078)
	DEFINE_XSFR(PW10DH 	,0xF079)
	DEFINE_XSFR(PW11DL 	,0xF07A)
	DEFINE_XSFR(PW11DH 	,0xF07B)
	DEFINE_XSFR(PW12DL 	,0xF07C)
	DEFINE_XSFR(PW12DH 	,0xF07D)
	DEFINE_XSFR(PW13DL 	,0xF07E)
	DEFINE_XSFR(PW13DH 	,0xF07F)

	DEFINE_XSFR(PW20DL 	,0xF088)
	DEFINE_XSFR(PW20DH 	,0xF089)
	DEFINE_XSFR(PW21DL 	,0xF08A)
	DEFINE_XSFR(PW21DH 	,0xF08B)
	DEFINE_XSFR(PW22DL 	,0xF08C)
	DEFINE_XSFR(PW22DH 	,0xF08D)
	DEFINE_XSFR(PW23DL 	,0xF08E)
	DEFINE_XSFR(PW23DH 	,0xF08F)

	DEFINE_XSFR(CPSTCH0 ,0xF0D0)
	DEFINE_XSFR(CPSTCH1 ,0xF0D1)
	DEFINE_XSFR(CPSTCH2 ,0xF0D2)
	DEFINE_XSFR(CSC1AVGL,0xF0D4)
	DEFINE_XSFR(CSC1AVGH,0xF0D5)
	DEFINE_XSFR(CSC2AVGL,0xF0D6)
	DEFINE_XSFR(CSC2AVGH,0xF0D7)
	DEFINE_XSFR(CSC3AVGL,0xF0D8)
	DEFINE_XSFR(CSC3AVGH,0xF0D9)
	DEFINE_XSFR(CSC4AVGL,0xF0DA)
	DEFINE_XSFR(CSC4AVGH,0xF0DB)
	DEFINE_XSFR(CSC5AVGL,0xF0DC)
	DEFINE_XSFR(CSC5AVGH,0xF0DD)

	DEFINE_XSFR(LPSMCH0	,0xF0DE)
	DEFINE_XSFR(LPSMCH1	,0xF0DF)
	DEFINE_XSFR(LPSMCH2 ,0xF0E0)
	DEFINE_XSFR(LPSMCH3 ,0xF0E1)
	DEFINE_XSFR(LPSMCH4 ,0xF0E2)
	DEFINE_XSFR(LPSMCH5 ,0xF0E3)

/*      Interrupt Vector      */
#define ISRInt0    0     /* Vector 0x03 */
#define ISRTimer0  1     /* Vector 0x0B */
#define ISRInt1    2     /* Vector 0x13 */
#define ISRTimer1  3     /* Vector 0x1B */
#define ISRInt2    4     /* Vector 0x23 */
#define ISRTimer3  6     /* Vector 0x33 */
#define ISRI2c     8     /* Vector 0x43 */
#define ISRUart0rx 10    /* Vector 0x53 */
#define ISRUart0tx 11    /* Vector 0x5B */
#define ISRUart1rx 12    /* Vector 0x63 */
#define ISRUart1tx 13    /* Vector 0x6B */
#define ISRTimerT  14    /* Vector 0x73 */
#define ISRPwm1    16    /* Vector 0x83 */
#define ISRPwm2    17    /* Vector 0x8B */
#define ISRAdc     21    /* Vector 0xAB */
#define ISRCS 	   22    /* Vector 0xB3 */
#define ISRLPSM    29    /* Vector 0xEB */

/*      C51 Macros      */
#ifdef __C51__
	#include <intrins.h>
	#define IDLE() {PCON |= 0x01;}
	#define STOP() {PCON |= 0x02;}
	#define PISP(ROM_ADDRESS, RAM_ADDRESS) {PERAM = (RAM_ADDRESS); PEROM = ((ROM_ADDRESS) & 0xFFE0); PECMD = 0x5A; _nop_(); _nop_();}
	#define BISP(ROM_ADDRESS, RAM_ADDRESS) {PERAM = (RAM_ADDRESS); PEROM = ((ROM_ADDRESS) & 0xFFFF); PECMD = 0x1E; _nop_(); _nop_();}

#else // for A51
	WRXSFR	MACRO	XADDR, XDA
					MOV	  DPTR, #XADDR
					MOV	  A, XDA
					MOVX  @DPTR, A
					ENDM

	RDXSFR	MACRO	XDA, XADDR
					MOV	  DPTR, #XADDR
					MOVX  A, @DPTR
					MOV   XDA, A
					ENDM
#endif  

#ifndef uint8_t
#define uint8_t unsigned char
#endif  // uint8_t

#ifndef uint16_t
#define uint16_t unsigned int
#endif  // uint16_t

#ifndef uint32_t
#define uint32_t unsigned long
#endif  // uint32_t

#endif  // __SN8F5754_H__
