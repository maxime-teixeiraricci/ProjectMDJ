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
    double speed = 5.0;
    // On va tester si le mouvement rentre en collision ou pas
    double dx =  InputMapping::inputMap["VerticalAxis"] * (- GravityComponent::GetDirection());   // Déplacement vertical
    double dy =  InputMapping::inputMap["HorizontalAxis"]; // Déplacement horizontal

    QVector3D forward = QVector3D(Mesh3D::vectorCamera.x(), Mesh3D::vectorCamera.y(), 0).normalized();
    QVector3D right = QVector3D::crossProduct(forward, QVector3D(0,0,1));

    QVector3D v = forward * dy + right * dx;
    v.normalize();

    // Pour eviter des artefacts dans les déplacements liés à une chute de FrameRate
    double dt = std::min( (1/30.0) , MainWidget::deltaTime);
    QVector3D move = v * dt * 5;

    gameObject->collider->Move(QVector3D(move.x(),0,0));
    gameObject->collider->Move(QVector3D(0,move.y(),0));


}

