#include "colorblockcomponent.h"
#include "switchcomponent.h"
#include "meshrenderer.h"
#include "mapmaker.h"

ColorBlockComponent::ColorBlockComponent()
{

}

void ColorBlockComponent::Do()
{
    bool S = SwitchComponent::activate ^ startState;
    gameObject->collider->isTrigger = S;
    if (!S) // Solide
    {
        gameObject->meshId = (startState)? MeshID::FULL_BLOCK_BLUE : MeshID::FULL_BLOCK_RED;
    }
    else // Non Solide
    {
        gameObject->meshId = (startState)? MeshID::WIRED_BLOCK_BLUE : MeshID::WIRED_BLOCK_RED;
        /*gameObject->mesh = meshes[S];
        gameObject->collider->isTrigger = !S;
        gameObject->mesh->Compute(gameObject->transform);*/
    }


    //MeshRenderer::instance->DrawSingle(gameObject);
}

