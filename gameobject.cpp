#include "gameobject.h"

GameObject::GameObject()
{

}

GameObject::GameObject(Mesh3D newMesh)
{
    mesh = newMesh;
    absoluPosition = QVector3D(0,0,0);
    relativePosition = QVector3D(0,0,0);
    parent = 0;
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

Mesh3D GameObject::getMesh(){
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

void GameObject::updateAbsolute()
{
    absoluPosition = relativePosition;
    if (parent)
    {
        absoluPosition += parent->absoluPosition;
    }
}

void GameObject::setMesh(Mesh3D newMesh){
    mesh = newMesh;
}

void GameObject::setRelativePosition(QVector3D newRelativePosition){
    relativePosition = newRelativePosition;
    updateAbsolute();



}

void GameObject::addChild(GameObject* newChild){

   newChild->setParent(this);
   newChild->updateAbsolute();
   enfants.push_back(newChild);
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

void GameObject::Draw(QOpenGLShaderProgram *program)
{
    mesh.Draw(program, absoluPosition);
    //mesh.Draw(program, enfants[0]->absoluPosition);
}

