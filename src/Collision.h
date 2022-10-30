#ifndef COLLISION_H
#define COLLISION_H

#include <SDL.h>
class Collision {
public:
    static bool CheckRectangleCollision(const SDL_Rect& rectangleA, const SDL_Rect& rectangleB);
    static bool CheckRectangleCollisionWithinAllowance(const SDL_Rect& rectangleA, const SDL_Rect& rectangleB, int allowance);
};



#endif