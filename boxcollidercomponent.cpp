#include "boxcollidercomponent.h"

BoxColliderComponent::BoxColliderComponent()
{

}


bool BoxColliderComponent::Collide(BoxColliderComponent *collider)
{
    float axn = center.x() - size.x();
    float axx = center.x() + size.x();
    float bxn = collider->center.x() - collider->size.x();
    float bxx = collider->center.x() + collider->size.x();

    bool A = ((axn <= bxn) && (bxn <= axx)) || ((bxn <= axn) && (axn <= bxx));

    float ayn = center.y() - size.y();
    float ayx = center.y() + size.y();
    float byn = collider->center.y() - collider->size.y();
    float byx = collider->center.y() + collider->size.y();

    bool B = ((ayn <= byn) && (byn <= ayx)) || ((byn <= ayn) && (ayn <= byx));

    float azn = center.z() - size.z();
    float azx = center.z() + size.z();
    float bzn = collider->center.z() - collider->size.z();
    float bzx = collider->center.z() + collider->size.z();

    bool C = ((azn <= bzn) && (bzn <= azx)) || ((bzn <= azn) && (azn <= bzx));
    return A && B && C;
}


void BoxColliderComponent::Move(QVector3D moveVect)
{

    QVector3D currentCenter = center;
    center += moveVect;
    for (unsigned int i = 0; i < gameObjects->size(); i++)
    {
        BoxColliderComponent *bc = static_cast<BoxColliderComponent*> (gameObjects->at(i)->collider);

        if ( Collide(bc) )
        {
            center = currentCenter;
            return;
        }
    }
    //center = currentCenter;
    gameObject->transform->position += moveVect;

}

void BoxColliderComponent::Teleport(QVector3D pos)
{
    QVector3D currentCenter = center;
    center = pos;
    for (unsigned int i = 0; i < gameObjects->size(); i++)
    {
        BoxColliderComponent *bc = static_cast<BoxColliderComponent*> (gameObjects->at(i)->collider);
        if ( Collide(bc) )
        {
            center = currentCenter;
            return;
        }
    }
    //center = currentCenter;
    gameObject->transform->position = pos;

}
