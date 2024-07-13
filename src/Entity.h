//
// Created by Emily Cullen on 22/10/2022.
//

#ifndef ENTITY_H
#define ENTITY_H

#include<vector>
#include<string>
#include <map>
#include <typeinfo>

#include "./Component.h"
#include "./Constants.h"


class Component;
class EntityManager;
union SDL_Event;

class Entity {
private:
    EntityManager& manager;
    bool isActive;
    std::vector<Component*> components;
    std::map<const std::type_info*, Component*> componentTypeMap;
public:
    std::string name;
    LayerType layer;
    Entity(EntityManager& manager);
    Entity(EntityManager& manager, std::string name, LayerType layer, bool isActive);
    void Update(float deltaTime);
    bool HandleEvent(SDL_Event &event);
    void Render();
    void Destroy();
    bool IsActive() const;
    void Activate(){ isActive = true; }
    void Deactivate(){ isActive = false; }
    void ListAllComponents() const;
    void CalculateColliderNextPosition(float deltaTime);

    bool IsMoving = false;
    // when there has been a collision
    bool resetPosition = false;

    template<typename T>
    bool HasComponent() const{
        return componentTypeMap.count(&typeid(T));
    }

    template <typename T, typename... TArgs>
    T& AddComponent(TArgs&&... args){
        T* newComponent(new T(std::forward<TArgs>(args)...));

        newComponent->owner = this;
        components.emplace_back(newComponent);
        componentTypeMap[&typeid(*newComponent)] = newComponent;
        newComponent->Initialize();
        return *newComponent;
    }

    template <typename T>
    T* GetComponent(){
        return static_cast<T*>(componentTypeMap[&typeid(T)]);
    }

};

#endif
