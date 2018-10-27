#ifndef MESH_H
#define MESH_H
#include <QVector2D>
#include <QVector3D>


class Mesh3D
{
public:
    Mesh3D();
    void Translate(QVector3D vector);
    void Load();


    std::vector<QVector3D> verticePosition;
    std::vector<QVector2D> texturePosition;
    std::vector<QVector3D> normals;

    std::vector<int> trianglesIndex;
    std::vector<int> texturesIndex;
    std::vector<int> normalsIndex;


};

#endif // MESH_H
