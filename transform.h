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

private:
    QVector3D position;
    QVector3D scale;
    QQuaternion rotation;

    void Rotate();
    void Translate();
    void Scale();


};

#endif // TRANSFORM_H
