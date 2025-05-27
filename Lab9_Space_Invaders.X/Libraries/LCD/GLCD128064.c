//##############################################################################
//	filename:		LCD128064.c
//
// 	Implements the BTHQ128064AVD-... Communication
//
//##############################################################################
//
//  	Author:             VSK
//  	Company:            HS Ulm
//
//      Revision:           x.x
//      Date:               Mai 2009
//      Assembled using     MPLAB 8.00 C18 3.14
//
//
//##############################################################################


/** I N C L U D E S ***********************************************************/
#include <p18cxxx.h>
#include <delays.h>
#include "GLCD128064.h"
#include "bitValues.h"


#pragma udata access ACCESSRAM
/** P R I V A T E  V A R I A B L E S ******************************************/
near union displaystatus disp_status;
near union v8bit LCDdbits;
near union v16bit posCursor;
#define posxCursor  posCursor.LB
#define posyCursor  posCursor.HB


/** G L O B A L  P R O T O T Y P E S ****************************************/
// -> GLCD12864.h

/** P R I V A T E  P R O T O T Y P E S ****************************************/
//char byte_mirror(char mbyte);

/** F U N C T I O N S *********************************************************/

////////////////////////////////////////////////////////////////////////////////
//                           lcd_command()                                    //
////////////////////////////////////////////////////////////////////////////////
void glcd_init(void)
{
    nCS	= 1;
    nRES = 0;
    D_C = 0;
    nWR = 1;
    nRD= 1;
    LCD_PIN_INIT();

    mLCD_OUT();	// data signals direction

//--- Initialisation LCD-Controller ST7565
    nRES = 1;
    Delay10TCYx( 100);
    glcd_command(DISP_RESET);               // Reset
//    glcd_command(DISP_BIAS_9);              // LCD BIAS ????  SED1565
    glcd_command(DISP_BIAS_7);              // LCD BIAS ????  SED1565
    glcd_command(DISP_ADCREV);              // ADC=1
    glcd_command(DISP_COMOUT_N);            // Common Output Mode Select
    glcd_command(DISP_V5_IRRS 7);           // Resistor ratio
    glcd_command(DISP_EV);                  // electronic volume
    glcd_command(DISP_EV_LVL 32);           // electronic volume value
    glcd_command(DISP_NORMAL);              // Display normal
//    glcd_command(DISP_ON);
    glcd_command(DISP_ALL_OFF);             // all dots off (normal)
    glcd_command(DISP_PW_CTRL PW_ALL_ON);   // power circuits
    glcd_command(DISP_ON);
    glcd_command(DISP_STLINE 0x00);         // Display Line Start adress
    glcd_command(DISP_END);
    clrGLCD();
}

////////////////////////////////////////////////////////////////////////////////
//                           clrGLCD()                                        //
////////////////////////////////////////////////////////////////////////////////

void clrGLCD(void)
{
    unsigned char p, c;                 // page, column

    for (p = 0; p <= 7; p++) {
        glcd_command(DISP_PGADDR p);    //Page adress set
        glcd_command(DISP_CADDRHN 0);   // Column adress low
        glcd_command(DISP_CADDRLN 0);   // Column adress high

        for(c = 0; c <= 127; c++){      //Spalte
            glcd_wrdata(0x00);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
//                           delRow()  (Row == Page)                          //
////////////////////////////////////////////////////////////////////////////////
void delRow(unsigned char row)
{
    unsigned char c;

    glcd_command(DISP_PGADDR row);  //Page adress set
    glcd_command(DISP_CADDRHN 0);   // Column adress low
    glcd_command(DISP_CADDRLN 0);   // Column adress high

    for(c = 0; c <= 127; c++){      //Spalte
        glcd_wrdata(0x00);
    }
}

////////////////////////////////////////////////////////////////////////////////
//                           setCursorGLCD()                                  //
////////////////////////////////////////////////////////////////////////////////
void setCursorGLCD(unsigned char row,unsigned char column)
{
    posxCursor = column;
    posyCursor = row;
}

////////////////////////////////////////////////////////////////////////////////
//                           putCharGLCDxy()                                  //
////////////////////////////////////////////////////////////////////////////////
void putcGLCDxy(unsigned char row,unsigned char column,char* c)
{ 
    unsigned char i;
    const rom char* ptrCharBase;
 
    posxCursor = column;
    posyCursor = row;
    glcd_command(DISP_PGADDR row);              //Page adress set
    glcd_command(DISP_CADDRHN(column / 16));    // Column adress low
    glcd_command(DISP_CADDRLN(column & 0x0F));  // Column adress high

    ptrCharBase = charSet8x5;
    ptrCharBase += (unsigned short) 5 * (*c);

    for (i = 0; i < 5; i++)
        glcd_wrdata(*ptrCharBase++);
    glcd_wrdata(0x00);
}

////////////////////////////////////////////////////////////////////////////////
//                           putsGLCDxy()                                     //
////////////////////////////////////////////////////////////////////////////////
void putsGLCDxy(unsigned char row,unsigned char column,char* s)
{
    unsigned char i;
    const rom char* ptrCharBase;

    posxCursor = column;
    posyCursor = row;
    glcd_command(DISP_PGADDR row);              //Page adress set
    glcd_command(DISP_CADDRHN(column / 16));    // Column adress low
    glcd_command(DISP_CADDRLN(column & 0x0F));  // Column adress high

    do{
        ptrCharBase = charSet8x5;
        ptrCharBase += (unsigned short) 5 * (*s);

        for (i = 0; i < 5; i++)
            glcd_wrdata(*ptrCharBase++);
        glcd_wrdata(0x00);
        s++;
    }while(*s != 0);
}

////////////////////////////////////////////////////////////////////////////////
//                           putrsGLCDxy()                                    //
////////////////////////////////////////////////////////////////////////////////
void putrsGLCDxy(unsigned char row,unsigned char column,const rom char* s)
{
    unsigned char i, s_val;
    const rom char* ptrCharBase;

    posxCursor = column;
    posyCursor = row;
    glcd_command(DISP_PGADDR row);              //Page adress set
    glcd_command(DISP_CADDRHN(column / 16));    // Column adress low
    glcd_command(DISP_CADDRLN(column & 0x0F));  // Column adress high

    do{
        s_val = *s;
        if (s_val == 'ä') s_val = 0x01;         // character set extentions
        else if (s_val == 'ö') s_val = 0x02;
        else if (s_val == 'ü') s_val = 0x03;
        else if (s_val == 'Ä') s_val = 0x04;
        else if (s_val == 'Ö') s_val = 0x05;
        else if (s_val == 'Ü') s_val = 0x06;
        else if (s_val == '°') s_val = 0x07;

        if (s_val > 0x7F) s_val = 0x00;

        ptrCharBase = charSet8x5;
        ptrCharBase += (unsigned short) 5 * s_val;

        for (i = 0; i < 5; i++)
            glcd_wrdata(*ptrCharBase++);
        glcd_wrdata(0x00);
        s++;
        s_val = *s;
    }while(s_val != 0);
}

////////////////////////////////////////////////////////////////////////////////
//                           putrsGLCDxy()                                    //
////////////////////////////////////////////////////////////////////////////////
void putrbmGLCDxy(unsigned char pages,unsigned char columns,const rom char* bm,
                    unsigned char page_top,unsigned char column_left)
{
    unsigned char p,c;
    const rom char* base;
    for(p = 0; p < pages; p++){
        glcd_command(DISP_PGADDR page_top + p);
        glcd_command(DISP_CADDRHN(column_left / 16));
        glcd_command(DISP_CADDRLN(column_left & 0x0F));
        for (c = 0; c < columns; c++){
            glcd_wrdata(*bm++);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
//                           lcd_command()                                    //
////////////////////////////////////////////////////////////////////////////////
void glcd_command(char cmd)        // intel 8080
{
    while(glcd_busy());
#ifdef DISP_DATA
    DISP_DATA = cmd;
#else
    LCDdbits.all = cmd;
    DATA_OUT_0 = LCDdbits.bit0;
    DATA_OUT_1 = LCDdbits.bit1;
    DATA_OUT_2 = LCDdbits.bit2;
    DATA_OUT_3 = LCDdbits.bit3;
    DATA_OUT_4 = LCDdbits.bit4;
    DATA_OUT_5 = LCDdbits.bit5;
    DATA_OUT_6 = LCDdbits.bit6;
    DATA_OUT_7 = LCDdbits.bit7;
#endif
    D_C = 0;
    nWR = 0;
    nCS = 0;
    Nop();
    Nop();
    nCS = 1;
    nWR = 1;
}


////////////////////////////////////////////////////////////////////////////////
//                             lcd_wrdata()                                   //
////////////////////////////////////////////////////////////////////////////////
void glcd_wrdata(char dat)
{
  	while (glcd_busy());
#ifdef DISP_DATA
    DISP_DATA = dat;
#else
    LCDdbits.all = dat;
    DATA_OUT_0 = LCDdbits.bit0;
    DATA_OUT_1 = LCDdbits.bit1;
    DATA_OUT_2 = LCDdbits.bit2;
    DATA_OUT_3 = LCDdbits.bit3;
    DATA_OUT_4 = LCDdbits.bit4;
    DATA_OUT_5 = LCDdbits.bit5;
    DATA_OUT_6 = LCDdbits.bit6;
    DATA_OUT_7 = LCDdbits.bit7;
#endif
    D_C = 1;
    nWR = 0;
    nCS = 0;
    Nop();
    Nop();
    nCS = 1;
    nWR = 1;
}

////////////////////////////////////////////////////////////////////////////////
//                             lcd_rddata()                                   //
////////////////////////////////////////////////////////////////////////////////
char glcd_rddata(void)
{
//	char data;
    while (glcd_busy());
    mLCD_IN();
    D_C = 1;        // Register Select
    nRD = 0;        // READ
    nCS = 0;        // Chip Select
    Nop();
    Nop();
#ifdef DISP_DATA
    data = DISP_DATA;
#else
    LCDdbits.bit0 = DATA_IN_0;
    LCDdbits.bit1 = DATA_IN_1;
    LCDdbits.bit2 = DATA_IN_2;
    LCDdbits.bit3 = DATA_IN_3;
    LCDdbits.bit4 = DATA_IN_4;
    LCDdbits.bit5 = DATA_IN_5;
    LCDdbits.bit6 = DATA_IN_6;
    LCDdbits.bit7 = DATA_IN_7;
#endif
    nCS = 1;
    nRD = 1;
    mLCD_OUT();
    return LCDdbits.all;
}

////////////////////////////////////////////////////////////////////////////////
//                             lcd_busy()                                     //
////////////////////////////////////////////////////////////////////////////////
char glcd_busy(void)
{
    mLCD_IN();
    nRD = 0;
    D_C = 0;
    nCS = 0;
    Nop();
    Nop();
#ifdef DISP_DATA
    disp_status.ALL = DISP_DATA;
#else
    //    DATA_IN_0
    //    DATA_IN_1
    //    DATA_IN_2
    //    DATA_IN_3
    disp_status.RESET = DATA_IN_4;
    disp_status.ON_OFF = DATA_IN_5;
    disp_status.ADC = DATA_IN_6;
    disp_status.BUSY = DATA_IN_7;
#endif
    nRD = 1;
    nCS = 1;
    mLCD_OUT();
    Nop();
    Nop();
    if (disp_status.BUSY)
        return 1;
    else
        return 0;
}

////////////////////////////////////////////////////////////////////////////////
//                             glcd_test()                                     //
////////////////////////////////////////////////////////////////////////////////
void glcd_signalsTest(void)
{
    LCD_PIN_INIT();
    mLCD_OUT();
    nCS = 1;
    nRES = 1;
    D_C = 1;
    nWR = 1;
    nRD = 1;
    DATA_OUT_0 = 1;
    DATA_OUT_1 = 1;
    DATA_OUT_2 = 1;
    DATA_OUT_3 = 1;
    DATA_OUT_4 = 1;
    DATA_OUT_5 = 1;
    DATA_OUT_6 = 1;
    DATA_OUT_7 = 1;

    nCS = 0;
    nRES = 0;
    D_C = 0;
    nWR = 0;
    nRD = 0;
    DATA_OUT_0 = 0;
    DATA_OUT_1 = 0;
    DATA_OUT_2 = 0;
    DATA_OUT_3 = 0;
    DATA_OUT_4 = 0;
    DATA_OUT_5 = 0;
    DATA_OUT_6 = 0;
    DATA_OUT_7 = 0;
}
