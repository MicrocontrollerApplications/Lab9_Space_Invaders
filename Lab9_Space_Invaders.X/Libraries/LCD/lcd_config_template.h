//##############################################################################
//    filename:        lcd_config.h
//##############################################################################
//    configuration file for LCD library (pins, timing, voltage, ...)
//##############################################################################
//
//      Author:             V.SchK
//      Company:            THU
//
//      Revision:           3.0
//      Date:               May 2019
//      Assembled using     XC8 2.00+
//
//##############################################################################

#ifndef _LCD_CONFIG_H
#define _LCD_CONFIG_H

#include <xc.h>
#include "a_globalheader.h"	//#define _XTAL_FREQ ...

#define LCD_TIMEOUT 100     // max nr. of busy checks ...

#define LCD_DELAY_5MS() __delay_ms(5)
#define LCD_DELAY_1US() __delay_us(1)


// uncomment the board in use or define a custom pinnig ;-) --------------------
#define uC_QUICK

//#define PICDEM2p_2002
//#define PICDEM2p_2006
//#define PICDEM_USB

//#define PIC_ADAPTER
//#define EXT_LCD_3_3_V   //DOG... displays
//#define EXT_LCD_5_V

//#define MINI_AD_LCD
//#define MINI_RS232_LCD
//#define MINI_...


//  custom boards at the end

#if defined uC_QUICK
    #warning "LCD-pinning for uC-Quick board !!!"
    #define LCD_E       LATCbits.LATC1
    #define LCD_E_DIR   TRISCbits.TRISC1
    #define LCD_RW      LATCbits.LATC0
    #define LCD_RW_DIR  TRISCbits.TRISC0
    #define LCD_RS      LATAbits.LATA5
    #define LCD_RS_DIR  TRISAbits.TRISA5

    #define LCD_D4_IN   PORTBbits.RB2
    #define LCD_D5_IN   PORTBbits.RB3
    #define LCD_D6_IN   PORTBbits.RB4
    #define LCD_D7_IN   PORTBbits.RB5
    #define LCD_D4_OUT  LATBbits.LATB2
    #define LCD_D5_OUT  LATBbits.LATB3
    #define LCD_D6_OUT  LATBbits.LATB4
    #define LCD_D7_OUT  LATBbits.LATB5
    #define LCD_D4_DIR  TRISBbits.TRISB2
    #define LCD_D5_DIR  TRISBbits.TRISB3
    #define LCD_D6_DIR  TRISBbits.TRISB4
    #define LCD_D7_DIR  TRISBbits.TRISB5

//    #define LCD_DIR_IN()  LCD_D4_DIR = LCD_D5_DIR = LCD_D6_DIR = LCD_D7_DIR = 1
//    #define LCD_DIR_OUT() LCD_D4_DIR = LCD_D5_DIR = LCD_D6_DIR = LCD_D7_DIR = 0
    #define LCD_DIR_IN()    TRISB |= 0x3C
    #define LCD_DIR_OUT()   TRISB &= 0xC3

	#define LCD_PINS_DIGITAL()  ANSELB &= 0b11000011

#elif defined  PICDEM2p_2002
    #warning "LCD-pinning for PICDEM2+ 2002 !!!"
    #define	LCD_E		LATAbits.LATA1
    #define	LCD_E_DIR	TRISAbits.TRISA1
    #define	LCD_RW		LATAbits.LATA2
    #define	LCD_RW_DIR	TRISAbits.TRISA2
    #define	LCD_RS		LATAbits.LATA3
    #define	LCD_RS_DIR	TRISAbits.TRISA3

    #define	LCD_D4_IN	PORTDbits.RD0
    #define	LCD_D5_IN	PORTDbits.RD1
    #define	LCD_D6_IN	PORTDbits.RD2
    #define	LCD_D7_IN	PORTDbits.RD3
    #define	LCD_D4_OUT	LATDbits.LATD0
    #define	LCD_D5_OUT	LATDbits.LATD1
    #define	LCD_D6_OUT	LATDbits.LATD2
    #define	LCD_D7_OUT	LATDbits.LATD3
    #define	LCD_D4_DIR	TRISDbits.TRISD0
    #define	LCD_D5_DIR	TRISDbits.TRISD1
    #define	LCD_D6_DIR	TRISDbits.TRISD2
    #define	LCD_D7_DIR	TRISDbits.TRISD3

    #define LCD_DIR_IN()  LCD_D4_DIR = LCD_D5_DIR = LCD_D6_DIR = LCD_D7_DIR = 1
    #define LCD_DIR_OUT() LCD_D4_DIR = LCD_D5_DIR = LCD_D6_DIR = LCD_D7_DIR = 0
//    #define LCD_DIR_IN()    TRISD |= 0x0F
//    #define LCD_DIR_OUT()   TRISD &= 0xF0

    #define LCD_PINS_DIGITAL()  ???????

#elif defined(PICDEM2p_2006) || defined(PIC_ADAPTER)
    #warning "LCD-pinning for PICDEM2+ 2006 !!!"
    #define	LCD_E		LATDbits.LATD6
    #define	LCD_E_DIR	TRISDbits.TRISD6
    #define	LCD_RW		LATDbits.LATD5
    #define	LCD_RW_DIR	TRISDbits.TRISD5
    #define	LCD_RS		LATDbits.LATD4
    #define	LCD_RS_DIR	TRISDbits.TRISD4

    #define	LCD_D4_IN	PORTDbits.RD0
    #define	LCD_D5_IN	PORTDbits.RD1
    #define	LCD_D6_IN	PORTDbits.RD2
    #define	LCD_D7_IN	PORTDbits.RD3
    #define	LCD_D4_OUT	LATDbits.LATD0
    #define	LCD_D5_OUT	LATDbits.LATD1
    #define	LCD_D6_OUT	LATDbits.LATD2
    #define	LCD_D7_OUT	LATDbits.LATD3
    #define	LCD_D4_DIR	TRISDbits.TRISD0
    #define	LCD_D5_DIR	TRISDbits.TRISD1
    #define	LCD_D6_DIR	TRISDbits.TRISD2
    #define	LCD_D7_DIR	TRISDbits.TRISD3

    #define LCD_DIR_IN()  LCD_D4_DIR = LCD_D5_DIR = LCD_D6_DIR = LCD_D7_DIR = 1
    #define LCD_DIR_OUT() LCD_D4_DIR = LCD_D5_DIR = LCD_D6_DIR = LCD_D7_DIR = 0
//    #define LCD_DIR_IN()    TRISD |= 0x0F
//    #define LCD_DIR_OUT()   TRISD &= 0xF0

    #define LCD_PINS_DIGITAL()  ???????

#elif defined  MINI_AD_LCD
    #warning "LCD-pinning for MINI_AD_LCD board !!!"
    #define	LCD_E		LATBbits.LATB2
    #define	LCD_E_DIR	TRISBbits.TRISB2
    #define	LCD_RW		LATBbits.LATB3
    #define	LCD_RW_DIR	TRISBbits.TRISB3
    #define	LCD_RS		LATAbits.LATA0
    #define	LCD_RS_DIR	TRISAbits.TRISA0

    #define	LCD_D4_IN	PORTAbits.RA7
    #define	LCD_D4_OUT	LATAbits.LATA7
    #define	LCD_D4_DIR	TRISAbits.TRISA7

    #define	LCD_D5_IN	PORTAbits.RA6
    #define	LCD_D5_OUT	LATAbits.LATA6
    #define	LCD_D5_DIR	TRISAbits.TRISA6

    #define	LCD_D6_IN	PORTBbits.RB4
    #define	LCD_D6_OUT	LATBbits.LATB4
    #define	LCD_D6_DIR	TRISBbits.TRISB4

    #define	LCD_D7_IN	PORTBbits.RB5
    #define	LCD_D7_OUT	LATBbits.LATB5
    #define	LCD_D7_DIR	TRISBbits.TRISB5

    #define LCD_DIR_IN()  LCD_D4_DIR = LCD_D5_DIR = LCD_D6_DIR = LCD_D7_DIR = 1
    #define LCD_DIR_OUT() LCD_D4_DIR = LCD_D5_DIR = LCD_D6_DIR = LCD_D7_DIR = 0
//    #define LCD_DIR_IN()    TRISA |= 0xC0; TRISB |= 0x30
//    #define LCD_DIR_OUT()   TRISA &= 0x3F; TRISB &= 0xCF

    #define LCD_PINS_DIGITAL()  ???????

#elif defined MINI_RS232_LCD
    #warning "LCD-pinning for MINI_RS232_LCD board !!!"
    #define	LCD_E		LATAbits.LATA1
    #define	LCD_E_DIR	TRISAbits.TRISA1
    #define	LCD_RW		LATAbits.LATA4
    #define	LCD_RW_DIR	TRISAbits.TRISA4
    #define	LCD_RS		LATAbits.LATA2
    #define	LCD_RS_DIR	TRISAbits.TRISA2

    #define	LCD_D4_IN	PORTBbits.RB5
    #define	LCD_D5_IN	PORTAbits.RA6
    #define	LCD_D6_IN	PORTAbits.RA7
    #define	LCD_D7_IN	PORTBbits.RB2

    #define	LCD_D4_OUT	LATBbits.LATB5
    #define	LCD_D5_OUT	LATAbits.LATA6
    #define	LCD_D6_OUT	LATAbits.LATA7
    #define	LCD_D7_OUT	LATBbits.LATB2

    #define	LCD_D4_DIR	TRISBbits.TRISB5
    #define	LCD_D5_DIR	TRISAbits.TRISA6
    #define	LCD_D6_DIR	TRISAbits.TRISA7
    #define	LCD_D7_DIR	TRISBbits.TRISB2

    #define LCD_DIR_IN()  LCD_D4_DIR = LCD_D5_DIR = LCD_D6_DIR = LCD_D7_DIR = 1
    #define LCD_DIR_OUT() LCD_D4_DIR = LCD_D5_DIR = LCD_D6_DIR = LCD_D7_DIR = 0
//    #define LCD_DIR_IN()    TRISA |= 0xC0; TRISB |= 0x24
//    #define LCD_DIR_OUT()   TRISA &= 0x3F; TRISB &= 0xDB

    #define LCD_PINS_DIGITAL()  ???????

#elif defined PICDEM_USB
    #warning "LCD-pinning for PICDEM_USB board - 8bit !!!"
    #define LCD_USE_8BIT_DATA
    #define	LCD_E		LATEbits.LATE2
    #define	LCD_E_DIR	TRISEbits.TRISE2
    #define	LCD_RW		LATEbits.LATE1
    #define	LCD_RW_DIR	TRISEbits.TRISE1
    #define	LCD_RS		LATEbits.LATE0
    #define	LCD_RS_DIR	TRISEbits.TRISE0

    #define	LCD_D4_IN	PORTDbits.RD4
    #define	LCD_D5_IN	PORTDbits.RD5
    #define	LCD_D6_IN	PORTDbits.RD6
    #define	LCD_D7_IN	PORTDbits.RD7

    #define	LCD_D4_OUT	LATDbits.LATD4
    #define	LCD_D5_OUT	LATDbits.LATD5
    #define	LCD_D6_OUT	LATDbits.LATD6
    #define	LCD_D7_OUT	LATDbits.LATD7

    #define	LCD_D4_DIR	TRISDbits.TRISD4
    #define	LCD_D5_DIR	TRISDbits.TRISD5
    #define	LCD_D6_DIR	TRISDbits.TRISD6
    #define	LCD_D7_DIR	TRISDbits.TRISD7

    #ifdef LCD_USE_8BIT_DATA
        #define	LCD_D0_IN	PORTDbits.RD0
        #define	LCD_D1_IN	PORTDbits.RD1
        #define	LCD_D2_IN	PORTDbits.RD2
        #define	LCD_D3_IN	PORTDbits.RD3

        #define	LCD_D0_OUT	LATDbits.LATD0
        #define	LCD_D1_OUT	LATDbits.LATD1
        #define	LCD_D2_OUT	LATDbits.LATD2
        #define	LCD_D3_OUT	LATDbits.LATD3

        #define	LCD_D0_DIR	TRISDbits.TRISD0
        #define	LCD_D1_DIR	TRISDbits.TRISD1
        #define	LCD_D2_DIR	TRISDbits.TRISD2
        #define	LCD_D3_DIR	TRISDbits.TRISD3

        #define LCD_DIR_IN()    TRISD = 0xFF
        #define LCD_DIR_OUT()   TRISD = 0x00
    #else
        #define LCD_DIR_IN()    TRISD |= 0xF0
        #define LCD_DIR_OUT()   TRISD &= 0x0F
    #endif

    #define LCD_PINS_DIGITAL()  ???????

#else
    #error PLEASE SPECIFY LCD CONNECTIONS !
#endif

//------------------------------------------------------------------------------
#ifdef PICDEM2p_2006
    #define LCD_ON      LATDbits.LATD7
    #define LCD_ON_DIR  TRISDbits.TRISD7
    #define LCD_On()    LCD_ON = 1;LCD_ON_DIR = 0;
    #warning DO NOT FORGET TO SWITCH ON THE DISPLAY AND TO ADD A POWER UP DELAY !
#else
    #define LCD_On()
#endif


#endif //_LCD_CONFIG_H
