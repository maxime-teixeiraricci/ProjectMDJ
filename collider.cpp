#include "collider.h"

Collider::Collider(Mesh3D m)
{
    mesh = m;
}

bool Collider::IsCollide(Collider target)
{
    if (SphereCollide(target))
        if (BBCollide(target))
            return OBBCollide(target);
    return false;
}

bool Collider::SphereCollide(Collider target)
{
    return mesh.sphereBoundDistance + target.mesh.sphereBoundDistance > (mesh.center - target.mesh.center).length();
}

bool Collider::BBCollide(Collider target)
{
    return !(
                (target.mesh.min.x() > mesh.max.x()) ||
                (target.mesh.min.y() > mesh.max.y()) ||
                (target.mesh.min.z() > mesh.max.z()) ||
                (target.mesh.max.x() < mesh.min.x()) ||
                (target.mesh.max.y() < mesh.min.y()) ||
                (target.mesh.max.z() < mesh.min.z())
            );
}

bool Collider::OBBCollide(Collider target)
{
    return true;
}

Mesh3D Collider::SphereCollider()
{
    Mesh3D m;
    m.Load("C:/Users/Maxime/Documents/ProjectMDJ/sphere.obj");
    m.Scale(mesh.sphereBoundDistance );
    m.Translate(mesh.center);
    return m;
}
