#include "gravitycomponent.h"
#include "mainwidget.h"
#include <algorithm>    // std::min

QVector3D GravityComponent::gravity = QVector3D(0,0,-9.8);
GravityComponent::GravityComponent()
{
    //gravity = QVector3D(0,0,-9.0);
}

void GravityComponent::Do()
{
    // Pour eviter des artefacts dans les déplacements liés à une chute de FrameRate
    double dt = std::min((1/30.0) , MainWidget::deltaTime);

    QVector3D v = GravityComponent::gravity * dt * 5;
    //std::cout << "[" << v.x() << ", " << v.y() << ", " << v.z() << "]" << std::endl;
    //gameObject->transform->position += QVector3D(0,0,0) * MainWidget::deltaTime ;
    gameObject->collider->Move(v);
    gameObject->mesh->Compute(gameObject->transform);

}


