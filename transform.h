#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "QVector3D"
#include "QQuaternion"
#include "QMatrix4x4"

class Transform
{
public:
    Transform();

    Transform* parent;

    void SetPosition(QVector3D vector);
    void SetRotation(QQuaternion quaternion);
    void SetScale(QVector3D vector);

    QVector3D GetPosition();
    QQuaternion GetRotation();
    QVector3D GetScale();

    QMatrix4x4 transformMatrix;

    QVector3D position;
    QVector3D scale;
    QQuaternion rotation;


    QVector3D eulerAngle;

    void getMatrix();
    void Rotate();
    void Translate();
    void Scale();



private:



};

#endif // TRANSFORM_H
