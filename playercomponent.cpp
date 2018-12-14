#include "playercomponent.h"
#include "mainwidget.h"

PlayerComponent::PlayerComponent()
{

}

void PlayerComponent::Do()
{
    //double dT = MainWidget::deltaTime;
    /*QVector3D pos = gameObject->transform->GetPosition();
    pos = pos - QVector3D(0,0,-9) * dT;
    gameObject->transform->SetPosition(pos);*/
    Move();
}

void PlayerComponent::Move()
{
    float dy = (input->inputMap["up"] - input->inputMap["down"]);
    float dx = (input->inputMap["right"] - input->inputMap["left"]);
    std::cout << "Vect : " << dx << ", " << dy << std::endl;
    QVector3D moveVect(dx, dy, 0);
    QVector3D pos = gameObject->transform->GetPosition();
    //pos = pos + moveVect;
    gameObject->SetPosition(pos);
    input->printMap();
    //gameObject->transform->SetPosition(pos);
}
