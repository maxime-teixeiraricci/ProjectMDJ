#ifndef MESH_H
#define MESH_H
#include <QVector2D>
#include <QVector3D>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

#include <QOpenGLBuffer>
#include "transform.h"
//#include <collider.h>

// Contient les informations d'une Mesh (Nécessaire pour LOD)
struct MeshIdentity
{

    std::vector<QVector3D> verticePosition;
    std::vector<QVector2D> texturePosition;
    std::vector<QVector3D> normals;
    std::vector<QVector3D> normalsTriangles;
    std::vector<QVector3D> color;

    std::vector<int> trianglesIndex;
    std::vector<int> texturesIndex;
    std::vector<int> normalsIndex;
};

class Mesh3D : protected QOpenGLFunctions
{
public:
    Mesh3D();
    static QVector3D vectorCamera;
    void Translate(QVector3D vector);
    void Scale(double scale);
    void Rotate(QQuaternion rotate);
    void Load(const QString fileName);
    void Load(const QString fileName, int lodIndex);
    void LoadTexture(const QString fileName);

    QOpenGLTexture *texture;

    // Gestion des LODs
    std::vector<MeshIdentity *> meshesLOD;
    unsigned int lodIndex;
    //

    QVector3D max;
    QVector3D min;
    std::vector<float> kdopMax;
    std::vector<float> kdopMin;
    QVector3D center;
    double sphereBoundDistance;
    void Draw(QOpenGLShaderProgram *program, QVector3D relativePosition);
    void Draw(QOpenGLShaderProgram *program, Transform *transform);
    QVector3D normalTriangle(QVector3D verticeA, QVector3D verticeB,QVector3D verticeC);

    void KDopCompute();
    QVector3D origin;
    int test;

    QColor color;


};

#endif // MESH_H
