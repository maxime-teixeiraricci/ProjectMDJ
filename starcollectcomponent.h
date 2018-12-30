#ifndef STARCOLLECTCOMPONENT_H
#define STARCOLLECTCOMPONENT_H
#include "component.h"
#include "gameobject.h"

class StarCollectComponent : public Component
{
public:
    StarCollectComponent();
    void Do();
    GameObject *gameObject;
    GameObject *playerObject;
};

#endif // STARCOLLECTCOMPONENT_H
