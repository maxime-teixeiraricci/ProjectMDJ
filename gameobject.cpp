#include "gameobject.h"
#include <collider.h>
#include "mainwidget.h"


GameObject::GameObject()
{

    transform = new Transform();
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


