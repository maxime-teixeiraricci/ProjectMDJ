#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <collider.h>
#include <iostream>
#include "mesh.h"
#include "transform.h"
#include "component.h"
#include "collidercomponent.h"
#include "QColor"

class GameObject
{
public:
    GameObject();
    GameObject(Mesh3D *newMesh);
    GameObject(Mesh3D *newMesh, GameObject* parent);

    int numberChildren();
    GameObject* getParent();
    std::vector<GameObject*> getChildren();
    GameObject* getChild(int index);
    Mesh3D* getMesh();

    void setParent(GameObject* newParent);
    void setMesh(Mesh3D* newMesh);

    void addChild(GameObject* newChild);
    void Draw(QOpenGLShaderProgram *program);
    void Draw(QOpenGLShaderProgram *program, Transform *transform);

    Mesh3D *mesh;
    Transform *transform;
    std::vector<Component *> components;
    ColliderComponent *collider = nullptr;
    void Destroy();


    int meshId = -1;
    int meshInstanceId;
    QColor color;
    bool isDrawable = true;


private:
    GameObject* parent;
    std::vector<GameObject*> children;



};

#endif // GAMEOBJECT_H
