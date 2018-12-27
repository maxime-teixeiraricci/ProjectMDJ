#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include "component.h"
#include <iostream>
#include "QVector3D"

class GameObject;

class ColliderComponent : public Component
{
public:
    ColliderComponent();
    virtual bool Collide(ColliderComponent *collider)
    {
        std::cout << "A" << std::endl;
        return false;
    }
    virtual void Move(QVector3D moveVect)
    {
        std::cout << "B" << std::endl;
    }
    virtual void Teleport(QVector3D pos)
    {
        std::cout << "B" << std::endl;
    }
};

#endif // COLLIDERCOMPONENT_H
