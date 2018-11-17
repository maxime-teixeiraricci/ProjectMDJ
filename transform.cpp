#include "transform.h"
#include "QPainter"
#include "QOpenGLShaderProgram"
#include <iostream>



Transform::Transform()
{
    //transformMatrix.setToIdentity();
    position = QVector3D(0,0,0);
    scale= QVector3D(1,1,1);
    rotation = QQuaternion(1,0,0,0);
    parent = 0;
    Rotate();
    Translate();
    Scale();
}

void Transform::Rotate()
{
    transformMatrix.rotate(rotation);
}

void Transform::Translate()
{
    transformMatrix.translate(position);
}

void Transform::Scale()
{
    transformMatrix.scale(scale);
}

void Transform::SetPosition(QVector3D vector)
{
    position = vector;
    Translate();
}

void Transform::SetRotation(QQuaternion quaternion)
{
    rotation = quaternion;
    Rotate();
}

void Transform::SetScale(QVector3D vector)
{
    scale = vector;
    Scale();
}

QVector3D Transform::GetPosition()
{
    return position;
}

QQuaternion Transform::GetRotation()
{
    return rotation;
}

QVector3D Transform::GetScale()
{
    return scale;
}
