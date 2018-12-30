#ifndef INVISIBILTYCOMPONENT_H
#define INVISIBILTYCOMPONENT_H

#include "component.h"
#include "gameobject.h"

class InvisibiltyComponent: public Component
{
public:
    InvisibiltyComponent();
    void Do();
    GameObject *gameObject;
};

#endif // INVISIBILTYCOMPONENT_H
