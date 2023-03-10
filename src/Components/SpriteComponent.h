#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SDL.h>
#include "../TextureManager.h"
#include "TransformComponent.h"
#include "../Animation.h"
#include "../Game.h"
#include "ColliderComponent.h"


class SpriteComponent: public Component {
private:
    TransformComponent* transform;
    SDL_Texture* texture;
    // The rectangle we are getting the sprite from, this is used on the spritesheet and isn't an on screen rect

    // Where we will display the sprite on screen
    SDL_Rect destinationRectangle;
    bool isAnimated;
    bool isAnimatedWhileNotMoving;
    int numFrames;
    int animationSpeed;
    bool isFixed;
    std::map<std::string, Animation> animations; //to keep track of my sprite animations

    unsigned int animationIndex = 0;
    bool hasCollisionAnimation;

    // Tracker for temporary anims
    float timeTracker = 0;


public:
    std::string currentAnimationName;
    bool collisionAnimPlaying = false;
    SDL_Rect sourceRectangle;
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    SpriteComponent(std::string assetTextureId) {
        this->isAnimated = false;
        this->isFixed = false;
        SetTexture(assetTextureId);
    }

    SpriteComponent(std::string assetTextureId, bool isFixed) {
        this->isAnimated = false;
        this->isFixed = isFixed;
        this->hasCollisionAnimation = false;
        SetTexture(assetTextureId);
    }

    SpriteComponent(std::string id, int numFrames, int animationSpeed, bool hasDirections, bool isFixed, bool isAnimatedWhileNotMoving, bool hasCollisionAnim){
        this->isAnimated = true;
        this->hasCollisionAnimation = hasCollisionAnim;
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

    ~SpriteComponent()
    {
        if (transform != nullptr)
        {
            delete transform;
        }
        SDL_DestroyTexture(texture);
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
        if (owner->HasComponent<ColliderComponent>() && hasCollisionAnimation)
        {
            int animsCount = animations.size();
            Animation collisionAnimStill = Animation(animsCount, numFrames, animationSpeed);
            animations.emplace("CollisionAnimStill", collisionAnimStill);
            Animation collisionAnimMoving = Animation(animsCount + 1, numFrames, animationSpeed);
            animations.emplace("CollisionAnimMoving", collisionAnimMoving);
        }
    }

    void Update(float deltaTime) override {

        if (!Game::suspendMovement)
        {
            // If the entity is moving and is animated, animate (flips between frames)
            // If the entity is NOT moving but is animated while not moving, animate
            if ((owner->IsMoving && isAnimated) || (!owner->IsMoving && isAnimatedWhileNotMoving))
            {
                if (animationSpeed !=0 && numFrames != 0)
                {
                    sourceRectangle.x = sourceRectangle.w * static_cast<int>((SDL_GetTicks()/animationSpeed)%numFrames);
                }
            }

            sourceRectangle.y = animationIndex * transform->height;
            destinationRectangle.x = static_cast<int>(transform->position.x) - (isFixed ? 0 :  Game::camera.x);
            destinationRectangle.y = static_cast<int>(transform->position.y) - (isFixed ? 0 :  Game::camera.y);
            destinationRectangle.w = transform->width * transform->scale;
            destinationRectangle.h = transform->height * transform->scale;
        }

        if (collisionAnimPlaying)
        {
            timeTracker += deltaTime;
            if (timeTracker >= 5)
            {
                //EndSquashedAnimation();
                timeTracker = 0;
                collisionAnimPlaying = false;
            }
        }

    }

    //with collision anim I could have a rule for now that if collision anim and collision result is 'squash'
    //then the collision sprite heigh is always half of the regular height
    // and the width is always double??
    // regular-width = 64
    // regular-height = 128
    //collision-wdith = 128
    // collision-height = 64
    // frames are half of regular frames for npw


    void Render() override {
        TextureManager::Draw(texture, sourceRectangle, destinationRectangle, spriteFlip, Game::renderer);
    }

};

#endif