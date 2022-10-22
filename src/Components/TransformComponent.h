#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "../EntityManager.h"
//#include "../../lib/glm/glm.hpp"
#include <SDL.h>
#include "../Game.h"
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
    }

    void Render() override {
    }
};

#endif
