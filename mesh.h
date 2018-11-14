#ifndef MESH_H
#define MESH_H
#include <QVector2D>
#include <QVector3D>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

#include <QOpenGLBuffer>
//#include <collider.h>

class Mesh3D : protected QOpenGLFunctions
{
public:
    Mesh3D();
    void Translate(QVector3D vector);
    void Scale(double scale);
    void Rotate(QQuaternion rotate);
    void Load(const char *fileName);

    QOpenGLTexture *texture;
    std::vector<QVector3D> verticePosition;
    std::vector<QVector2D> texturePosition;
    std::vector<QVector3D> normals;

    std::vector<int> trianglesIndex;
    std::vector<int> texturesIndex;
    std::vector<int> normalsIndex;

    QVector3D max;
    QVector3D min;
    std::vector<float> kdopMax;
    std::vector<float> kdopMin;
    QVector3D center;
    double sphereBoundDistance;
    void Draw(QOpenGLShaderProgram *program, QVector3D relativePosition);

    void KDopCompute();
    QVector3D origin;
    int test;

    QColor color;


};

#endif // MESH_H
