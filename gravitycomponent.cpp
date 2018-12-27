#include "gravitycomponent.h"
#include "mainwidget.h"

QVector3D GravityComponent::gravity = QVector3D(0,0,-9.8);
GravityComponent::GravityComponent()
{
    //gravity = QVector3D(0,0,-9.0);
}

void GravityComponent::Do()
{
    QVector3D v = GravityComponent::gravity * MainWidget::deltaTime;
    //std::cout << "[" << v.x() << ", " << v.y() << ", " << v.z() << "]" << std::endl;
    //gameObject->transform->position += QVector3D(0,0,0) * MainWidget::deltaTime ;
    gameObject->collider->Move(v);

}
