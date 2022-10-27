#ifndef CONSTANTS_H
#define CONSTANTS_H

const unsigned int WINDOW_WIDTH = 1280;
const unsigned int WINDOW_HEIGHT = 640;

const unsigned int FPS = 60;
const unsigned int FRAME_TARGET_TIME = 1000/FPS;

//BOXES

// MAKE SURE THAT WINDOW_WIDTH AND WINDOW_HEIGHT CAN BE DIVIDED BY THIS INTO WHOLE NUMBERS OR .5 OF A NUMBER
const unsigned int BOXES_PER_ROW_AND_COLUMN = 10;
const unsigned int BOX_PADDING = 0;
const float BOX_WIDTH = WINDOW_WIDTH / BOXES_PER_ROW_AND_COLUMN;
const float BOX_HEIGHT = WINDOW_HEIGHT / BOXES_PER_ROW_AND_COLUMN;
// value used to create a 'midpoint key', it's based on the window_height, so if window_height is a 3 digit number, then should be 1000
// if window_height is a 4 digit number then this should be 10000, and so on
const unsigned int BOX_MIDPOINT_MULTIPLIER = 1000;
const unsigned int BOX_NEIGHBOURS = 4;

const unsigned int PLAYER_SPRITE_HEIGHT = 64;
const unsigned int PLAYER_SPRITE_WIDTH = 96;

enum LayerType {
    TILEMAP_LAYER = 0,
    OBSTACLE_LAYER = 1,
    PLAYER_LAYER = 2,
    NPC_LAYER = 3
};

const unsigned int NUM_LAYERS = 4;

enum CollisionType {
    NO_COLLISION,
    PLAYER_NPC_COLLISION,
    PLAYER_VEGETATION_COLLISION,
    PLAYER_LEVEL_COMPLETE_COLLISION
};


#endif