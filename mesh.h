#ifndef MESH_H
#define MESH_H
#include <QVector2D>
#include <QVector3D>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_4_Core>

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

struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
    QVector3D normal;
    QVector3D color;
};

class Mesh3D : protected QOpenGLExtraFunctions
{
public:
    Mesh3D();
    static QVector3D vectorCamera;
    void Translate(QVector3D vector);
    void Scale(double scale);
    void Rotate(QQuaternion rotate);
    void Load(const QString fileName);
    void StaticLoad(const QString fileName);
    void Load(const QString fileName, int lodIndex);
    void LoadTexture(const QString fileName);
    void Compute(Transform *transform);
    void Compute();

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
    //void Draw(QOpenGLShaderProgram *program, QVector3D relativePosition);
    void Draw(QOpenGLShaderProgram *program, Transform *transform);
    QVector3D normalTriangle(QVector3D verticeA, QVector3D verticeB,QVector3D verticeC);

    void KDopCompute();
    QVector3D origin;
    int test;
    bool isDrawable = true;

    QColor color;

    std::vector<VertexData> outVertexData;
    std::vector<GLushort> outIndexData;


};

#endif // MESH_H
