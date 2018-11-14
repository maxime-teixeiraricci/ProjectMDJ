#include "collider.h"
#include <iostream>

Collider::Collider()
{

}

Collider::Collider(Mesh3D *m)
{
    mesh = m;
}

bool Collider::IsCollide(Collider *target)
{
    if (SphereCollide(target))
    {
        if (BBCollide(target))
        {
            return kdopCollide(target);
        }
    }
    return false;
}

bool Collider::SphereCollide(Collider *target)
{

    return mesh->sphereBoundDistance + target->mesh->sphereBoundDistance > (mesh->origin - target->mesh->origin).length();
}

bool Collider::BBCollide(Collider *target)
{

    if (target->mesh->max.z() > mesh->max.z() && mesh->max.z() < target->mesh->min.z()) return false;
    if (target->mesh->max.z() < mesh->max.z() && target->mesh->max.z() < mesh->min.z()) return false;

    if (target->mesh->max.y() > mesh->max.y() && mesh->max.y() < target->mesh->min.y()) return false;
    if (target->mesh->max.y() < mesh->max.y() && target->mesh->max.y() < mesh->min.y()) return false;

    if (target->mesh->max.x() > mesh->max.x() && mesh->max.x() < target->mesh->min.x()) return false;
    if (target->mesh->max.x() < mesh->max.x() && target->mesh->max.x() < mesh->min.x()) return false;
    return true;
}

bool Collider::OBBCollide(Collider *target)
{
    return true;
}

bool Collider::kdopCollide(Collider *target)
{
    mesh->KDopCompute();
    target->mesh->KDopCompute();
    for (unsigned int i = 0; i < mesh->kdopMax.size(); i ++)
    {
        float Ax = mesh->kdopMax.at(i);
        float An = mesh->kdopMin.at(i);
        float Bx = target->mesh->kdopMax.at(i);
        float Bn = target->mesh->kdopMin.at(i);
        if (Ax > Bx && Bx < An) return false;
        if (Bx > Ax && Ax < Bn) return false;
    }
    return true;
}

Mesh3D Collider::SphereCollider()
{
    Mesh3D m;
    m.Load("C:/Users/Maxime/Documents/ProjectMDJ/sphere.obj");
    m.Scale(mesh->sphereBoundDistance );
    m.Translate(mesh->center);
    return m;
}

bool Collider::isColliding(std::vector<Collider *> colliders)
{
    for (unsigned int i =0; i < colliders.size(); i++)
    {
        if (this != colliders[i])
        {
            if (IsCollide(colliders[i])) return true;
        }
    }
    return false;
}
