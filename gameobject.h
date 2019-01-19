#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <collider.h>
#include <iostream>
#include "mesh.h"
#include "transform.h"
#include "component.h"
#include "collidercomponent.h"
#include "QColor"

class GameObject
{
public:
    GameObject();

    void Destroy();

    Transform *transform;
    std::vector<Component *> components;
    ColliderComponent *collider = nullptr;
    int meshId = -1;
    int meshInstanceId = -1;
    bool isDrawable = true;
    GameObject* parent;
    std::vector<GameObject*> children;

};

#endif // GAMEOBJECT_H
