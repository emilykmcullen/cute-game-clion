#include "./EntityManager.h"
#include <iostream>
#include "./Components/ColliderComponent.h"
#include "./Components/InteractionComponent.h"

void EntityManager::ClearData(){
    for (auto& entity: entities){
        //entity->Destroy();
        delete entity;
    }
    entities.clear();
    entities.shrink_to_fit();
}

bool EntityManager::HasNoEntities(){
    return entities.size()==0;
}

void EntityManager::Update(float deltaTime){
    for (auto& entity: entities){
        entity->CalculateColliderNextPosition(deltaTime);
    }

    // if there is going to be a collision, do appropriate actions
    CheckPlayerCollisions();

    for (auto& entity: entities){
        entity->Update(deltaTime);
    }
    DestroyInactiveEntities();
}

void EntityManager::DestroyInactiveEntities() {
    for (int i = 0; i < entities.size(); i++) {
        if (!entities[i]->IsActive()) {
            entities.erase(entities.begin() + i);
        }
    }
}

void EntityManager::Render(){
    for (int layerNumber = 0; layerNumber < NUM_LAYERS; layerNumber ++){
        for (auto& entity: GetEntitiesByLayer(static_cast<LayerType>(layerNumber))){
            entity->Render();
        }
    }
}

Entity& EntityManager::AddEntity(std::string entityName, LayerType layer){
    Entity *entity = new Entity(*this, entityName, layer);
    entities.emplace_back(entity);
    return *entity;
}

void EntityManager::ListAllEntities() const {
    unsigned int i = 0;
    for(auto& entity: entities){
        std::cout<< "Entity Name[" << i << "]" << entity->name << std::endl;
        entity->ListAllComponents();
        i++;
    }
}

std::vector<Entity*> EntityManager::GetEntities() const {
    return entities;
}

Entity* EntityManager::GetEntityByName(std::string entityName) const {
    for (auto* entity: entities) {
        if (entity->name.compare(entityName) == 0) {
            return entity;
        }
    }
    return NULL;
}

std::vector<Entity*> EntityManager::GetNonTileEntities() const {
    std::vector<Entity*> selectedEntities;
    for (auto& entity: entities){
        if (entity->layer != 0){
            selectedEntities.emplace_back(entity);
        }
    }
    return selectedEntities;
}

//void EntityManager::SetNonTileEntities() {
//    for (auto& entity: entities){
//        if (entity->layer != 0){
//            nonTileEntities.emplace_back(entity);
//        }
//    }
//}

std::vector<Entity*> EntityManager::GetEntitiesByLayer(LayerType layer) const {
    std::vector<Entity*> selectedEntities;
    for (auto& entity: entities){
        if (entity->layer == layer){
            selectedEntities.emplace_back(entity);
        }
    }
    return selectedEntities;
}

unsigned int EntityManager::GetEntityCount(){
    return entities.size();
}

CollisionType EntityManager::CheckPlayerCollisions() const {
    Entity* thisEntity = GetEntityByName("player");
    //check current entity has collider component
    ColliderComponent* thisCollider = thisEntity->GetComponent<ColliderComponent>();
    for (int j = 0; j < entities.size(); j++) {
        //only check entities that are AFTER the current one (eg. 'to the right' of the current entity)
        //do not need to check entities before current entity as this combination will have already been check
        auto& thatEntity = entities[j];
        if (thisEntity->name.compare(thatEntity->name) != 0 && thatEntity->HasComponent<ColliderComponent>()) {
            ColliderComponent* thatCollider = thatEntity->GetComponent<ColliderComponent>();
            if (Collision::CheckRectangleCollision(thisCollider->nextPosCollider, thatCollider->nextPosCollider)) {
                if (thisCollider->colliderTag.compare("PLAYER") == 0 && thatCollider->colliderTag.compare("NPC") == 0) {
                    thisEntity->resetPosition = true;
                    return PLAYER_NPC_COLLISION;
                }
                if (thisCollider->colliderTag.compare("PLAYER") == 0 && thatCollider->colliderTag.compare("LEVEL_COMPLETE") == 0) {
                    return PLAYER_LEVEL_COMPLETE_COLLISION;
                }
                if (thisCollider->colliderTag.compare("PLAYER") == 0 && thatCollider->colliderTag.compare("OBSTACLE") == 0) {
                    thisEntity->resetPosition = true;
                    return PLAYER_OBSTACLE_COLLISION;
                }
            }
        }
    }
    return NO_COLLISION;
}


interaction EntityManager::CheckIfClickedOnEntity(Sint32 x, Sint32 y)
{
    std::vector<Entity*> nonTileEntities = GetNonTileEntities();
    for (int i = 0; i < nonTileEntities.size(); i++)
    {
        Entity* entity = nonTileEntities[i];



        if (entity->HasComponent<ColliderComponent>() && entity->HasComponent<InteractionComponent>())
        {
            ColliderComponent* colliderComponent = entity->GetComponent<ColliderComponent>();
            // Check if click is in bounds of collider
            if (x > colliderComponent->destinationRectangle.x &&
                x < colliderComponent->destinationRectangle.x + (colliderComponent->destinationRectangle.w * colliderComponent->transform->scale) &&
                y > colliderComponent->destinationRectangle.y &&
                y < colliderComponent->destinationRectangle.y + (colliderComponent->destinationRectangle.h * colliderComponent->transform->scale))
            {
                InteractionComponent* interactionComponent = entity->GetComponent<InteractionComponent>();
                return interactionComponent->GetInteraction();
            }
        }
    }
    interaction fallbackInteraction { InteractionType::NO_INTERACTION, -1};
    return fallbackInteraction;
}