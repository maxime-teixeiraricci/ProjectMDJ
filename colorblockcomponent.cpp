#include "colorblockcomponent.h"
#include "switchcomponent.h"

ColorBlockComponent::ColorBlockComponent()
{

}

void ColorBlockComponent::Do()
{
    bool S = SwitchComponent::activate ^ startState;
    if (S ) // Solide
    {
        gameObject->mesh = meshes[S];
        gameObject->collider->isTrigger = !S;
        gameObject->mesh->Compute(gameObject->transform);
    }
    else // Non Solide
    {
        gameObject->mesh = meshes[S];
        gameObject->collider->isTrigger = !S;
        gameObject->mesh->Compute(gameObject->transform);
    }
}

