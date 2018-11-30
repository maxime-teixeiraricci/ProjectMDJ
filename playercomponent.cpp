#include "playercomponent.h"
#include "mainwidget.h"

PlayerComponent::PlayerComponent()
{

}

void PlayerComponent::Do()
{
    double dT = MainWidget::deltaTime;
    QVector3D pos = gameObject->transform->GetPosition();
    pos = pos - QVector3D(0,0,-9) * dT;
    gameObject->transform->SetPosition(pos);
}
