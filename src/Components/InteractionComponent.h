//
// Created by Emily Cullen on 27/10/2022.
//

#ifndef SDL2_BASIC_SETUP_INTERACTIONCOMPONENT_H
#define SDL2_BASIC_SETUP_INTERACTIONCOMPONENT_H
#include "../Component.h"
#include "../Map.h"
#include "../Utils.h"
#include "SDL.h"
#include "TransformComponent.h"

class InteractionComponent : public Component
{
public:
    interaction interactionobj;
    SDL_Rect interactionRect;
    TransformComponent* transform = nullptr;

    InteractionComponent(InteractionType interaction, std::string info, int x, int y, int width, int height)
    {
        this->interactionobj.interactionType = interaction;
        this->interactionobj.info = info;
        this->interactionRect = { x, y, width, height };
    }

    InteractionComponent(InteractionType interaction, std::string info)
    {
        this->interactionobj.interactionType = interaction;
        this->interactionobj.info = info;
    }

    ~InteractionComponent()
    {
    }

    interaction GetInteraction() const { return interactionobj; }

    void Initialize() override {
        //get and set the transform, only IF the entity has a transform component
        if (owner->HasComponent<TransformComponent>()){
            transform = owner->GetComponent<TransformComponent>();
        }
    }

    void Update(float deltaTime) override {
//        if (!specialSizeInteractionRect) {
//            interactionRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
//            interactionRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
//            interactionRect.w = transform->width * transform->scale;
//            interactionRect.h = transform->height * transform->scale;
//        }
            interactionRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
            interactionRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
            interactionRect.w = transform->width * transform->scale;
            interactionRect.h = transform->height * transform->scale;
    }

    //just used for viewing the bounding boxes, can be removed later
    void Render() override {
        SDL_SetRenderDrawColor(Game::renderer, 0,255,0,255);
        SDL_RenderDrawRect(Game::renderer, &interactionRect);
    }

};

#endif //SDL2_BASIC_SETUP_INTERACTIONCOMPONENT_H
