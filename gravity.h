#ifndef GRAVITY_H
#define GRAVITY_H
#include "QVector3D"
#include "gameobject.h"

class Gravity
{
public:
    Gravity();
    void ApplyGravity(GameObject *gameObject);
    QVector3D gravity;
};

#endif // GRAVITY_H
