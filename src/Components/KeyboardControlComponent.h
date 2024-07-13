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
    bool upKeyPressedFirst = false;
    bool downKeyPressed = false;
    bool rightKeyPressed = false;
    bool leftKeyPressed = false;
    bool leftKeyPressedFirst = false;
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

            if (keyCode.compare(upKey)==0 && !upKeyPressed){
                upKeyPressed = true;
                upKeyPressedFirst = !downKeyPressed;
            }
            if (keyCode.compare(rightKey)==0 && !rightKeyPressed){
                rightKeyPressed = true;
                leftKeyPressedFirst = leftKeyPressed;
            }
            if (keyCode.compare(downKey)==0 && !downKeyPressed){
                downKeyPressed = true;
                upKeyPressedFirst = upKeyPressed;
            }
            if (keyCode.compare(leftKey)==0 && !leftKeyPressed){
                leftKeyPressed = true;
                leftKeyPressedFirst = !rightKeyPressed;
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
        if (upKeyPressed && (!downKeyPressed || !upKeyPressedFirst))
        {
            transform->velocity.y = -velocity;
        }
        if (rightKeyPressed && (!leftKeyPressed || leftKeyPressedFirst))
        {
            transform->velocity.x = velocity;
        }
        if (downKeyPressed && (!upKeyPressed || upKeyPressedFirst))
        {
            transform->velocity.y = velocity;
        }
        if (leftKeyPressed && (!rightKeyPressed || !leftKeyPressedFirst))
        {
            transform->velocity.x = -velocity;
        }

        if ((downKeyPressed && (!upKeyPressed || !upKeyPressedFirst)) && (rightKeyPressed && (!leftKeyPressed || !leftKeyPressedFirst)))
        {
            sprite->Play("RightAnimation");
        }
        else if((downKeyPressed && (!upKeyPressed || !upKeyPressedFirst)) && (leftKeyPressed && (!rightKeyPressed || leftKeyPressedFirst)))
        {
            sprite->Play("LeftAnimation");
        }
        else if (downKeyPressed && (!upKeyPressed || !upKeyPressedFirst))
        {
            sprite->Play("DownAnimation");
        }

        else if ((upKeyPressed && (!downKeyPressed || upKeyPressedFirst)) && (rightKeyPressed && (!leftKeyPressed || !leftKeyPressedFirst)))
        {
            sprite->Play("RightAnimation");
        }
        else if ((upKeyPressed && (!downKeyPressed || upKeyPressedFirst)) && (leftKeyPressed && (!rightKeyPressed || leftKeyPressedFirst)))
        {
            sprite->Play("LeftAnimation");
        }
        else if (upKeyPressed && (!downKeyPressed || upKeyPressedFirst))
        {
            sprite->Play("UpAnimation");
        }

        else if (rightKeyPressed && (!leftKeyPressed || !leftKeyPressedFirst))
        {
            sprite->Play("RightAnimation");
        }
        else if (leftKeyPressed && (!rightKeyPressed || leftKeyPressedFirst))
        {
            sprite->Play("LeftAnimation");
        }
    }
};

#endif