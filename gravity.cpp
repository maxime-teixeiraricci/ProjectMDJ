#include "gravity.h"

Gravity::Gravity()
{

}

void Gravity::ApplyGravity(GameObject *gameObject)
{
    gameObject->SetPosition(gameObject->position + gravity * 0.15f);
}
