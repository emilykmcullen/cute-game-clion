//
// Created by Emily Cullen on 22/10/2022.
//
#ifndef COMPONENT_H
#define COMPONENT_H

class Entity;
union SDL_Event;

class Component {
public:
    Entity* owner;
    virtual ~Component(){};
    virtual void Initialize(){};
    virtual void Update(float deltaTime){};
    virtual bool HandleEvent(SDL_Event &event){return false;};
    virtual void Render(){};
    bool isActive = true;
};

#endif

