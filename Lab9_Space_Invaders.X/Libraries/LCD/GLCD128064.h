//##############################################################################
//	filename:		LCD128064.h
//
// 	Implements the BTHQ128064AVD-... Communication
//
//##############################################################################
//
//      Author:             VSK
//      Company:            HS Ulm
//
//      Revision:           x.x
//      Date:               Mai 2009
//      Assembled using     MPLAB 8.00 C18 3.14
//
//
//##############################################################################

#ifndef GLCD12864_H
#define	GLCD12864_H

#include "glcd12864_config.h"

extern rom const char charSet8x5[];

/** G L O B A L  P R O T O T Y P E S ******************************************/
void clrGLCD(void);
void delRowGLCD(unsigned char row);
void setCursorGLCD(unsigned char row,unsigned char column);
#define putcGLCD glcd_wrdata   //(char c);
void putcGLCDxy(unsigned char row,unsigned char column,char* c);
void putsGLCDxy(unsigned char row,unsigned char column,char* s);
void putrsGLCDxy(unsigned char row,unsigned char column,const rom char* s);
void putrbmGLCDxy(unsigned char pages,unsigned char columns,const rom char* bm,
                    unsigned char page_top,unsigned char column_left);

void glcd_command(char cmd);
void glcd_wrdata(char dat);
char glcd_rddata(void);
char glcd_busy(void);
void glcd_init(void);
void glcd_signalsTest(void);

///** Pin Defining **************************************************************/
// -> glcd12864_config.h

// display commands
// -1-
#define DISP_ON         0b10101111
#define DISP_OFF        0b10101110
// -2-
#define DISP_STLINE     0b01000000 |    // or 6-bit address
// -3-
#define DISP_PGADDR     0b10110000 |    // or 5-bit address
// -4-
#define DISP_CADDRHN    0b00010000 |    // or 4-bit address (high nibble)
#define DISP_CADDRLN    0b00000000 |    // or 4-bit address	(low nibble)
// -8-
#define DISP_ADCNORM    0b10100000
#define DISP_ADCREV     0b10100001
// -9-
#define DISP_NORMAL     0b10100110
#define DISP_REVERS     0b10100111
// -10-
#define DISP_ALL_ON     0b10100101
#define DISP_ALL_OFF    0b10100100
// -11-
#define DISP_BIAS_9     0b10100010
#define DISP_BIAS_7     0b10100011
// -12-
#define DISP_RdMdWr     0b11100000
// -13-
#define DISP_END        0b11101110
// -14-
#define DISP_RESET      0b11100010
// -15-
#define DISP_COMOUT_N   0b11000000
#define DISP_COMOUT_R   0b11001000
// -16-
#define DISP_PW_CTRL    0b00101000	|   // or 3-bit mode
#define PW_ALL_ON       0b111
#define PW_ALL_OFF      0b000
// -17-
#define DISP_V5_IRRS    0b00100000	|   // or 3-bit ratio
// -18-
#define DISP_EV         0b10000001
#define DISP_EV_LVL     0b11000000	|   // or 6-bit voltage level
// -19-
#define DISP_STIND_OFF  0b10101100
#define DISP_STIND_ON   0b10101101
#define DISP_STIND_MODE 0b11111100	|   // or 2-bit mode
#define STIND_OFF       0b00
#define STIND_1s        0b01
#define STIND_05s       0b10
#define STIND_ON        0b11
// -20-
// power saver
// -21-
#define DISP_NOP        0b11100011

union displaystatus //VSK remove this ???
{
   struct
   {
       unsigned char free   : 4;
       unsigned char RESET  : 1;
       unsigned char ON_OFF : 1;
       unsigned char ADC    : 1;
       unsigned char BUSY   : 1;
   };
   unsigned char ALL;
};
#endif //GLCD12864_H
