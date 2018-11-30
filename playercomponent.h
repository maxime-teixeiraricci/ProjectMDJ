#ifndef PLAYERCOMPONENT_H
#define PLAYERCOMPONENT_H
#include "component.h"
#include "gameobject.h"

class PlayerComponent: public Component
{
public:
    PlayerComponent();
    void Do();

    GameObject *gameObject;
};

#endif // PLAYERCOMPONENT_H
