#ifndef GRAVITYCONPONENT_H
#define GRAVITYCONPONENT_H
#include "component.h"
#include "gameobject.h"
#include "inputmapping.h"

class GravityComponent: public Component
{
public:
    GravityComponent();
    void Do();
    GameObject *gameObject;
    static QVector3D gravity;
};

#endif // GRAVITYCONPONENT_H
