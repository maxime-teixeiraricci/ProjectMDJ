#include "rotationcomponent.h"
#include "meshrenderer.h"

RotationComponent::RotationComponent()
{

}

void RotationComponent::Do()
{
    gameObject->transform->eulerAngle += QVector3D(0,0,5);
    gameObject->transform->rotation = QQuaternion::fromEulerAngles(gameObject->transform->eulerAngle);
    gameObject->transform->getMatrix();

    MeshRenderer::instance->DrawSingle(gameObject);
    //gameObject->mesh->Compute(gameObject->transform);
}
