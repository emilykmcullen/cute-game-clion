//
// Created by Emily Cullen on 27/10/2022.
//

#ifndef SDL2_BASIC_SETUP_INTERACTIONCOMPONENT_H
#define SDL2_BASIC_SETUP_INTERACTIONCOMPONENT_H
#include "../Component.h"
#include "../Map.h"
#include "../Utils.h"

class InteractionComponent : public Component
{
public:
    interaction interactionobj;

    InteractionComponent(InteractionType interaction, int level)
    {
        this->interactionobj.interactionType = interaction;
        this->interactionobj.info = level;
    }

    InteractionComponent(InteractionType interaction)
    {
        this->interactionobj.interactionType = interaction;
        this->interactionobj.info = -1;
    }

    interaction GetInteraction() const { return interactionobj; }
};

#endif //SDL2_BASIC_SETUP_INTERACTIONCOMPONENT_H
