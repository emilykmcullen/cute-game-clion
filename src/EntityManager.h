#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "./Entity.h"
#include "./Component.h"
#include "./Constants.h"
#include <vector>
#include "Collision.h"
#include "Map.h"
#include "Utils.h"

union SDL_Event;

class EntityManager {
private:
    std::vector<Entity*> entities;
    //std::vector<Entity*> nonTileEntities;
public:
    void ClearData();
    void Update(float deltaTime);
    void HandleEvent(SDL_Event &event);
    void Render();
    bool HasNoEntities();
    Entity& AddEntity(std::string entityName, LayerType layer, bool isActive);
    std::vector<Entity*> GetEntities() const;
    std::vector<Entity*> GetNonTileEntities() const;
    //void SetNonTileEntities();
    std::vector<Entity*> GetEntitiesByLayer(LayerType layer) const;
    Entity* GetEntityByName(std::string name) const;
    void CheckPlayerCollisions() const;
    void DestroyInactiveEntities();

    unsigned int GetEntityCount();
    void ListAllEntities() const;

    interaction CheckIfClickedOnEntity(Sint32 x, Sint32 y);
    CursorType IsCursorOverInteractionRect(Sint32 x, Sint32 y);

    void RearrangeObstacleLayers();


};

#endif