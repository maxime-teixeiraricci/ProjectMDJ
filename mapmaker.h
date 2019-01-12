#ifndef MAPMAKER_H
#define MAPMAKER_H

#include <gameobject.h>

class MapMaker
{
public:
    MapMaker();
    void CreateLevel(QString mapfile);
    void InstantiateMesh();
};

#endif // MAPMAKER_H
