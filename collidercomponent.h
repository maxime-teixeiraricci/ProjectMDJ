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
        std::cout << "ColliderComponent : Collider Not Implement" << std::endl;
        return false;
    }
    virtual void Move(QVector3D moveVect)
    {
        std::cout << "ColliderComponent : Move Not Implement" << std::endl;
    }
    virtual void Teleport(QVector3D pos)
    {
         std::cout << "ColliderComponent : Teleport Not Implement" << std::endl;
    }

    bool isTrigger = false;
};

#endif // COLLIDERCOMPONENT_H
