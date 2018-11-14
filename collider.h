#ifndef COLLIDER_H
#define COLLIDER_H


#include "mesh.h"

class Collider
{
public:
    Collider();
    Collider(Mesh3D *m);
    bool IsCollide(Collider *target);
    bool SphereCollide(Collider *target);
    bool BBCollide(Collider *target);
    bool OBBCollide(Collider *target);
    bool kdopCollide(Collider *target);
    Mesh3D SphereCollider();
    bool isColliding(std::vector<Collider *> gameObjects);
    Mesh3D* mesh;
};

#endif // COLLIDER_H
