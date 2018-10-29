#ifndef MESH_H
#define MESH_H
#include <QVector2D>
#include <QVector3D>
#include <QOpenGLTexture>

class Mesh3D
{
public:
    Mesh3D();
    void Translate(QVector3D vector);
    void Scale(double scale);
    void Load();

    QOpenGLTexture *texture;
    std::vector<QVector3D> verticePosition;
    std::vector<QVector2D> texturePosition;
    std::vector<QVector3D> normals;

    std::vector<int> trianglesIndex;
    std::vector<int> texturesIndex;
    std::vector<int> normalsIndex;

    QVector3D max;
    QVector3D min;
    QVector3D center;
    double sphereBoundDistance;


};

#endif // MESH_H
