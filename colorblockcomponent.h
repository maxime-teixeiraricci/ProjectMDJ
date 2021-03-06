#ifndef COLORBLOCKCOMPONENT_H
#define COLORBLOCKCOMPONENT_H
#include "component.h"
#include "vector"
#include "mesh.h"
#include "gameobject.h"

class ColorBlockComponent: public Component
{
public:
    ColorBlockComponent();
    void Do();
    void Change();
    GameObject* gameObject;
    bool startState;
};

#endif // COLORBLOCKCOMPONENT_H
