#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include <QVector3D>
#include <QMap>
#include <mesh.h>
#include <QOpenGLExtraFunctions>
#include <QColor>
#include "gameobject.h"

class MeshRenderer : protected QOpenGLExtraFunctions
{
public:
    static MeshRenderer *instance;
    MeshRenderer();

    QList<std::vector<QMatrix4x4>> transitions;
    QList<std::vector<QColor>> colors;
    QList<Mesh3D*> meshes;

    void Draw(QOpenGLShaderProgram *program);
    void DrawSingle(GameObject *gameObject);

    void ComputeGameObject();
    void Init(QOpenGLShaderProgram *program);

    unsigned int *VAOs;
    unsigned int *EBOs;
    unsigned int *vertexVBOs;
    unsigned int *instanceVBOs;

};

#endif // MESHRENDERER_H
