//##############################################################################
//    filename:        GLCDnokia.h
//##############################################################################
//    header file GLCD library for Nokia 5110, 3110... displays
//##############################################################################
//
//      Author:             V.SchK
//      Company:            THU
//
//      Revision:           2.0
//      Date:               July 2017
//      Assembled using     XC8 2.00+
//
//      todo    - add comments ;-)
//              -
//##############################################################################
//
//      FUNCTIONS:
//
//- void GLCD_Init(void)
//      must be called before using other functions !!!
//
//- void GLCD_Clear(void)
//- void GLCD_ClearRow(unsigned char row)
//- void GLCD_Clear2Row(unsigned char row)
//      clear whole display or only a row (height one or two)
//
//- void GLCD_Write(unsigned char data, unsigned char dc);
//      write one byte (data or command)
//
//- void GLCD_WriteChar(char c);
//      write one char from charSet8x5[] (6 lines) at current cursor position
//
//- void GLCD_SetCursor(unsigned char row, unsigned char column);
//
//- char GLCD_CharOut(unsigned char row, unsigned char column, char c);
//      write one char from charSet8x5[] (6 lines) at given cursor position
//
//- void GLCD_TextOut(unsigned char row, unsigned char col, unsigned char *text)
//      writes string of characters from charSet8x5[] (6 lines)
//      -> unsigned char string[] = {"Hello"};
//         GLCD_TextOut(0,0,string);
//         GLCD_TextOut(0,0,"Hello");
//
//- char GLCD_Write2Char(char c);
//- char GLCD_Char2Out(unsigned char row, unsigned char column, char c);
//- void GLCD_Text2Out(unsigned char row, unsigned char col, unsigned char *text)
//      functions that use double height characters (two lines) charSet16x7[]
//
//- void GLCD_Value2Out(unsigned char row, unsigned char col, short value)
//      writes a (signed) number at the give coordinates
//
//- void GLCD_Value2Out_00(unsigned char row, unsigned char col, short value,
//                       unsigned char min_dig);
//      writes a number with leading zeros to get minimum specified digits
//      -> short number = 7;
//         GLCD_Value2Out_00(0,0,7,4); write "0007" at the top left of the display
//
//- void GLCDputrbm_XY(unsigned char rows, unsigned char columns,
//                     const char* bm, unsigned char row_top, unsigned char col_left);
//      show bitmap
//##############################################################################

#ifndef GLCDNOKIA_H
#define GLCDNOKIA_H

#include "glcdNokia_config.h"

extern const char charSet8x5[];
extern const char charSet16x7[];

#define GLCD_MAXCOL 83
#define GLCD_MAXROW  5

#define CMD         0
#define DTA         1

// intruction set
#define DSPL_NOP    0x00
#define DSPL_FKT    0x20
// basic instruction set (H = 0)
#define DSPL_CTRL   0x08
#define DSPL_Y      0x40
#define DSPL_X      0x80
// extended instruction set (H = 1)
#define DSPL_TEMP   0x04
#define DSPL_BIAS   0x10
#define DSPL_VOP    0x80

#define FKT_ON      0x00
#define FKT_PD      0x04
#define FKT_HORZ    0x00
#define FKT_VERT    0x02
#define FKT_BASC    0x00
#define FKT_EXT     0x01

#define CTRL_BLANK  0x00
#define CTRL_NORML  0x04
#define CTRL_ALLON  0x01
#define CTRL_IVM    0x05

#define GLCD_ERROR   0x00
#define GLCD_OK      0x01

extern void GLCD_Init(void);
extern void GLCD_ClearRow(unsigned char row);
extern void GLCD_Clear2Row(unsigned char row);
extern void GLCD_Clear(void);
extern void GLCD_Write(unsigned char data, unsigned char dc);
extern void GLCD_WriteChar(char c);

#define GLCD_SetCursor(row, column) GLCD_Write(DSPL_X | column, CMD); GLCD_Write(DSPL_Y | row, CMD);

extern char GLCD_CharOut(unsigned char row, unsigned char column, char c);
extern void GLCD_TextOut(unsigned char row, unsigned char col, char *text);

extern char GLCD_Char2Out(unsigned char row, unsigned char column, char c);
extern void GLCD_Text2Out(unsigned char row, unsigned char col, char *text);

extern void GLCD_Value2Out_00(unsigned char row, unsigned char col, short value, unsigned char min_dig);
#define GLCD_Value2Out(r,c,v) GLCD_Value2Out_00(r,c,v,1)


extern void GLCDputrbm_XY(unsigned char rows, unsigned char columns,
                const char* bm, unsigned char row_top, unsigned char col_left);

#endif	/* GLCDNOKIA_H */
