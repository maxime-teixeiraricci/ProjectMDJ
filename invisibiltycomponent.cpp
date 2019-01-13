#include "invisibiltycomponent.h"
#include "mainwidget.h"
#include "meshrenderer.h"
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
    //if (gameObject->meshInstanceId>-1) MeshRenderer::instance->transitions[gameObject->meshId][gameObject->meshInstanceId] = gameObject->transform->transformMatrix;
    MeshRenderer::instance->DrawSingle(gameObject);
}
