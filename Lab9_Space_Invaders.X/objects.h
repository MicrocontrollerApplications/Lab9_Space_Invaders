/* 
 * File:   objects.h
 * Author: Sebastian Moosbauer
 *
 * Created on May 27, 2025, 9:30 AM
 */

#ifndef OBJECTS_H
#define	OBJECTS_H

#include <xc.h>

const uint8_t INVADER_SHAPE[] = {0x98, 0x5C, 0xB6, 0x5F, 0x5F, 0xB6, 0x5C, 0x98};
const uint8_t CLEAR_INVADER_SHAPE[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const uint8_t DEFENDER_SHAPE[] = {0xC0, 0xC0, 0xF0, 0x00, 0x00, 0xF0, 0xC0, 0xC0};
const uint8_t CLEAR_DEFENDER_SHAPE[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const uint8_t PROJECTILE_SHAPE[10][2] = {
    {0x80, 0x80},
    {0xC0, 0xC0},
    {0x60, 0x60},
    {0x30, 0x30},
    {0x18, 0x18},
    {0x0C, 0x0C},
    {0x06, 0x06},
    {0x03, 0x03},
    {0x01, 0x01},
    {0x00, 0x00}
};
const uint8_t CLEAR_PROJECTILE_SHAPE[] = {0x00, 0x00};

typedef uint8_t* shape_t;

typedef struct {
    uint8_t x;
    uint8_t y;
} tuple_t;

typedef struct {
    shape_t shape;
    tuple_t position;
    uint8_t lives;
    tuple_t size;
} object_t;

typedef struct {
    tuple_t position;
    tuple_t size;
    unsigned active : 1;
} projectile_t;

typedef struct {
    unsigned invaders_move_right : 1;
    unsigned invader_boss : 1;
    unsigned reinit : 1;
    unsigned switch_motion : 1;
    unsigned game_over : 1;
    unsigned update_invaders : 1;
    unsigned update_projectile : 1;
    unsigned move_left : 1;
    unsigned move_right : 1;
} objects_flags_t;

extern object_t defender;
// extern object_t invaders[];
#define num_invaders 15
extern objects_flags_t flags;

void print_object(shape_t shape, tuple_t size, tuple_t position);
void print_invaders(object_t* invaders);
void update_invaders(object_t* invaders);
void init_invaders(object_t* invaders);
uint8_t check_for_hit(projectile_t* projectile, object_t* invader);

#endif	/* OBJECTS_H */

