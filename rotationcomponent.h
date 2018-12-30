#ifndef ROTATIONCOMPONENT_H
#define ROTATIONCOMPONENT_H
#include "gameobject.h"

class RotationComponent: public Component
{
public:
    RotationComponent();
    void Do();
    GameObject *gameObject;
};

#endif // ROTATIONCOMPONENT_H
