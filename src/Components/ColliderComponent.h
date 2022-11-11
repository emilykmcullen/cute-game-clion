#pragma once

#include "../Game.h"
#include "../EntityManager.h"
#include "./TransformComponent.h"
#include <SDL.h>

class ColliderComponent: public Component {
public:
    std::string colliderTag;
    SDL_Rect collider; //of the entity
    TransformComponent* transform = nullptr;
    SDL_Rect nextPosCollider;
    int xOffset = 0;
    int yOffset = 0;


    ColliderComponent(std::string colliderTag, int x, int y, int width, int height, int scale) {
        int newWidth = width * scale;
        int newHeight = height * scale;
        this->colliderTag = colliderTag;
        this->collider = {x , y , newWidth, newHeight};
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
            xOffset = collider.x - transform->position.x;
            yOffset = collider.y - transform->position.y;
        }
    }

    void Update(float deltaTime) override {


        collider.x = static_cast<int>(transform->position.x) + xOffset;
        collider.y = static_cast<int>(transform->position.y) + yOffset;
        this->nextPosCollider = collider;

    }


    //just used for viewing the bounding boxes, can be removed later
     void Render() override {
         SDL_SetRenderDrawColor(Game::renderer, 255,0,0,255);
         //SDL_RenderDrawRect(Game::renderer, &sourceRectangle);
         SDL_RenderDrawRect(Game::renderer, &collider);
        //SDL_RenderDrawRect(Game::renderer, &destinationRectangle);
         //SDL_RenderDrawRect(Game::renderer, &nextPosCollider);
         //SDL_RenderDrawRect(Game::renderer,&Game::camera);

     }
};