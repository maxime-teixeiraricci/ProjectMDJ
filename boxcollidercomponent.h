#ifndef BOXCOLLIDERCOMPONENT_H
#define BOXCOLLIDERCOMPONENT_H

#include "mainwidget.h"
#include "collidercomponent.h"
#include "QVector3D"
#include "gameobject.h"

class BoxColliderComponent: public ColliderComponent
{
public:
    BoxColliderComponent();
    bool Collide(BoxColliderComponent *collider);
    //bool Collide(ColliderComponent *collider);
    void Move(QVector3D moveVect);
    void Teleport(QVector3D pos);
    GameObject *gameObject;

    QVector3D center;
    QVector3D size;


};

#endif // BOXCOLLIDERCOMPONENT_H
