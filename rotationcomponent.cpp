#include "rotationcomponent.h"


RotationComponent::RotationComponent()
{

}

void RotationComponent::Do()
{
    gameObject->transform->eulerAngle += QVector3D(0,0,1);
    gameObject->transform->rotation = QQuaternion::fromEulerAngles(gameObject->transform->eulerAngle);
    gameObject->mesh->Compute(gameObject->transform);
}
