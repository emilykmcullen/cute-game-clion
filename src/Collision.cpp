#include "./Collision.h"

bool Collision::CheckRectangleCollision(const SDL_Rect& rectangleA, const SDL_Rect& rectangleB)
{
    return (
            rectangleA.x + rectangleA.w >= rectangleB.x &&
            rectangleB.x + rectangleB.w >= rectangleA.x &&
            rectangleA.y + rectangleA.h >= rectangleB.y &&
            rectangleB.y + rectangleB.h >= rectangleA.y
    );
}

bool Collision::CheckRectangleCollisionWithinAllowance(const SDL_Rect& rectangleA, const SDL_Rect& rectangleB, int allowance)
{
        return (
                rectangleA.x + rectangleA.w >= rectangleB.x - allowance &&
                rectangleB.x + rectangleB.w >= rectangleA.x - allowance &&
                rectangleA.y + rectangleA.h >= rectangleB.y - allowance &&
                rectangleB.y + rectangleB.h >= rectangleA.y - allowance
                );
}
