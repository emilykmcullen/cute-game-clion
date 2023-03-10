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
    bool updateAnimation = false;
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

    ~MovementScheduleComponent()
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

    void Initialize() override
    {
        transform = owner->GetComponent<TransformComponent>();
        sprite = owner->GetComponent<SpriteComponent>();
    }

    void Update(float deltaTime) override
    {
        // if we are an enemy, we also need to check if we're close to the player
        // if so we come off our regular schedule and move towards the player instead d
        if (atDestination)
        {
            timeTracker += deltaTime;
        }

        if (!Game::suspendMovement)
        {
            // We have been at the destination for enough time, start to move to next destination
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
                float absX = abs(moveDirection.x);
                float absY = abs(moveDirection.y);

                //TEMP
                if (!sprite->collisionAnimPlaying)
                {
                    if (absX > absY || absX > 0.5 ) // if X dir is bigger than Y direction, OR if X direction is actually just high (more than 0.5 for now)
                    {
                        if (moveDirection.x >= 0)
                        {

                            sprite->Play("RightAnimation");
                        }
                        else
                        {
                            sprite->Play("LeftAnimation");
                        }
                    }
                    else
                    {
                        if (moveDirection.y >= 0)
                        {
                            sprite->Play("DownAnimation");
                        }
                        else
                        {
                            sprite->Play("UpAnimation");
                        }
                    }
                }
                else
                {
                    sprite->Play("CollisionAnimMoving");
                }


                // Have we reached the destination (or within +/- units of it)?
                if (ReachedDestination(4))
                {
                    atDestination = true;
                    owner->IsMoving = false;
                    timeTracker = 0;

                    //TEMP TO DO
                    if (!sprite->collisionAnimPlaying)
                    {
                        if (transform->velocity.y > 0 && (abs(transform->velocity.y) > abs(transform->velocity.x)))
                        {
                            sprite->Play("DownStationary");
                        }
                        else if (transform->velocity.y < 0 && (abs(transform->velocity.y) > abs(transform->velocity.x)))
                        {
                            sprite->Play("UpStationary");
                        }
                        else if (transform->velocity.x < 0)
                        {
                            sprite->Play("LeftStationary");
                        }
                        else
                        {
                            sprite->Play("RightStationary");
                        }
                    }
                    else
                    {
                        sprite->Play("CollisionAnimStill");
                    }
                    transform->velocity.x = 0;
                    transform->velocity.y = 0;
                }
            }
            // if we are at the destination the animation is not updated!!!
            // We are at the destination but maybe something else has happened that means the animation needs updating
            if (updateAnimation)
            {

                //TO DO : sort this out
                sprite->Play("CollisionAnimStill");
                updateAnimation = false;
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
