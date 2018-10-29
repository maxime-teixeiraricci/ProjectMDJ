#ifndef COLLIDER_H
#define COLLIDER_H

#include "mesh.h"

class Collider
{
public:
    Mesh3D mesh;
    Collider(Mesh3D m);
    bool IsCollide(Collider target);
    bool SphereCollide(Collider target);
    bool BBCollide(Collider target);
    bool OBBCollide(Collider target);
    Mesh3D SphereCollider();
};

#endif // COLLIDER_H
