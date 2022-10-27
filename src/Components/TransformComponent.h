#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "../Utils.h"
#include "../Game.h"

class TransformComponent: public Component {
public:
    vec2 position;
    vec2 velocity;
    int width;
    int height;
    int scale;
    vec2 prevPos;

    TransformComponent(float posX, float posY, float velX, float velY, int w, int h, int s){
        position = vec2{posX, posY};
        velocity = vec2{velX, velY};
        width = w;
        height = h;
        scale = s;
        prevPos = vec2{posX, posY};
    }

    void Initialize() override {
    }

    SDL_Rect CalculateNextPosition(SDL_Rect rect, float deltaTime)
    {
        // Clamp to right edge of map
        if ((rect.x + (velocity.x * deltaTime)) > (WINDOW_WIDTH * 2) - (PLAYER_SPRITE_WIDTH * scale))
        {
            rect.x = (WINDOW_WIDTH * 2) - (PLAYER_SPRITE_WIDTH * scale);
        }
            // Clamp to left edge
        else if ((rect.x + (velocity.x * deltaTime)) < 0)
        {
            rect.x = 0;
        }
        else
        {
            rect.x += velocity.x * deltaTime;
        }

        // Clamp to bottom of map
        if ((rect.y + (velocity.y * deltaTime)) > (WINDOW_HEIGHT * 2) - (PLAYER_SPRITE_HEIGHT * scale))
        {
            rect.y = (WINDOW_HEIGHT* 2) - (PLAYER_SPRITE_HEIGHT * scale);
        }
        else if ((rect.y + (velocity.y * deltaTime)) < 0)
        {
            rect.y = 0;
        }
        else
        {
            rect.y += velocity.y * deltaTime;
        }
        return rect;
    }

    void Update(float deltaTime) override
    {

//        if (owner->name == "player")
//        {
//            std::cout << "Player prev pos: " << prevPos.x << ", " << prevPos.y << std::endl;
//        }
        if (!owner->resetPosition)
        {
            // Clamp to right edge of map
            if ((position.x + (velocity.x * deltaTime)) > (WINDOW_WIDTH * 2) - (width * scale))
            {
                position.x = (WINDOW_WIDTH * 2) - (width * scale);
            }
                // Clamp to left edge
            else if ((position.x + (velocity.x * deltaTime)) < 0)
            {
                position.x = 0;
            }
            else
            {
                position.x += velocity.x * deltaTime;
            }

            // Clamp to bottom of map
            if ((position.y + (velocity.y * deltaTime)) > (WINDOW_HEIGHT * 2) - (height * scale))
            {
                position.y = (WINDOW_HEIGHT* 2) - (height * scale);
            }
            else if ((position.y + (velocity.y * deltaTime)) < 0)
            {
                position.y = 0;
            }
            else
            {
                position.y += velocity.y * deltaTime;
            }

            //std::cout << "Player new pos: " << position.x << ", " << position.y << std::endl;

        }
        owner->resetPosition = false;

    }

    void Render() override {
    }
};

#endif
