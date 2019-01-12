#include "invisibiltycomponent.h"
#include "mainwidget.h"
InvisibiltyComponent::InvisibiltyComponent()
{

}

void InvisibiltyComponent::Do()
{
    if ((MainWidget::playerObject->transform->position - gameObject->transform->position).length() > 4.0)
    {
        gameObject->isDrawable = false;
    }
    else
    {
        gameObject->isDrawable = true;
    }
}
