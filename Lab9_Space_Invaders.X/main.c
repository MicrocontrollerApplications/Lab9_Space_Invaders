/*
 * File:   main.c
 * Author: Sebastian Moosbauer
 *
 * Created on May 27, 2025, 9:48 AM
 */


#include <xc.h>
#include <space_invaders.h>
#include <GLCDnokia.h>

void __init(void);

void main(void) {
    __init();
    
    init_space_invaders();
    
    while (1) {
        update_defender();
        update_invaders();
        update_projectile();
        check_game_status();
    }

    return;
}

void __init(void) {
    OSCCONbits.IRCF = 0b111; // Fosc = 16MHz
    GLCD_Init();

    // configure pin for Button TL as input

    ANSELAbits.ANSA2 = 0;
    TRISAbits.TRISA2 = 1;

    T1CONbits.TMR1CS = 0; // Fosc / 4
    T1CONbits.T1CKPS = 0b10; // PS = 1:8
    T1CONbits.T1RD16 = 1;
    PIR1bits.TMR1IF = 0;
    T1CONbits.TMR1ON = 1;

    INTCON2bits.INTEDG2 = 0; // RB2 Interrupt on falling edge
    INTCON3bits.INT2IF = 0;
    INTCON3bits.INT2IE = 1;

    INTCON2bits.INTEDG0 = 0; // RB0 Interrupt on falling edge
    INTCONbits.INT0IF = 0;
    INTCONbits.INT0IE = 1;

    PIE1bits.TMR1IE = 1;
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
}

void __interrupt(high_priority) __isr(void) {
    // catch and process interrupt for TL to trigger a shot
    if ( /*...*/ ) {
        
        if (!projectile.active) {
            // enable projectile
            // projectile.active = ; 
            projectile.position = defender.position;
        }

        return;
    }

    // interrupt for rotary encoder
    if( /*...*/ ) {
        
    }

    // global timer to schedule invader's and projectile's updates
    if (PIR1bits.TMR1IF && PIE1bits.TMR1IE) {
        static uint8_t counter = 0;
        PIR1bits.TMR1IF = 0;
        if (10 == counter) {
            flags.update_invaders = 1;
            counter = 0;
        }

        flags.update_projectile = 1;
        ++counter;
        return;
    }

    while (1) {
        Nop();
    }
}
