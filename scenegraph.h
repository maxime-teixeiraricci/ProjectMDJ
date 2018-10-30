#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include "gameobject.h"

class SceneGraph
{
public:
    SceneGraph();

    GameObject* getRacine();
    int getProfondeur();

    void setRacine(GameObject* newRacine);
    void setProfondeur(int newProfondeur);

    void addChild(GameObject* parent,GameObject* enfant);
    void removeObjectBranch(GameObject* object);

    QVector3D getAbsolutPosition(GameObject* object);

private:
    GameObject* racine;
    int profondeur;


};

#endif // SCENEGRAPH_H
