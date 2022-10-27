//
// Created by Emily Cullen on 27/10/2022.
//

#ifndef SDL2_BASIC_SETUP_MOVEMENTSCHEDULECOMPONENT_H
#define SDL2_BASIC_SETUP_MOVEMENTSCHEDULECOMPONENT_H
#include <vector>
#include "../Utils.h"
#include "../Component.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

class MovementScheduleComponent : public Component
{
public:
    std::vector<vec2> destinations;
    int timeAtDestination;
    int indexOfCurrentDestination;
    vec2 currentDestination;

    float timeTracker = 0;
    bool atDestination = true;
    TransformComponent* transform;
    SpriteComponent* sprite;

    MovementScheduleComponent(std::vector<vec2> destinations, int timeAtDestinations) : destinations(destinations), timeAtDestination(timeAtDestinations)
    {
        // First destination is usually their starting position
        if (destinations.size() != 0)
        {
            indexOfCurrentDestination = 0;
            currentDestination = destinations.at(0);
        }
        else
        {
            std::cout << "MovementScheduleComponent::destinations is empty";
        }
    }

    void Initialize() override
    {
        transform = owner->GetComponent<TransformComponent>();
        sprite = owner->GetComponent<SpriteComponent>();
    }

    void Update(float deltaTime) override
    {
        if (atDestination)
        {
            timeTracker += deltaTime;
        }

        // We have been at the destination for enough time
        if (timeTracker >= timeAtDestination)
        {
            atDestination = false;
            timeTracker = 0;

            // Get next destination index
            if ((indexOfCurrentDestination + 1) < destinations.size())
            {
                indexOfCurrentDestination += 1;
            }
            else
            {
                // Reset back to the start destination
                indexOfCurrentDestination = 0;
            }
            // Set next destination
            currentDestination = destinations.at(indexOfCurrentDestination);
        }

        if (!atDestination)
        {
            // Update the x/y direction velocity to move towards the destination
            vec2 moveDirection = { currentDestination.x - transform->position.x, currentDestination.y - transform->position.y};
            NormalizeVector(moveDirection);
            transform->velocity.x = (moveDirection.x * 100);
            transform->velocity.y = (moveDirection.y * 100);
            // NEED TO CALCULATE WHICH SPRITE ANIMATION TO PLAY HERE
            owner->IsMoving = true;
            if (moveDirection.x > 0)
            {
                sprite->Play("RightAnimation");
            }
            else if (moveDirection.x < 0)
            {
                sprite->Play("LeftAnimation");
            }
            else if (moveDirection.y > 0)
            {
                sprite->Play("DownAnimation");
            }
            else if (moveDirection.y < 0)
            {
                sprite->Play("UpAnimation");
            }
            // Have we reached the destination (or within +/-2 units of it)?
            if (ReachedDestination(100))
            {
                atDestination = true;
                owner->IsMoving = false;
                timeTracker = 0;
                transform->velocity.x = 0;
                transform->velocity.y = 0;
                sprite->Play("DownAnimation"); //temporary - need to add an animation for standing still
            }
        }

    }

    void Render() override
    {

    }

    bool ReachedDestination(int allowance)
    {
        return (transform->position.x > currentDestination.x - allowance &&
                transform->position.x < currentDestination.x + allowance &&
                transform->position.y > currentDestination.y - allowance &&
                transform->position.y < currentDestination.y + allowance);
    }

};


#endif //SDL2_BASIC_SETUP_MOVEMENTSCHEDULECOMPONENT_H
