/*
 * File:   main.c
 * Author: Sebastian Moosbauer
 *
 * Created on May 27, 2025, 9:48 AM
 */


#include <xc.h>
#include <objects.h>
#include <GLCDnokia.h>

void __init(void);

object_t invaders[num_invaders];
projectile_t projectile = {.size = {2, 2}};

void main(void) {
    __init();
    init_invaders(invaders);
    print_object(defender.shape, defender.size, defender.position);
    print_invaders(invaders);
    projectile.position = defender.position;
    while (1) {
        if (PORTBbits.RB1 == 0) {
            while (PORTBbits.RB1 == 0);
            projectile.active = 1;
        }
        if (flags.update_projectile && projectile.active) {
            flags.update_projectile = 0;
            static uint8_t projectile_idx = 0;
            static tuple_t prev_pos;
            print_object(PROJECTILE_SHAPE[projectile_idx], projectile.size, projectile.position);
            if (projectile_idx > 0 && projectile_idx % 8 == 0) {

                print_object(PROJECTILE_SHAPE[0], projectile.size, (tuple_t) {
                    projectile.position.x, projectile.position.y - 8
                });
            }
            if (projectile_idx > 0 && projectile_idx % 9 == 0) {

                print_object(PROJECTILE_SHAPE[1], projectile.size, (tuple_t) {
                    projectile.position.x, projectile.position.y - 8
                });
                projectile_idx = 1;
                projectile.position.y -= 8;
                if (projectile.position.y < 16) {
                    projectile.active = 0;
                }
            }

            ++projectile_idx;

            // collision check
        }


        if (flags.update_invaders) {
            flags.update_invaders = 0;
            update_invaders(invaders);
        }

        if (flags.game_over) {
            --defender.lives;
            if (defender.lives == 0) {
                GLCD_Text2Out(0, 3, "GAME");
                GLCD_Text2Out(1, 3, "OVER");
                while (1);
            }
            flags.game_over = 0;
        }

        // print_object(defender.shape, defender.size, defender.position);
    }

    return;
}

void __init(void) {
    OSCCONbits.IRCF = 0b111; // Fosc = 16MHz
    GLCD_Init();

    ANSELB = 0;
    TRISBbits.TRISB2 = 1;
    TRISBbits.TRISB1 = 1;

    T1CONbits.TMR1CS = 0; // Fosc / 4
    T1CONbits.T1CKPS = 0b11; // PS = 1:8
    T1CONbits.T1RD16 = 1;
    PIR1bits.TMR1IF = 0;
    T1CONbits.TMR1ON = 1;

    INTCON2bits.INTEDG2 = 0; // RB2 Interrupt on falling edge
    INTCON3bits.INT2IF = 0;
    INTCON3bits.INT2IE = 1;

    PIE1bits.TMR1IE = 1;
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
}

void __interrupt(high_priority) __isr(void) {
    if (INTCON3bits.INT2IF && INTCON3bits.INT2IE) {
        INTCON3bits.INT2F = 0;
        if (!projectile.active) {
            projectile.active = 1;
            projectile.position = defender.position;
        }

        return;
    }

    if (PIR1bits.TMR1IF && PIE1bits.TMR1IE) {
        static uint8_t counter = 0;
        PIR1bits.TMR1IF = 0;
        if (15 == counter) {
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
