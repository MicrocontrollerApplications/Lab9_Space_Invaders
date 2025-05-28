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

projectile_t projectile = {.size =
    {2, 2}};

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

#define print_invader(invader) print_object(invader->shape, invader->size, invader->position)

void print_invaders() {
    for (uint8_t i = 0; i < num_invaders; ++i) {
        if ((invaders + i)->lives)
            print_invader((invaders + i));
    }
}

#define check_border_left(invader) invader->position.x <= invader->size.x / 2
#define check_border_right(invader) invader->position.x + invader->size.x / 2 > GLCD_MAXCOL
#define clear_invader(invader) print_object(CLEAR_INVADER_SHAPE, invader->size, invader->position)

void update_invaders() {
    if (!flags.update_invaders) {
        return;
    }
    flags.update_invaders = 0;

    // clear invader's rows, to print new ones
    for (uint8_t i = 0; i < GLCD_MAXROW; ++i) {
        GLCD_ClearRow(i);
    }

    for (uint8_t i = 0; i < num_invaders; ++i) {
        if ((invaders + i)->lives == 0)
            continue;

        // clear_invader((invaders+i));
        (invaders + i)->position.x += flags.invaders_move_right ? 1 : -1;
        print_invader((invaders + i));

        if (check_border_left((invaders + i)) || check_border_right((invaders + i))) {
            flags.switch_motion = 1;
        }
    }

    // change direction of movement
    if (flags.switch_motion) {
        flags.switch_motion = 0;
        flags.invaders_move_right ^= 1;
        // if this is the second change of direction go one row down
        if (flags.invaders_move_right) {
            for (uint8_t i = num_invaders; i > 0; --i) {
                if ((invaders + i - 1)->lives == 0)
                    continue;

                (invaders + i - 1)->position.y += 8;
                if ((invaders + i - 1)->position.y / 8 == GLCD_MAXROW) {
                    flags.game_over = 1;
                    init_invaders();
                    break;
                }
            }
        }
    }
}

void init_invaders() {
    memcpy(invaders, initial_invaders, sizeof (initial_invaders));
    hit_count = 0;
}

#define invader_is_active(invader) invader->position.y < 41

uint8_t check_for_hit(projectile_t* projectile, object_t* invader) {
    // skip currently not printed invaders (workaround...)
    if (invader->position.y > 41) {
        Nop();
        return 0;
    }

    uint8_t vertical_hit = projectile->position.x >= invader->position.x - invader->size.x / 2 &&
            projectile->position.x <= invader->position.x + invader->size.x / 2;
    uint8_t horizontal_hit = projectile->position.y <= invader->position.y + invader->size.x / 2;
    return horizontal_hit && vertical_hit;
}

#define clear_projectile(projectile) print_object(CLEAR_PROJECTILE_SHAPE, projectile->size, projectile->position)
#define clear_invader(invader) print_object(CLEAR_INVADER_SHAPE, invader->size, invader->position)

void process_collision(projectile_t* projectile, object_t* invader) {
    if(0 == --invader->lives){
        flags.hit = 1;
    }
    clear_projectile(projectile);
    clear_invader(invader);
    projectile->active = 0;
}

void update_projectile() {
    static uint8_t projectile_idx = 0;
    if (!flags.update_projectile) {
        return;
    }
    flags.update_projectile = 0;

    if (!projectile.active) {
        return;
    }

    print_object(PROJECTILE_SHAPE[projectile_idx], projectile.size, projectile.position);

    // projectile spanning two rows of the display?
    if (projectile_idx > 0 && projectile_idx % 8 == 0) {

        print_object(PROJECTILE_SHAPE[0], projectile.size, (tuple_t) {
            projectile.position.x, projectile.position.y - 8
        });
    }

    // projectile changed to new display row?
    if (projectile_idx > 0 && projectile_idx % 9 == 0) {
        projectile.position.y -= 8;
        print_object(PROJECTILE_SHAPE[1], projectile.size, projectile.position);
        projectile_idx = 1;
        if (projectile.position.y < 8) {
            projectile.active = 0;
        }
    }

    ++projectile_idx;

    // collision check
    for (uint8_t i = num_invaders; i >= 1; --i) {
        if (invaders[i - 1].lives == 0)
            continue;

        if (check_for_hit(&projectile, &invaders[i - 1])) {
            process_collision(&projectile, &invaders[i - 1]);
            break;
        }
    }
}

void update_defender() {
    if (flags.move_left) {
        flags.move_left = 0;
        if (defender.position.x > defender.size.x / 2) {
            print_object(CLEAR_DEFENDER_SHAPE, defender.size, defender.position);
            --defender.position.x;
            print_object(defender.shape, defender.size, defender.position);
        }
    }

    if (flags.move_right) {
        flags.move_right = 0;
        if (defender.position.x < GLCD_MAXCOL - defender.size.x / 2) {
            print_object(CLEAR_DEFENDER_SHAPE, defender.size, defender.position);
            ++defender.position.x;
            print_object(defender.shape, defender.size, defender.position);
        }
    }
}

typedef union {
    struct {
        unsigned unused                 :3;
        unsigned LIVE_BAR               :3;
        unsigned unused2                :2;
    };
} LIVE_BAR_t;
extern volatile LIVE_BAR_t live_bar __at(0xF8A);

const uint8_t live_counter[3] = {0b111, 0b110, 0b100, 0b000};

void check_game_status() {
    if (flags.game_over) {
        --defender.lives;
        live_bar.LIVE_BAR = live_counter[defender.lives];
        if (defender.lives == 0) {
            GLCD_Text2Out(0, 3, "GAME");
            GLCD_Text2Out(1, 3, "OVER");
            while (1);
        }
        flags.game_over = 0;
    }

    if (flags.hit) {
        ++hit_count;
        flags.hit = 0;
    }
    
    if(hit_count >= num_invaders){
        GLCD_Text2Out(0, 4, "YOU");
        GLCD_Text2Out(1, 4, "WON");
        while (1);
    }
}

void init_space_invaders(){
    init_invaders();
    print_invaders();
    print_defender();
    
    TRISB &= 0b11000111;
    live_bar.LIVE_BAR = live_counter[defender.lives];
}
