#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "../Utils.h"

class TransformComponent: public Component {
public:
    vec2 position;
    vec2 velocity;
    int width;
    int height;
    int scale;

    TransformComponent(float posX, float posY, float velX, float velY, int w, int h, int s){
        position = vec2{posX, posY};
        velocity = vec2{velX, velY};
        width = w;
        height = h;
        scale = s;
    }

    void Initialize() override {

    }

    void Update(float deltaTime) override
    {

        if (owner->name == "player")
        {
            // Clamp to right edge of map
            if ((position.x + (velocity.x * deltaTime)) > (WINDOW_WIDTH * 2) - (PLAYER_SPRITE_WIDTH * scale))
            {
                position.x = (WINDOW_WIDTH * 2) - (PLAYER_SPRITE_WIDTH * scale);
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
            if ((position.y + (velocity.y * deltaTime)) > (WINDOW_HEIGHT * 2) - (PLAYER_SPRITE_HEIGHT * scale))
            {
                position.y = (WINDOW_HEIGHT* 2) - (PLAYER_SPRITE_HEIGHT * scale);
            }
            else if ((position.y + (velocity.y * deltaTime)) < 0)
            {
                position.y = 0;
            }
            else
            {
                position.y += velocity.y * deltaTime;
            }

        }
        else
        {
            position.x += velocity.x * deltaTime;
            position.y += velocity.y * deltaTime;
        }
    }

    void Render() override {
    }
};

#endif
