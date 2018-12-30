#ifndef SWITCHCOMPONENT_H
#define SWITCHCOMPONENT_H
#include "component.h"
#include "gameobject.h"

class SwitchComponent: public Component
{
public:
    SwitchComponent();
    void Do();
    static bool activate;
    void ChangeColor();
    bool startState;
    GameObject *gameObject;
};

#endif // SWITCHCOMPONENT_H
