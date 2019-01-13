#include "boxcollidercomponent.h"
#include "QColor"
#include "meshrenderer.h"

BoxColliderComponent::BoxColliderComponent()
{

}


bool BoxColliderComponent::Collide(BoxColliderComponent *collider)
{
    float axn = center.x() - size.x();
    float axx = center.x() + size.x();
    float bxn = collider->center.x() - collider->size.x();
    float bxx = collider->center.x() + collider->size.x();

    bool A = ((axn <= bxn) && (bxn <= axx)) || ((bxn <= axn) && (axn <= bxx));

    float ayn = center.y() - size.y();
    float ayx = center.y() + size.y();
    float byn = collider->center.y() - collider->size.y();
    float byx = collider->center.y() + collider->size.y();

    bool B = ((ayn <= byn) && (byn <= ayx)) || ((byn <= ayn) && (ayn <= byx));

    float azn = center.z() - size.z();
    float azx = center.z() + size.z();
    float bzn = collider->center.z() - collider->size.z();
    float bzx = collider->center.z() + collider->size.z();

    bool C = ((azn <= bzn) && (bzn <= azx)) || ((bzn <= azn) && (azn <= bzx));
    return A && B && C;
}




void BoxColliderComponent::Move(QVector3D moveVect)
{
    QVector3D currentCenter = center;
    center += moveVect;
    for (unsigned int i = 0; i < MainWidget::gameObjects.size(); i++)
    {
        if (MainWidget::gameObjects.at(i) != gameObject &&
                MainWidget::gameObjects.at(i)->collider != nullptr &&
                !MainWidget::gameObjects.at(i)->collider->isTrigger)
        {
            BoxColliderComponent *bc = static_cast<BoxColliderComponent*> (MainWidget::gameObjects.at(i)->collider);
            if ( Collide(bc) )
            {
                center = currentCenter;
                QVector3D vect =(MainWidget::gameObjects.at(i)->transform->position - gameObject->transform->position).normalized();

                QVector3D v = 0.95 * moveVect * QVector3D::dotProduct(moveVect.normalized(),vect);
                float dx = QVector3D::dotProduct(QVector3D(1,0,0),vect);
                float dy = QVector3D::dotProduct(QVector3D(0,1,0),vect);
                if ((dx*dx) < (dy*dy))
                {
                    //Move(QVector3D(0,v.y(),v.z()));
                    Move(QVector3D(moveVect.x()*0.95,v.y(),v.z()));
                }
                else
                {
                    Move(QVector3D(v.x(),moveVect.y()*0.95,v.z()));
                    //Move(QVector3D(0,moveVect.y()*0.98,0));
                }
                /*QVector3D p1(v.x(),0,0);
                QVector3D p2(0,v.y(),0);
                QVector3D p3(0,0,v.z());
                Move(p1);
                Move(p2);
                Move(p3);*/
                return;
            }
        }

    }
    gameObject->transform->position += moveVect;

}

void BoxColliderComponent::Teleport(QVector3D pos)
{
    QVector3D currentCenter = center;
    //center = currentCenter;
    center = pos;
    gameObject->transform->position = pos;
    qDebug() << "TELEPORT";
    MeshRenderer::instance->DrawSingle(gameObject);

}
