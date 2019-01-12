#include "gameobject.h"
#include <collider.h>
#include "mainwidget.h"


GameObject::GameObject()
{

    transform = new Transform();
}

GameObject::GameObject(Mesh3D *newMesh)
{
    mesh = newMesh;
    transform = new Transform();
}

GameObject::GameObject(Mesh3D *newMesh, GameObject* parent)
{
    setParent(parent);
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

void GameObject::Destroy()
{
    for (unsigned int i = 0; i < MainWidget::gameObjects.size(); i++)
    {
        if (MainWidget::gameObjects[i] == this)
        {
            MainWidget::gameObjects.erase(MainWidget::gameObjects.begin()+i);
            return;
        }
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
