#include "rotationcomponent.h"
#include "meshrenderer.h"
#include "mainwidget.h"

RotationComponent::RotationComponent()
{

}

void RotationComponent::Do()
{
    gameObject->transform->eulerAngle += QVector3D(0,0,90) * MainWidget::deltaTime;
    gameObject->transform->rotation = QQuaternion::fromEulerAngles(gameObject->transform->eulerAngle);
}
