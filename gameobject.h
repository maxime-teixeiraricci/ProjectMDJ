#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "mesh.h"

class GameObject
{
public:
    GameObject();
    GameObject(Mesh3D newMesh);
    virtual ~GameObject();

    GameObject* getParent();
    std::vector<GameObject*> getChilds();
    Mesh3D getMesh();
    QVector3D getRelativePosition();
    int getNbChilds();

    void setParent(GameObject* newParent);
    void setMesh(Mesh3D newMesh);
    void setRelativePosition(QVector3D newRelativePosition);

    void addChild(GameObject* newChild);
    uint posElmtChilds(GameObject* obj);
    void removeChild(GameObject* child);
    void Draw(QOpenGLShaderProgram *program);
    void updateAbsolute();



private:
    GameObject* parent;
    std::vector<GameObject*> enfants;
    int nbEnfants;
    Mesh3D mesh;
    QVector3D relativePosition;
    QVector3D absoluPosition;



};

#endif // GAMEOBJECT_H
