#include "./EntityManager.h"
#include <iostream>
#include "./Components/ColliderComponent.h"
#include "./Components/InteractionComponent.h"
#include "./Components/MovementScheduleComponent.h"

void EntityManager::ClearData(){
    for (auto& entity: entities){
        //entity->Destroy();
        if (entity != nullptr)
        {
            delete entity;
        }
    }
    entities.clear();
    entities.shrink_to_fit();
}

bool EntityManager::HasNoEntities(){
    return entities.size()==0;
}

void EntityManager::Update(float deltaTime){

    RearrangeObstacleLayers();

    for (auto& entity: entities){
        if (entity->IsActive())
        {
            entity->CalculateColliderNextPosition(deltaTime);
        }
    }

    // if there is going to be a collision, do appropriate actions
    CheckPlayerCollisions();

    for (auto& entity: entities){
        entity->Update(deltaTime);
    }
    //DestroyInactiveEntities();
}

//void EntityManager::DestroyInactiveEntities() {
//    for (int i = 0; i < entities.size(); i++) {
//        if (!entities[i]->IsActive()) {
//            entities.erase(entities.begin() + i);
//        }
//    }
//}

void EntityManager::HandleEvent(SDL_Event &event){
    for (int layerNumber = NUM_LAYERS - 1; layerNumber > 0; layerNumber --){
        for (auto& entity: GetEntitiesByLayer(static_cast<LayerType>(layerNumber))){
            if (entity->IsActive())
            {
                if (entity->HandleEvent(event)) {
                    return;
                }
            }
        }
    }
}

void EntityManager::Render(){
    for (int layerNumber = 0; layerNumber < NUM_LAYERS; layerNumber ++){
        for (auto& entity: GetEntitiesByLayer(static_cast<LayerType>(layerNumber))){
            if (entity->IsActive())
            {
                entity->Render();
            }
        }
    }
}

// So that we render the obstacles in the correct order depending on their position relative to the player
void EntityManager::RearrangeObstacleLayers()
{
    Entity* player = GetEntityByName("player");
    for (auto& entity: GetEntitiesByLayer(OBSTACLE_ONTOP_LAYER))
    {
        // If the player is below the obstacle, the obstacle should be behind the player
        if (player->GetComponent<TransformComponent>()->position.y > entity->GetComponent<TransformComponent>()->position.y)
        {
            entity->layer = OBSTACLE_LAYER;
        }
    }
    for (auto& entity: GetEntitiesByLayer(OBSTACLE_LAYER))
    {
        // If the player is above the obstacle, the obstacle should be infront of the player
        if (player->GetComponent<TransformComponent>()->position.y < entity->GetComponent<TransformComponent>()->position.y)
        {
            entity->layer = OBSTACLE_ONTOP_LAYER;
        }
    }
}

Entity& EntityManager::AddEntity(std::string entityName, LayerType layer, bool isActive){
    Entity *entity = new Entity(*this, entityName, layer, isActive);
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

//Check PRE-COLLISIONS!
void EntityManager::CheckPlayerCollisions() const {
    Entity* thisEntity = GetEntityByName("player");
    //check current entity has collider component
    ColliderComponent* thisCollider = thisEntity->GetComponent<ColliderComponent>();
    for (int j = 0; j < entities.size(); j++) {
        //only check entities that are AFTER the current one (eg. 'to the right' of the current entity)
        //do not need to check entities before current entity as this combination will have already been check
        auto& thatEntity = entities[j];
        if (thatEntity->IsActive())
        {
            if (thisEntity->name.compare(thatEntity->name) != 0 && thatEntity->HasComponent<ColliderComponent>()) {
                ColliderComponent* thatCollider = thatEntity->GetComponent<ColliderComponent>();
                // CHECK IF WE WILL COLLIDE IN THE NEXT FRAME
                if (Collision::CheckRectangleCollision(thisCollider->nextPosCollider, thatCollider->nextPosCollider)) {
                    if (thisCollider->colliderTag.compare("PLAYER") == 0 && thatCollider->colliderTag.compare("NPC") == 0) {
                        //reset player position to the previous frame position
                        if (thatCollider->resultOfCollision == "stopmovement")
                        {
                            thisEntity->resetPosition = true;
                        }
                        thatEntity->resetPosition = true;
                    }
                    if (thisCollider->colliderTag.compare("PLAYER") == 0 && thatCollider->colliderTag.compare("OBSTACLE") == 0) {
                        thisEntity->resetPosition = true;
                        thatEntity->resetPosition = true;
                    }
                }
                // CHECK CURRENT COLLISION
                if (Collision::CheckRectangleCollision(thisCollider->collider, thatCollider->collider)) {
                    if (thisCollider->colliderTag.compare("PLAYER") == 0 && thatCollider->colliderTag.compare("NPC") == 0) {
                        if (thatCollider->resultOfCollision == "squash")
                        {
                            SpriteComponent* thatSprite = thatEntity->GetComponent<SpriteComponent>();
                            MovementScheduleComponent* thatMS = thatEntity->GetComponent<MovementScheduleComponent>();
                            if (!thatSprite->collisionAnimPlaying)
                            {
                                thatSprite->collisionAnimPlaying = true;
                                thatMS->updateAnimation = true;
                            }
                        }
                    }
                }

            }
        }
    }
}



interaction EntityManager::CheckIfClickedOnEntity(Sint32 x, Sint32 y)
{
    Entity* trackedEntity = nullptr;
    std::vector<Entity*> nonTileEntities = GetNonTileEntities();
    for (int i = 0; i < nonTileEntities.size(); i++)
    {
        //TO DO: BETTER WAY TO DO THIS RATHER THAN GETTING THE NON-TILE ENTITIES EVERY FRAME?
        Entity* entity = nonTileEntities[i];
        if (entity->HasComponent<InteractionComponent>() && entity->IsActive())
        {
            InteractionComponent* interactionComponent = entity->GetComponent<InteractionComponent>();
            // Check if click is in bounds of collider
            if (x > interactionComponent->interactionRect.x &&
                x < interactionComponent->interactionRect.x + interactionComponent->interactionRect.w &&
                y > interactionComponent->interactionRect.y &&
                y < interactionComponent->interactionRect.y + interactionComponent->interactionRect.h)
            {
                Entity* player = GetEntityByName("player");
                TransformComponent* playerTransform = player->GetComponent<TransformComponent>();
                int playerX = (int)playerTransform->position.x - Game::camera.x;
                int playerY = (int)playerTransform->position.y - Game::camera.y;
                SDL_Rect playerRect = { playerX, playerY,  (int)playerTransform->width * (int)playerTransform->scale, (int)playerTransform->height * (int)playerTransform->scale };
                // Is the interactable entity near enough to the player?
                int clickAllowance = interactionComponent->clickAllowance;
                if (clickAllowance == -1 || Collision::CheckRectangleCollisionWithinAllowance(playerRect, interactionComponent->interactionRect, clickAllowance))
                {
                    if (trackedEntity == nullptr)
                    {
                        trackedEntity = entity;
                    }
                    else if (entity->IsActive() && static_cast<int>(entity->layer) > static_cast<int>(trackedEntity->layer))
                    {
                        trackedEntity = entity;
                    }
                }
            }
        }
    }
    if (trackedEntity == nullptr)
    {
        interaction fallbackInteraction { InteractionType::NO_INTERACTION, "0"};
        return fallbackInteraction;
    }
    else
    {
        InteractionComponent* interactionComponent = trackedEntity->GetComponent<InteractionComponent>();
        return interactionComponent->GetInteraction();
    }
}

CursorType EntityManager::IsCursorOverInteractionRect(Sint32 x, Sint32 y)
{
    std::vector<Entity*> nonTileEntities = GetNonTileEntities();
    for (int i = 0; i < nonTileEntities.size(); i++)
    {
        //TO DO: BETTER WAY TO DO THIS RATHER THAN GETTING THE NON-TILE ENTITIES EVERY FRAME?
        Entity* entity = nonTileEntities[i];
        if (entity->HasComponent<InteractionComponent>() && entity->IsActive())
        {
            InteractionComponent* interactionComponent = entity->GetComponent<InteractionComponent>();
            // Check if click is in bounds of collider
            if (x > interactionComponent->interactionRect.x &&
                x < interactionComponent->interactionRect.x + interactionComponent->interactionRect.w &&
                y > interactionComponent->interactionRect.y &&
                y < interactionComponent->interactionRect.y + interactionComponent->interactionRect.h)
            {
                Entity* player = GetEntityByName("player");
                TransformComponent* playerTransform = player->GetComponent<TransformComponent>();
                int playerX = (int)playerTransform->position.x - Game::camera.x;
                int playerY = (int)playerTransform->position.y - Game::camera.y;
                SDL_Rect playerRect = { playerX, playerY,  (int)playerTransform->width * (int)playerTransform->scale, (int)playerTransform->height * (int)playerTransform->scale };
                // Is the interactable entity near enough to the player?
                int clickAllowance = interactionComponent->clickAllowance;

                if (clickAllowance == -1 || Collision::CheckRectangleCollisionWithinAllowance(playerRect, interactionComponent->interactionRect, clickAllowance))
                {
                    return CursorType::LARGE;
                }
                return CursorType::LARGE_GREY;
            }
        }
    }
    return CursorType::REGULAR;
}