#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <collider.h>
#include <iostream>
#include "mesh.h"

class GameObject
{
public:

    GameObject(Mesh3D *newMesh);
    GameObject(Mesh3D *newMesh, GameObject* parent);
    GameObject(Mesh3D *newMesh, QVector3D position);

    int numberChildren();
    GameObject* getParent();
    std::vector<GameObject*> getChildren();
    GameObject* getChild(int index);
    Mesh3D* getMesh();
    QVector3D GetPosition();

    void setParent(GameObject* newParent);
    void setMesh(Mesh3D* newMesh);

    void addChild(GameObject* newChild);
    void Draw(QOpenGLShaderProgram *program, QVector3D parentPosition);
    void Draw(QOpenGLShaderProgram *program);
    void SetPosition(QVector3D newPosition);

    int test;
    QVector3D position;
    QVector3D scale;
    QVector4D rotation; // Quaternion <3
    Collider* collider;

private:
    GameObject* parent;
    std::vector<GameObject*> children;
    Mesh3D *mesh;


};

#endif // GAMEOBJECT_H
