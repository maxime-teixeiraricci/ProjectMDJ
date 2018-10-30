#include "scenegraph.h"

SceneGraph::SceneGraph()
{
}

GameObject* SceneGraph::getRacine(){
    return racine;
}

int SceneGraph::getProfondeur(){
    return profondeur;
}

void SceneGraph::setRacine(GameObject* newRacine){
    racine = newRacine;
}

void SceneGraph::setProfondeur(int newProfondeur){
    profondeur = newProfondeur;
}

void SceneGraph::addChild(GameObject* parent,GameObject* enfant){
    parent->addChild(enfant);
}

void SceneGraph::removeObjectBranch(GameObject* object){
    object->getParent()->removeChild(object);
}

QVector3D SceneGraph::getAbsolutPosition(GameObject* object){
    QVector3D pos = object->getRelativePosition();
    GameObject* currentObj = object;
    do{
        pos += currentObj->getRelativePosition();
        currentObj = currentObj->getParent();
    }while(currentObj->getParent());
    return pos;
}
