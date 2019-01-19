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

    QList<Mesh3D*> meshes;
    QList<std::vector<QMatrix4x4>> transitions;
    QList<std::vector<QColor>> colors;


    void Draw();


    void ComputeGameObject();
    void Init();

    unsigned int *VAOs;
    unsigned int *EBOs;
    unsigned int *vertexVBOs;
    unsigned int *instanceVBOs;
    bool done = false;

};

#endif // MESHRENDERER_H
