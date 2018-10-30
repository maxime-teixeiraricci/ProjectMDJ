#include "gameobject.h"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{
}

GameObject* GameObject::getParent(){
    return parent;
}

std::vector<GameObject*> GameObject::getChilds(){
    return enfants;
}

Mesh3D* GameObject::getMesh(){
    return mesh;
}

QVector3D GameObject::getRelativePosition(){
    return relativePosition;
}

int GameObject::getNbChilds(){
    return nbEnfants;
}

void GameObject::setParent(GameObject* newParent){
    parent = newParent;
}

void GameObject::setMesh(Mesh3D* newMesh){
    mesh = newMesh;
}

void GameObject::setRelativePosition(QVector3D newRelativePosition){
    relativePosition = newRelativePosition;
}

void GameObject::addChild(GameObject* newChild){
    enfants.push_back(newChild);
    nbEnfants++;
}

uint GameObject::posElmtChilds(GameObject* obj){

    // ici, comment obtenir idx tel qu'il corresponde à la position de 'result' dans v1 ?
    uint idx = std::find( enfants.begin(), enfants.end(), obj ) - enfants.begin();
    return idx;
}

void GameObject::removeChild(GameObject* child){
    enfants.erase(std::find( enfants.begin(), enfants.end(), child ));
    nbEnfants--;
}


