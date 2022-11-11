#ifndef CONSTANTS_H
#define CONSTANTS_H

const unsigned int WINDOW_WIDTH = 1280;
const unsigned int WINDOW_HEIGHT = 800;

const unsigned int FPS = 60;
const unsigned int FRAME_TARGET_TIME = 1000/FPS;

enum LayerType {
    TILEMAP_LAYER = 0,
    OBSTACLE_LAYER = 1,
    PLAYER_LAYER = 2,
    OBSTACLE_ONTOP_LAYER = 3,
    NPC_LAYER = 4,
    INTERACTION_LAYER = 5
};
const unsigned int NUM_LAYERS = 5;

enum InteractionType {
    NO_INTERACTION = 0,
    LOAD_SCENE = 1,
    SPEAK = 2,
    DEACTIVATE = 3
};

enum CursorType {
    REGULAR = 0,
    LARGE = 1,
    LARGE_GREY = 2
};


enum CollisionType {
    NO_COLLISION,
    PLAYER_NPC_COLLISION,
    PLAYER_VEGETATION_COLLISION,
    PLAYER_LEVEL_COMPLETE_COLLISION,
    PLAYER_OBSTACLE_COLLISION
};


#endif