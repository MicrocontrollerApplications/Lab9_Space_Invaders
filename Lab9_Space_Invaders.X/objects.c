/* 
 * File:   objects.c
 * Author: Sebastian Moosbauer
 *
 * Created on May 27, 2025, 11:20 AM
 */

#include "objects.h"
#include <string.h>

#include <GLCDnokia.h>

objects_flags_t flags = {.invaders_move_right = 1, .invader_boss = 0, .reinit = 0};


object_t defender = {.shape = DEFENDER_SHAPE, .position =
    {42, 40}, .lives = 3, .size =
    {8, 8}};

const object_t const initial_invaders[] = {
    {.shape = INVADER_SHAPE, .position =
        {4, 248}, .lives = 1, .size =
        {8, 8}},
    {.shape = INVADER_SHAPE, .position =
        {20, 248}, .lives = 1, .size =
        {8, 8}},
    {.shape = INVADER_SHAPE, .position =
        {36, 248}, .lives = 1, .size =
        {8, 8}},
    {.shape = INVADER_SHAPE, .position =
        {52, 248}, .lives = 1, .size =
        {8, 8}},
    {.shape = INVADER_SHAPE, .position =
        {68, 248}, .lives = 1, .size =
        {8, 8}},
    {.shape = INVADER_SHAPE, .position =
        {12, 0}, .lives = 1, .size =
        {8, 8}},
    {.shape = INVADER_SHAPE, .position =
        {28, 0}, .lives = 1, .size =
        {8, 8}},
    {.shape = INVADER_SHAPE, .position =
        {44, 0}, .lives = 1, .size =
        {8, 8}},
    {.shape = INVADER_SHAPE, .position =
        {60, 0}, .lives = 1, .size =
        {8, 8}},
    {.shape = INVADER_SHAPE, .position =
        {76, 0}, .lives = 1, .size =
        {8, 8}},
    {.shape = INVADER_SHAPE, .position =
        {4, 8}, .lives = 1, .size =
        {8, 8}},
    {.shape = INVADER_SHAPE, .position =
        {20, 8}, .lives = 1, .size =
        {8, 8}},
    {.shape = INVADER_SHAPE, .position =
        {36, 8}, .lives = 1, .size =
        {8, 8}},
    {.shape = INVADER_SHAPE, .position =
        {52, 8}, .lives = 1, .size =
        {8, 8}},
    {.shape = INVADER_SHAPE, .position =
        {68, 8}, .lives = 1, .size =
        {8, 8}}
};

void print_object(shape_t shape, tuple_t size, tuple_t position) {
    const uint8_t col = position.x - size.x / 2;
    const uint8_t row = (position.y - size.y) / 8 + 1;
    // set cursor to print object
    GLCD_Write(DSPL_X | col, CMD);
    GLCD_Write(DSPL_Y | row, CMD);
    // print object
    for (uint8_t i = 0; i < size.y; ++i) {
        GLCD_Write(*(shape + i), DTA);
    }
}

void print_invaders(object_t* invaders) {
    object_t invader;
    for (uint8_t i = 0; i < num_invaders; ++i) {
        invader = *(invaders + i);
        if (invader.lives)
            print_object(invader.shape, invader.size, invader.position);
    }
}

#define check_border_left(invader) invader->position.x <= invader->size.x / 2
#define check_border_right(invader) invader->position.x + invader->size.x / 2 > GLCD_MAXCOL
#define clear_invader(invader) print_object(CLEAR_INVADER_SHAPE, invader->size, invader->position)
#define print_invader(invader) print_object(invader->shape, invader->size, invader->position)

void update_invaders(object_t* invaders) {
    // clear invader's rows, to print new ones
    for (uint8_t i = 0; i < GLCD_MAXROW; ++i){
        GLCD_ClearRow(i);
    }
    
    for (uint8_t i = 0; i < num_invaders; ++i) {
        if ((invaders + i)->lives == 0)
            continue;

        // clear_invader((invaders+i));
        (invaders + i)->position.x += flags.invaders_move_right ? 1 : -1;
        print_invader((invaders+i));

        if (check_border_left((invaders + i)) || check_border_right((invaders + i))) {
            flags.switch_motion = 1;
        }
    }

    if (flags.switch_motion) {
        flags.switch_motion = 0;
        flags.invaders_move_right ^= 1;
        if (flags.invaders_move_right) {
            for (uint8_t i = num_invaders; i > 0; --i) {
                if ((invaders + i - 1)->lives == 0)
                    continue;
                
                (invaders + i - 1)->position.y += 8;
                if((invaders + i - 1)->position.y / 8 == GLCD_MAXROW){
                    flags.game_over = 1;
                    init_invaders(invaders);
                    break;
                }
            }
        }
    }
}

void init_invaders(object_t* invaders){
    memcpy(invaders, initial_invaders, sizeof(initial_invaders));
}

#define invader_is_active(invader) invader->position.y < 41
uint8_t check_for_hit(projectile_t* projectile, object_t* invader){
    if(invader->position.y > 41){
        Nop();
        return 0;
    }
    
    uint8_t vertical_hit = projectile->position.x >= invader->position.x - invader->size.x/2 &&
                            projectile->position.x <= invader->position.x + invader->size.x/2;
    uint8_t horizontal_hit = projectile->position.y <= invader->position.y + invader->size.x/2;
    return horizontal_hit && vertical_hit;
}