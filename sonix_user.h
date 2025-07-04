//--------------------------------------------------------------------------
//Filename		: sonix_user.h
//Function		: 
//Description	: 
//--------------------------------------------------------------------------
#ifndef		_SONIX_USER_H_
#define		_SONIX_USER_H_

/*_____ I N C L U D E S ____________________________________________________*/


/*_____ D E F I N I T I O N S ______________________________________________*/
enum 
{
	eOFF = 0,
	eON  = 1,

	eZERO = 0,
	eNONE = 0,
	eNULL = 0,
	
	eFALSE = 0,
	eTRUE  = 1,

	eLOW  = 0,
	eHIGH = 1,

	eCLEAR = 0,

	eRESET = 0,
	eSET   = 1,	
	
	eACK  =0,
	eNACK =1,
};



typedef union 
{
	uint16_t uniWord;
	uint8_t uniByte[2];
}TwoByte;

typedef union 
{	
	uint32_t uniDWord;
	uint16_t uniWord[2];
	uint8_t  uniByte[4];
}FourByte;


#define	BIT_0		(0x01U<<0)
#define	BIT_1		(0x01U<<1)
#define	BIT_2		(0x01U<<2)
#define	BIT_3		(0x01U<<3)
#define	BIT_4		(0x01U<<4)
#define	BIT_5		(0x01U<<5)
#define	BIT_6		(0x01U<<6)
#define	BIT_7		(0x01U<<7)

#define B00000000 0x00
#define B00000001 0x01
#define B00000010 0x02
#define B00000011 0x03
#define B00000100 0x04
#define B00000101 0x05
#define B00000110 0x06
#define B00000111 0x07
#define B00001000 0x08
#define B00001001 0x09
#define B00001010 0x0A
#define B00001011 0x0B
#define B00001100 0x0C
#define B00001101 0x0D
#define B00001110 0x0E
#define B00001111 0x0F

#define B00010000 0x10
#define B00010001 0x11
#define B00010010 0x12
#define B00010011 0x13
#define B00010100 0x14
#define B00010101 0x15
#define B00010110 0x16
#define B00010111 0x17
#define B00011000 0x18
#define B00011001 0x19
#define B00011010 0x1A
#define B00011011 0x1B
#define B00011100 0x1C
#define B00011101 0x1D
#define B00011110 0x1E
#define B00011111 0x1F

#define B00100000 0x20
#define B00100001 0x21
#define B00100010 0x22
#define B00100011 0x23
#define B00100100 0x24
#define B00100101 0x25
#define B00100110 0x26
#define B00100111 0x27
#define B00101000 0x28
#define B00101001 0x29
#define B00101010 0x2A
#define B00101011 0x2B
#define B00101100 0x2C
#define B00101101 0x2D
#define B00101110 0x2E
#define B00101111 0x2F

#define B00110000 0x30
#define B00110001 0x31
#define B00110010 0x32
#define B00110011 0x33
#define B00110100 0x34
#define B00110101 0x35
#define B00110110 0x36
#define B00110111 0x37
#define B00111000 0x38
#define B00111001 0x39
#define B00111010 0x3A
#define B00111011 0x3B
#define B00111100 0x3C
#define B00111101 0x3D
#define B00111110 0x3E
#define B00111111 0x3F

#define B01000000 0x40
#define B01000001 0x41
#define B01000010 0x42
#define B01000011 0x43
#define B01000100 0x44
#define B01000101 0x45
#define B01000110 0x46
#define B01000111 0x47
#define B01001000 0x48
#define B01001001 0x49
#define B01001010 0x4A
#define B01001011 0x4B
#define B01001100 0x4C
#define B01001101 0x4D
#define B01001110 0x4E
#define B01001111 0x4F

#define B01010000 0x50
#define B01010001 0x51
#define B01010010 0x52
#define B01010011 0x53
#define B01010100 0x54
#define B01010101 0x55
#define B01010110 0x56
#define B01010111 0x57
#define B01011000 0x58
#define B01011001 0x59
#define B01011010 0x5A
#define B01011011 0x5B
#define B01011100 0x5C
#define B01011101 0x5D
#define B01011110 0x5E
#define B01011111 0x5F

#define B01100000 0x60
#define B01100001 0x61
#define B01100010 0x62
#define B01100011 0x63
#define B01100100 0x64
#define B01100101 0x65
#define B01100110 0x66
#define B01100111 0x67
#define B01101000 0x68
#define B01101001 0x69
#define B01101010 0x6A
#define B01101011 0x6B
#define B01101100 0x6C
#define B01101101 0x6D
#define B01101110 0x6E
#define B01101111 0x6F

#define B01110000 0x70
#define B01110001 0x71
#define B01110010 0x72
#define B01110011 0x73
#define B01110100 0x74
#define B01110101 0x75
#define B01110110 0x76
#define B01110111 0x77
#define B01111000 0x78
#define B01111001 0x79
#define B01111010 0x7A
#define B01111011 0x7B
#define B01111100 0x7C
#define B01111101 0x7D
#define B01111110 0x7E
#define B01111111 0x7F

#define B10000000 0x80
#define B10000001 0x81
#define B10000010 0x82
#define B10000011 0x83
#define B10000100 0x84
#define B10000101 0x85
#define B10000110 0x86
#define B10000111 0x87
#define B10001000 0x88
#define B10001001 0x89
#define B10001010 0x8A
#define B10001011 0x8B
#define B10001100 0x8C
#define B10001101 0x8D
#define B10001110 0x8E
#define B10001111 0x8F

#define B10010000 0x90
#define B10010001 0x91
#define B10010010 0x92
#define B10010011 0x93
#define B10010100 0x94
#define B10010101 0x95
#define B10010110 0x96
#define B10010111 0x97
#define B10011000 0x98
#define B10011001 0x99
#define B10011010 0x9A
#define B10011011 0x9B
#define B10011100 0x9C
#define B10011101 0x9D
#define B10011110 0x9E
#define B10011111 0x9F

#define B10100000 0xA0
#define B10100001 0xA1
#define B10100010 0xA2
#define B10100011 0xA3
#define B10100100 0xA4
#define B10100101 0xA5
#define B10100110 0xA6
#define B10100111 0xA7
#define B10101000 0xA8
#define B10101001 0xA9
#define B10101010 0xAA
#define B10101011 0xAB
#define B10101100 0xAC
#define B10101101 0xAD
#define B10101110 0xAE
#define B10101111 0xAF

#define B10110000 0xB0
#define B10110001 0xB1
#define B10110010 0xB2
#define B10110011 0xB3
#define B10110100 0xB4
#define B10110101 0xB5
#define B10110110 0xB6
#define B10110111 0xB7
#define B10111000 0xB8
#define B10111001 0xB9
#define B10111010 0xBA
#define B10111011 0xBB
#define B10111100 0xBC
#define B10111101 0xBD
#define B10111110 0xBE
#define B10111111 0xBF

#define B11000000 0xC0
#define B11000001 0xC1
#define B11000010 0xC2
#define B11000011 0xC3
#define B11000100 0xC4
#define B11000101 0xC5
#define B11000110 0xC6
#define B11000111 0xC7
#define B11001000 0xC8
#define B11001001 0xC9
#define B11001010 0xCA
#define B11001011 0xCB
#define B11001100 0xCC
#define B11001101 0xCD
#define B11001110 0xCE
#define B11001111 0xCF

#define B11010000 0xD0
#define B11010001 0xD1
#define B11010010 0xD2
#define B11010011 0xD3
#define B11010100 0xD4
#define B11010101 0xD5
#define B11010110 0xD6
#define B11010111 0xD7
#define B11011000 0xD8
#define B11011001 0xD9
#define B11011010 0xDA
#define B11011011 0xDB
#define B11011100 0xDC
#define B11011101 0xDD
#define B11011110 0xDE
#define B11011111 0xDF

#define B11100000 0xE0
#define B11100001 0xE1
#define B11100010 0xE2
#define B11100011 0xE3
#define B11100100 0xE4
#define B11100101 0xE5
#define B11100110 0xE6
#define B11100111 0xE7
#define B11101000 0xE8
#define B11101001 0xE9
#define B11101010 0xEA
#define B11101011 0xEB
#define B11101100 0xEC
#define B11101101 0xED
#define B11101110 0xEE
#define B11101111 0xEF

#define B11110000 0xF0
#define B11110001 0xF1
#define B11110010 0xF2
#define B11110011 0xF3
#define B11110100 0xF4
#define B11110101 0xF5
#define B11110110 0xF6
#define B11110111 0xF7
#define B11111000 0xF8
#define B11111001 0xF9
#define B11111010 0xFA
#define B11111011 0xFB
#define B11111100 0xFC
#define B11111101 0xFD
#define B11111110 0xFE
#define B11111111 0xFF
/*_____ D E C L A R A T I O N S ____________________________________________*/
/*_____ M A C R O S ________________________________________________________*/

#define uchar	unsigned char 
#define uint	unsigned int	
#define ulong	unsigned long
	
#define u8	unsigned char 
#define u16	unsigned int
#define u32	unsigned long
	
#ifndef int8_t
#define int8_t  char
#endif  // int8_t

#ifndef int16_t
#define int16_t  int
#endif  // int16_t

#ifndef int32_t
#define int32_t  long
#endif  // int32_t

#ifndef xuint8_t
#define xuint8_t  xdata unsigned char 
#endif  // xuint8_t

#ifndef xuint16_t
#define xuint16_t  xdata unsigned int 
#endif  // xuint16_t

#ifndef xuint32_t
#define xuint32_t  xdata unsigned long 
#endif  // xuint32_t

#ifndef xint8_t
#define xint8_t  xdata  char 
#endif  // xint8_t

#ifndef xint16_t
#define xint16_t  xdata  int 
#endif  // xint16_t

#ifndef xint32_t
#define xint32_t  xdata  long 
#endif  // xint32_t

#ifndef bit_
#define bit_  bit 
#endif  // bit_


#endif	/*_SONIX_USER_H_*/
