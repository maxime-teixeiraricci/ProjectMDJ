#include "mesh.h"
#include <iostream>
#include <QFile>
#include <QOpenGLFunctions>
#include <QGenericMatrix>
#include <QOpenGLExtraFunctions>
#include <stdlib.h>



QVector3D Mesh3D::vectorCamera = QVector3D(0,0,0);

Mesh3D::Mesh3D()
{
    texture = new QOpenGLTexture(QImage(":/PaletteTest.png").mirrored());
    color = QColor(255,255,255);
    lodIndex = 0;
}

void Mesh3D::Load(const QString fileName)
{
    Load(fileName,0);
}

void Mesh3D::LoadTexture(const QString fileName)
{
    texture = new QOpenGLTexture(QImage(fileName).mirrored());
}


void Mesh3D::Load(const QString fileName, int LODIndex)
{
    MeshIdentity *lod = new MeshIdentity();

    std::vector<QVector3D> temp_vertices;
    std::vector<QVector2D> temp_uvs;
    std::vector<QVector3D> temp_normals;
    QFile file(fileName);
    file.open(QFile::ReadOnly);

    if( file.exists() == NULL )
    {
        std::cout<<"Impossible to open the file !\n"<< std::endl;
    }
    int done = 1;
    while( done )
    {
        char lineHeader[128];
        // read the first word of the line

        int res = file.readLine(lineHeader, 128);

        if (res == EOF)
        {
            done = 0; // EOF = End Of File. Quit the loop.
        }
        if ( lineHeader[0] == 'v' && lineHeader[1] != 't' && lineHeader[1] != 'n'){
            float X,Y,Z;
            QVector3D vertex;

            sscanf_s(lineHeader, "v %f %f %f\n", &X,&Y,&Z);
            vertex.setX(X);
            vertex.setY(Y);
            vertex.setZ(Z);

            lod->verticePosition.push_back(vertex);
        }else if ( lineHeader[0] == 'v' && lineHeader[1] == 't'){
            float X,Y;
            QVector2D uv;
            sscanf_s(lineHeader, "vt %f %f\n", &X, &Y );
            uv.setX(X);
            uv.setY(Y);
            lod->texturePosition.push_back(uv);
        }else if ( lineHeader[0] == 'v' && lineHeader[1] == 'n'){
            float X,Y,Z;
            QVector3D normal;
            sscanf_s(lineHeader, "vn %f %f %f\n", &X, &Y, &Z );
            normal.setX(X);
            normal.setY(Y);
            normal.setZ(Z);
            lod->normals.push_back(normal);
        }else if ( lineHeader[0] == 'f' )
        {
            std::string vertex1, vertex2, vertex3;
            GLushort vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = sscanf_s(lineHeader, "f %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );


            if (matches != 9)
            {
                printf("File can't be read by our simple parser : ( Try exporting with other options\n");
            }
            lod->trianglesIndex.push_back(vertexIndex[0]-1);
            lod->trianglesIndex.push_back(vertexIndex[1]-1);
            lod->trianglesIndex.push_back(vertexIndex[2]-1);
            lod->texturesIndex    .push_back(uvIndex[0]-1);
            lod->texturesIndex    .push_back(uvIndex[1]-1);
            lod->texturesIndex    .push_back(uvIndex[2]-1);
            lod->normalsIndex.push_back(normalIndex[0]-1);
            lod->normalsIndex.push_back(normalIndex[1]-1);
            lod->normalsIndex.push_back(normalIndex[2]-1);
        }
    }
    meshesLOD.push_back(lod);
}



void Mesh3D::Compute()
{
    Compute(new Transform());
}

void Mesh3D::Compute(Transform *transform)
{
    MeshIdentity *mesh = meshesLOD[lodIndex];

    QVector3D vectCam = Mesh3D::vectorCamera;

    vectCam.normalize();
    int index = 0;
    outVertexData = {};
    outIndexData = {};
    color = QColor(255,255,255);

    for( unsigned int i=0; i < mesh->trianglesIndex.size(); i+=3 )
    {
        QMatrix4x4 rt = QMatrix4x4();
        rt.rotate(transform->rotation.normalized());

        for(int m = 0; m < 3 ; m ++)
        {
            int I = mesh->trianglesIndex[i+m];
            int J = mesh->texturesIndex[i+m];
            int K = mesh->normalsIndex[i+m];
            transform->getMatrix();
            QVector3D vertex = transform->transformMatrix * mesh->verticePosition[ I ];
            QVector2D texture = mesh->texturePosition[ J ];

            QVector3D normal = rt * mesh->normals[K];
            QVector3D colorTexture = QVector3D(color.red() /255.0f, color.green()/255.0f, color.blue()/255.0f);
            outVertexData.push_back( {vertex, texture,normal,colorTexture});
            outIndexData.push_back(index++);
        }
    }
}
