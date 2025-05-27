//##############################################################################
//    filename:        glcd12864_config.h
//##############################################################################
//    configuration file for GLCD library (pins ...)
//##############################################################################
//
//      Author:             V.SchK
//      Company:            HS-Ulm
//
//      Revision:           1.0
//      Date:               April 2016
//      Assembled using     C18 3.41+ / XC8 1.30+
//
//##############################################################################

#ifndef _GLCD12864_CONFIG_H
#define _GLCD12864_CONFIG_H

/** Pin Defining **************************************************************/

    #define nRES            LATBbits.LATB5  // reset
    #define nCS             LATBbits.LATB3  // chip select
    #define D_C             LATBbits.LATB2  // data or cmd
    #define nWR             LATBbits.LATB1  // write
    #define nRD             LATBbits.LATB0  // read
    #define LCD_PIN_INIT()  TRISB &= 0b11010000; (ANCON1bits.PCFG11 = 1)
    // PORTC is digital except of RC2/AN11 (1=digital))

    #define mLCD_IN()   (TRISC = 0xFF)        // for data lines
    #define mLCD_OUT()  (TRISC = 0x00)

    #define DISP_DATA	PORTC //VSK - used for RD and WR !!! (full port))
// alternative
//    #define DATA_IN_0   PORTCbits.RC0
//    #define DATA_IN_1   PORTCbits.RC1
//    #define DATA_IN_2   PORTCbits.RC2
//    #define DATA_IN_3   PORTCbits.RC3
//    #define DATA_IN_4   PORTCbits.RC4
//    #define DATA_IN_5   PORTCbits.RC5
//    #define DATA_IN_6   PORTCbits.RC6
//    #define DATA_IN_7   PORTCbits.RC7
//
//    #define DATA_OUT_0  LATCbits.LATC0
//    #define DATA_OUT_1  LATCbits.LATC1
//    #define DATA_OUT_2  LATCbits.LATC2
//    #define DATA_OUT_3  LATCbits.LATC3
//    #define DATA_OUT_4  LATCbits.LATC4
//    #define DATA_OUT_5  LATCbits.LATC5
//    #define DATA_OUT_6  LATCbits.LATC6
//    #define DATA_OUT_7  LATCbits.LATC7

#endif //_GLCD12864_CONFIG_H
