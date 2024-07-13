#ifndef KEYBOARDCONTROLCOMPONENT_H
#define KEYBOARDCONTROLCOMPONENT_H

#include "../Game.h"
#include "../EntityManager.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"

class KeyboardControlComponent: public Component {
public:
    std::string upKey;
    std::string downKey;
    std::string rightKey;
    std::string leftKey;
    std::string shootKey;
    bool upKeyPressed = false;
    bool downKeyPressed = false;
    bool rightKeyPressed = false;
    bool leftKeyPressed = false;
    TransformComponent *transform;
    SpriteComponent *sprite;

    KeyboardControlComponent(){}

    KeyboardControlComponent(std::string upKey, std::string rightKey, std::string downKey, std::string leftKey, std::string shootKey){
        this->upKey = GetSDLKeyStringCode(upKey);
        this->rightKey = GetSDLKeyStringCode(rightKey);
        this->downKey = GetSDLKeyStringCode(downKey);
        this->leftKey = GetSDLKeyStringCode(leftKey);
        this->shootKey = GetSDLKeyStringCode(shootKey);
    }

    ~KeyboardControlComponent()
    {
        if (sprite)
        {
            delete sprite;
        }
        if (transform)
        {
            delete transform;
        }
    }

    std::string GetSDLKeyStringCode(std::string key){
        //return values are the keys for these keys in SDL
        if (key.compare("up") == 0) return "1073741906";
        if (key.compare("down") == 0) return "1073741905";
        if (key.compare("left") == 0) return "1073741904";
        if (key.compare("right") == 0) return "1073741903";
        if (key.compare("space") == 0) return "32";
        return std::to_string(static_cast<int>(key[0]));
    }

    void Initialize() override {
        transform = owner->GetComponent<TransformComponent>();
        sprite = owner->GetComponent<SpriteComponent>();

    }

    bool HandleEvent(SDL_Event &event)
    {
        if(event.type == SDL_KEYDOWN){
            std::string keyCode = std::to_string(event.key.keysym.sym);

            if (keyCode.compare(upKey)==0){
                upKeyPressed = true;
            }
            if (keyCode.compare(rightKey)==0){
                rightKeyPressed = true;
            }
            if (keyCode.compare(downKey)==0){
                downKeyPressed = true;
            }
            if (keyCode.compare(leftKey)==0){
                leftKeyPressed = true;
            }
            if (keyCode.compare(shootKey)==0){
                // to do
            }
        }
        if (event.type == SDL_KEYUP){
            std::string keyCode = std::to_string(event.key.keysym.sym);

            if (keyCode.compare(upKey)==0){
                upKeyPressed = false;
                transform->velocity.y = 0;
            }
            if (keyCode.compare(rightKey)==0){
                rightKeyPressed = false;
                transform->velocity.x=0;
            }
            if (keyCode.compare(downKey)==0){
                downKeyPressed = false;
                transform->velocity.y=0;
            }
            if (keyCode.compare(leftKey)==0){
                leftKeyPressed = false;
                transform->velocity.x=0;
            }
        }
        if (upKeyPressed || downKeyPressed || rightKeyPressed || leftKeyPressed)
        {
            owner->IsMoving = true;
        }
        else
        {
            owner->IsMoving = false;
        }
        SetMovement();
        return false;
    }

    void SetMovement()
    {
        int velocity = 250;
        if (upKeyPressed && rightKeyPressed || rightKeyPressed && downKeyPressed || downKeyPressed && leftKeyPressed || leftKeyPressed && upKeyPressed)
        {
            velocity = 180;
        }
        if (upKeyPressed)
        {
            transform->velocity.y = -velocity;
        }
        if (rightKeyPressed)
        {
            transform->velocity.x = velocity;
        }
        if (downKeyPressed)
        {
            transform->velocity.y = velocity;
        }
        if (leftKeyPressed)
        {
            transform->velocity.x = -velocity;
        }

        if (downKeyPressed && rightKeyPressed)
        {
            sprite->Play("RightAnimation");
        }
        else if(downKeyPressed && leftKeyPressed)
        {
            sprite->Play("LeftAnimation");
        }
        else if (downKeyPressed)
        {
            sprite->Play("DownAnimation");
        }

        else if  (upKeyPressed && rightKeyPressed)
        {
            sprite->Play("RightAnimation");
        }
        else if (upKeyPressed && leftKeyPressed)
        {
            sprite->Play("LeftAnimation");
        }
        else if (upKeyPressed)
        {
            sprite->Play("UpAnimation");
        }

        else if (rightKeyPressed)
        {
            sprite->Play("RightAnimation");
        }
        else if (leftKeyPressed)
        {
            sprite->Play("LeftAnimation");
        }
    }
};

#endif