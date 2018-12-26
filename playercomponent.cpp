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
    float dx = InputMapping::inputMap["VerticalAxis"];   // Déplacement vertical
    float dy = InputMapping::inputMap["HorizontalAxis"]; // Déplacement horizontal
    QVector3D moveVect(dx, dy, 0);
    //gameObject->transform->position += moveVect;
    gameObject->collider->Move(moveVect * MainWidget::deltaTime * 10);
}

