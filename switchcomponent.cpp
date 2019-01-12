#include "switchcomponent.h"
#include "mainwidget.h"
#include "boxcollidercomponent.h"

bool SwitchComponent::activate = false;

SwitchComponent::SwitchComponent()
{

}

void SwitchComponent::Do()
{
    BoxColliderComponent *gbc = static_cast<BoxColliderComponent*> (gameObject->collider);
    BoxColliderComponent *pbc = static_cast<BoxColliderComponent*> (MainWidget::playerObject->collider);

    if (!SwitchComponent::activate^startState && pbc->Collide(gbc))
    {
        SwitchComponent::activate = !SwitchComponent::activate;

    }
    ChangeColor();

}

void SwitchComponent::ChangeColor()
{
    if (SwitchComponent::activate^startState)
    {
        gameObject->meshId = 6;
        //gameObject->mesh->LoadTexture("../ProjectMDJ/blackSwitch.png");
        //gameObject->mesh->color = QColor(50.0,50.0,50.0);
    }
    else
    {
        gameObject->meshId = 7;
        //gameObject->mesh->color = QColor(255.0,255.0,255.0);
    }
}
