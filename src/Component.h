//
// Created by Emily Cullen on 22/10/2022.
//
#ifndef COMPONENT_H
#define COMPONENT_H

class Entity;

class Component {
public:
    Entity* owner;
    virtual ~Component(){};
    virtual void Initialize(){};
    virtual void Update(float deltaTime){};
    virtual void Render(){};
    bool isActive = true;
};

#endif

