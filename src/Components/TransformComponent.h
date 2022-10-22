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

    void Update(float deltaTime) override {
        position.x += velocity.x * deltaTime;
        position.y += velocity.y * deltaTime;

        //TO DO: SORT OUT SOMETHING TO SORT THIS KINDA SITUATION!
        if (owner->name == "player")
        {
            if (position.x > (WINDOW_WIDTH * 2) - PLAYER_SPRITE_WIDTH)
            {
                position.x = (WINDOW_WIDTH * 2) - PLAYER_SPRITE_WIDTH;
            }
        }
    }

    void Render() override {
    }
};

#endif
