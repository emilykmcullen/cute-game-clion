#pragma once

#include "../Game.h"
#include "../EntityManager.h"
#include "./TransformComponent.h"
#include <SDL.h>

class ColliderComponent: public Component {
public:
    std::string colliderTag;
    SDL_Rect collider; //of the entity
    SDL_Rect sourceRectangle;
    SDL_Rect destinationRectangle;
    TransformComponent* transform = nullptr;
    SDL_Rect nextPosCollider;


    ColliderComponent(std::string colliderTag, int x, int y, int width, int height) {
        this->colliderTag = colliderTag;
        this->collider = {x , y , width, height};
        this->nextPosCollider = collider;
    }

    ~ColliderComponent()
    {
        if (transform)
        {
            delete transform;
        }
    }

    void Initialize() override {
        //get and set the transform, only IF the entity has a transform component
        if (owner->HasComponent<TransformComponent>()){
            transform = owner->GetComponent<TransformComponent>();
            sourceRectangle = {0, 0, transform->width, transform->height};
            destinationRectangle = {collider.x, collider.y, collider.w, collider.h};
            this->nextPosCollider = collider;
        }
    }

    void Update(float deltaTime) override {
//        collider.x = static_cast<int>(transform->position.x) - Game::camera.x;
//        collider.y = static_cast<int>(transform->position.y) - Game::camera.y;
//        collider.w = transform->width * transform->scale;
//        collider.h = transform->height * transform->scale;
//        nextPosCollider = collider;

        //--ORIGINAL--
        collider.x = static_cast<int>(transform->position.x);
        collider.y = static_cast<int>(transform->position.y);
        collider.w = transform->width * transform->scale;
        collider.h = transform->height * transform->scale;
        destinationRectangle.x = collider.x - Game::camera.x;
        destinationRectangle.y = collider.y - Game::camera.y;
        this->nextPosCollider = collider;
    }


    //just used for viewing the bounding boxes, can be removed later
     void Render() override {
         //SDL_SetRenderDrawColor(Game::renderer, 255,0,0,255);
         //SDL_RenderDrawRect(Game::renderer, &sourceRectangle);
         //SDL_RenderDrawRect(Game::renderer, &collider);
         //SDL_RenderDrawRect(Game::renderer, &nextPosCollider);
        //SDL_RenderDrawRect(Game::renderer,&Game::camera);

     }
};