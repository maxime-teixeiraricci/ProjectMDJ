#include "collider.h"

Collider::Collider()
{

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
    return false
}

bool Collider::OBBCollide(Collider target)
{
    return false;
}
