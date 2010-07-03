#ifndef GLOBAL
#define GLOBAL

#define MARKER 15
#define XMAP_W 40
#define XMAP_H 40

#define KEY_SCROLL_SIZE 16

#define BLOCK_SIZE 32

#define K_W 8 //Boundary Block Konstant
#define K_H 20

#define SCREEN_W 24
#define SCREEN_H 18

#define STATIC 1
#define MOB 2
#define PLAYER 3
#define OBJECT 4


#define OBJECT_JUMPER 100
#define MOB_GOOMPA 101
#define MOB_GOOMPA_DEAD 102
#define OBJECT_QUESTION_MARK 103
#define MOB_MAR 104
#define MOB_MAR_WALKL 104
#define MOB_MAR_WALKR 105
#define MOB_MAR_STANDL 106
#define MOB_MAR_STANDR 107
#define OBJ_PLATFORM_1 108
#define OBJ_PLATFORM_2 109
#define OBJ_PLATFORM_3 110

#define COLLISION_THRESHOLD 0.0
#define MOVEMENT_MULTIPLIER 0.9
#define MIN_INCREMENT 0.1
#define GRAVITY 1.5 //adder
#define STD_GROUND_FRICTION 0.80
#define MAX_VELOCITY 16
#define MINRUNVELOCITY 0.3
#define MAX_JUMP BLOCK_SIZE*2
#define JUMPSTARTVELOCITY 6
#define JUMPCODE 10000
#define JUMPTHRESHOLD 1
#define SLIDETHRESHOLD 1



#define MAPOBJ 1
#define PLAYEROBJ 2

#define DBGB 1024

#include "t_debug/debug.h"
#endif
