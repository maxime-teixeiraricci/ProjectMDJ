#ifndef PLAYERCOMPONENT_H
#define PLAYERCOMPONENT_H
#include "component.h"
#include "gameobject.h"
#include "inputmapping.h"

class PlayerComponent: public Component
{
public:
    //static
    PlayerComponent();
    void Do();
    void Move();

    GameObject *gameObject;
};

#endif // PLAYERCOMPONENT_H
