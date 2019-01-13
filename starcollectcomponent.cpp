#include "starcollectcomponent.h"
#include "QVector3D"
#include "mainwidget.h"

StarCollectComponent::StarCollectComponent()
{

}


void StarCollectComponent::Do()
{
    if ((gameObject->transform->position - MainWidget::playerObject->transform->position).length() < 1.5f)
    {
        std::cout << "Destroy !!" << std::endl;
        MainWidget::score ++;
        qDebug() << "Score: " << MainWidget::score;
        gameObject->Destroy();

    }
}
