#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <collider.h>
#include <iostream>
#include "mesh.h"
#include "transform.h"

class GameObject
{
public:

    GameObject(Mesh3D *newMesh);
    GameObject(Mesh3D *newMesh, GameObject* parent);

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
    void Draw(QOpenGLShaderProgram *program, Transform *transform);
    void SetPosition(QVector3D newPosition);
    void SetScale(QVector3D newScale);
    void SetRotation(QQuaternion newRotation);

    int test;
    QVector3D position;
    QVector3D scale;
    QVector4D rotation; // Quaternion <3
    Collider* collider;
    Mesh3D *mesh;
    Transform *transform;

private:
    GameObject* parent;
    std::vector<GameObject*> children;



};

#endif // GAMEOBJECT_H
