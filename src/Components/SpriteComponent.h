#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SDL.h>
#include "../TextureManager.h"
#include "TransformComponent.h"
#include "../Animation.h"
#include "../Game.h"


class SpriteComponent: public Component {
private:
    TransformComponent* transform;
    SDL_Texture* texture;
    SDL_Rect sourceRectangle;
    SDL_Rect destinationRectangle;
    bool isAnimated;
    bool isAnimatedWhileNotMoving;
    int numFrames;
    int animationSpeed;
    bool isFixed;
    std::map<std::string, Animation> animations; //to keep track of my sprite animations
    std::string currentAnimationName;
    unsigned int animationIndex = 0;

public:
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    SpriteComponent(std::string assetTextureId) {
        this->isAnimated = false;
        this->isFixed = false;
        SetTexture(assetTextureId);
    }

    SpriteComponent(std::string assetTextureId, bool isFixed) {
        this->isAnimated = false;
        this->isFixed = isFixed;
        SetTexture(assetTextureId);
    }

    SpriteComponent(std::string id, int numFrames, int animationSpeed, bool hasDirections, bool isFixed, bool isAnimatedWhileNotMoving){
        this->isAnimated = true;
        if (animationSpeed == 0)
        {
            std::cout << "ERROR: animationSpeed cannot be 0" << std::endl;
            this->animationSpeed = 1;
        }
        else
        {
            this->animationSpeed = animationSpeed;
        }
        if (numFrames == 0)
        {
            std::cout << "ERROR: numFrames cannot be 0" << std::endl;
            this->numFrames = 1;
        }
        else
        {
            this->numFrames = numFrames;
        }
        this->isFixed = isFixed;
        this->isAnimatedWhileNotMoving = isAnimatedWhileNotMoving;

        if(hasDirections){
            Animation downAnimation = Animation(0, numFrames, animationSpeed);
            Animation rightAnimation = Animation(1, numFrames, animationSpeed);
            Animation leftAnimation = Animation(2, numFrames, animationSpeed);
            Animation upAnimation = Animation(3, numFrames, animationSpeed);
            Animation downStationary = Animation(4, numFrames, animationSpeed);
            Animation rightStationary = Animation(5, numFrames, animationSpeed);
            Animation leftStationary = Animation(6, numFrames, animationSpeed);
            Animation upStationary = Animation(7, numFrames, animationSpeed);

            animations.emplace("DownAnimation", downAnimation);
            animations.emplace("RightAnimation", rightAnimation);
            animations.emplace("LeftAnimation", leftAnimation);
            animations.emplace("UpAnimation", upAnimation);
            animations.emplace("DownStationary", downStationary);
            animations.emplace("RightStationary", rightStationary);
            animations.emplace("LeftStationary", leftStationary);
            animations.emplace("UpStationary", upStationary);

            this->animationIndex = 0;
            this->currentAnimationName = "RightStationary";
        }
        else {
            Animation singleAnimation = Animation(0, numFrames, animationSpeed);
            animations.emplace("SingleAnimation", singleAnimation);
            this->animationIndex=0;
            this->currentAnimationName = "SingleAnimation";
        }
        Play(this->currentAnimationName);
        SetTexture(id);
    }

    void Play(std::string animationName){
        numFrames = animations[animationName].numFrames;
        animationIndex = animations[animationName].index;
        animationSpeed = animations[animationName].animationSpeed;
        currentAnimationName = animationName;
    }

    void SetTexture(std::string assetTextureId){
        texture = Game::assetManager->GetTexture(assetTextureId);
    }

    void Initialize() override {
        transform = owner->GetComponent<TransformComponent>();
        sourceRectangle.x = 0;
        sourceRectangle.y = 0;
        sourceRectangle.w = transform->width;
        sourceRectangle.h = transform->height;
    }

    void Update(float deltaTime) override {
        // If the entity is moving and is animated, animate (flips between frames)
        // If the entity is NOT moving but is animated while not moving, animate
        if ((owner->IsMoving && isAnimated) || (!owner->IsMoving && isAnimatedWhileNotMoving))
        {
            sourceRectangle.x = sourceRectangle.w * static_cast<int>((SDL_GetTicks()/animationSpeed)%numFrames);
        }

        sourceRectangle.y = animationIndex * transform->height;
        destinationRectangle.x = static_cast<int>(transform->position.x) - (isFixed ? 0 :  Game::camera.x);
        destinationRectangle.y = static_cast<int>(transform->position.y) - (isFixed ? 0 :  Game::camera.y);
        destinationRectangle.w = transform->width * transform->scale;
        destinationRectangle.h = transform->height * transform->scale;
    }


    void Render() override {
        TextureManager::Draw(texture, sourceRectangle, destinationRectangle, spriteFlip, Game::renderer);
    }
};

#endif