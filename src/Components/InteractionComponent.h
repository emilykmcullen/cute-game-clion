//
// Created by Emily Cullen on 27/10/2022.
//

#ifndef SDL2_BASIC_SETUP_INTERACTIONCOMPONENT_H
#define SDL2_BASIC_SETUP_INTERACTIONCOMPONENT_H
#include "../Component.h"
#include "../Map.h"
#include "../Utils.h"
#include "SDL.h"

class InteractionComponent : public Component
{
public:
    interaction interactionobj;
    SDL_Rect interactionRect;

    InteractionComponent(InteractionType interaction, int info)
    {
        this->interactionobj.interactionType = interaction;
        this->interactionobj.info = info;
    }

    InteractionComponent(InteractionType interaction)
    {
        this->interactionobj.interactionType = interaction;
        this->interactionobj.info = -1;
    }

    interaction GetInteraction() const { return interactionobj; }
};

#endif //SDL2_BASIC_SETUP_INTERACTIONCOMPONENT_H
