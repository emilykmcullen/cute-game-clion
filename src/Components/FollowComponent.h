#pragma once

#include "../Game.h"
#include "../EntityManager.h"
#include "./TransformComponent.h"
#include <SDL.h>

class FollowComponent: public Component {
public:
    TransformComponent* transform = nullptr;



    FollowComponent() {

    }

    ~FollowComponent()
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
        }
    }

    void Update(float deltaTime) override {

    }

    void Render() override {
    }
};