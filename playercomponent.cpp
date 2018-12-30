#include "playercomponent.h"
#include "mainwidget.h"

PlayerComponent::PlayerComponent()
{

}

void PlayerComponent::Do()
{
   Move();
}

void PlayerComponent::Move()
{
    // On va tester si le mouvement rentre en collision ou pas
    float dx = -GravityComponent::GetDirection() *InputMapping::inputMap["VerticalAxis"];   // Déplacement vertical
    float dy =  InputMapping::inputMap["HorizontalAxis"]; // Déplacement horizontal

    QVector3D forward = QVector3D(Mesh3D::vectorCamera.x(), Mesh3D::vectorCamera.y(), 0).normalized();
    QVector3D right = QVector3D::crossProduct(forward, QVector3D(0,0,1));

    QVector3D v = forward * dy + right * dx;
    gameObject->collider->Move(v * MainWidget::deltaTime * 25);
}

