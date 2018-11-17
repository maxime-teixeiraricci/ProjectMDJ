#include "gameobject.h"
#include <collider.h>

GameObject::GameObject(Mesh3D *newMesh)
{
    mesh = newMesh;
    this->position = QVector3D(0,0,0);
    this->scale = QVector3D(1,1,1);
    this->rotation = QVector4D(0,0,0,1);
    collider = new Collider(newMesh);
    transform = new Transform();
}

GameObject::GameObject(Mesh3D *newMesh, GameObject* parent)
{
    //mesh = newMesh;
    position = QVector3D(0,0,0);
    scale = QVector3D(1,1,1);
    rotation = QVector4D(0,0,0,1);
    setParent(parent);
    collider = new Collider(newMesh);
    transform = new Transform();
}



GameObject* GameObject::getParent()
{
    return parent;
}

std::vector<GameObject*> GameObject::getChildren()
{
    return children;
}

GameObject* GameObject::getChild(int index)
{
    return children.at(index);
}

Mesh3D* GameObject::getMesh()
{
    return mesh;
}

void GameObject::setParent(GameObject* newParent)
{
    parent = newParent;
}


int GameObject::numberChildren()
{
    return children.size();
}

void GameObject::setMesh(Mesh3D* newMesh)
{
    mesh = newMesh;
}

void GameObject::addChild(GameObject* newChild)
{
    children.push_back(newChild);
}

void GameObject::Draw(QOpenGLShaderProgram *program, QVector3D parentPosition)
{
    mesh->Draw(program, position +parentPosition);
    for (unsigned int child = 0 ; child < children.size(); child ++)
    {
       getChild(child)->Draw(program, position + parentPosition);
    }
}

void GameObject::Draw(QOpenGLShaderProgram *program)
{
    Draw(program, transform);
}

void GameObject::Draw(QOpenGLShaderProgram *program, Transform *transform)
{
    mesh->Draw(program, transform);
}

void GameObject::SetPosition(QVector3D newPosition)
{
    transform->SetPosition(newPosition);
}

void GameObject::SetScale(QVector3D newScale)
{
    transform->SetScale(newScale);
}

void GameObject::SetRotation(QQuaternion newRotation)
{
    transform->SetRotation(newRotation);
}

QVector3D GameObject::GetPosition()
{
    return position;
}
