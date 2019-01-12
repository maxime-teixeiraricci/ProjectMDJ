#include "colorblockcomponent.h"
#include "switchcomponent.h"

ColorBlockComponent::ColorBlockComponent()
{

}

void ColorBlockComponent::Do()
{
    bool S = SwitchComponent::activate ^ startState;
    gameObject->collider->isTrigger = !S;
    if (!S) // Solide
    {
        gameObject->meshId = (startState)?2:4;
        /*gameObject->mesh = meshes[S];

        gameObject->mesh->Compute(gameObject->transform);
        */
    }
    else // Non Solide
    {
        gameObject->meshId = (startState)?3:5;
        /*gameObject->mesh = meshes[S];
        gameObject->collider->isTrigger = !S;
        gameObject->mesh->Compute(gameObject->transform);*/
    }
}

