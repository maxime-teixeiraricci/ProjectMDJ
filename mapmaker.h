#ifndef MAPMAKER_H
#define MAPMAKER_H

#include <gameobject.h>

enum MeshID {GRASS_BLOCK,
             MOVABLE_BLOCK,
             WIRED_BLOCK_BLUE,
            FULL_BLOCK_BLUE,
            WIRED_BLOCK_RED,
            FULL_BLOCK_RED,
            SWITCH_UP_RED,
            SWITCH_UP_BLUE,
            STAR,
            INVISIBLE_BLOCK,
            MUD_BLOCK,
            SWITCH_DOWN_BLACK,
            PLANK_BLOCK};


class MapMaker
{
public:
    MapMaker();


    void CreateLevel(QString mapfile);
    void InstantiateMesh();
};

#endif // MAPMAKER_H
