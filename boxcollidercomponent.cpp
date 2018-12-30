#include "boxcollidercomponent.h"
#include "QColor"

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
    for (unsigned int i = 0; i < MainWidget::gameObjects.size(); i++)
        {
            if (MainWidget::gameObjects.at(i) != gameObject &&
                    MainWidget::gameObjects.at(i)->collider != nullptr &&
                    !MainWidget::gameObjects.at(i)->collider->isTrigger)
            {
                BoxColliderComponent *bc = static_cast<BoxColliderComponent*> (MainWidget::gameObjects.at(i)->collider);
                if ( Collide(bc) )
                {
                    center = currentCenter;
                    Move(
                    0.95 * moveVect * QVector3D::dotProduct(moveVect.normalized(),
                        (MainWidget::gameObjects.at(i)->transform->position - gameObject->transform->position).normalized()));
                    return;
                }
            }

        }
        gameObject->transform->position += moveVect;

}

void BoxColliderComponent::Teleport(QVector3D pos)
{
    QVector3D currentCenter = center;
    center = pos;
    for (unsigned int i = 0; i < MainWidget::gameObjects.size(); i++)
    {
        if (MainWidget::gameObjects.at(i)->collider != nullptr)
        {
            BoxColliderComponent *bc = static_cast<BoxColliderComponent*> (MainWidget::gameObjects.at(i)->collider);
            if ( Collide(bc) )
            {
                center = currentCenter;
                return;
            }
        }
    }
    //center = currentCenter;
    gameObject->transform->position = pos;

}
