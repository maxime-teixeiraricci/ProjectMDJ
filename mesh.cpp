#include "mesh.h"
#include <iostream>
#include <QFile>
//#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
//#include <QOpenGLBuffer>

Mesh3D::Mesh3D()
{
   verticePosition ={};
    texturePosition={};
    normals={};

    trianglesIndex={};
    texturesIndex={};
    normalsIndex={};
}

void Mesh3D::Load()
{
    std::vector< GLushort > vertexIndices, uvIndices, normalIndices;
    std::vector<QVector3D> temp_vertices;
    std::vector<QVector2D> temp_uvs;
    std::vector<QVector3D> temp_normals;
    QFile file("C:/Users/Maxime/Documents/HMIN317/cube.obj");
    file.open(QFile::ReadOnly);

    if( file.exists() == NULL )
    {
        std::cout<<"Impossible to open the file !\n"<< std::endl;
    }

    std::cout<<"Modele chargée !!!!" << std::endl;
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
            verticePosition.push_back(vertex);
        }else if ( lineHeader[0] == 'v' && lineHeader[1] == 't'){
            float X,Y;
            QVector2D uv;
            sscanf_s(lineHeader, "vt %f %f\n", &X, &Y );
            uv.setX(X);
            uv.setY(Y);
            texturePosition.push_back(uv);
        }else if ( lineHeader[0] == 'f' )
        {
            std::string vertex1, vertex2, vertex3;
            GLushort vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = sscanf_s(lineHeader, "f %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );


            if (matches != 9)
            {
                printf("File can't be read by our simple parser : ( Try exporting with other options\n");
            }
            trianglesIndex.push_back(vertexIndex[0]-1);
            trianglesIndex.push_back(vertexIndex[1]-1);
            trianglesIndex.push_back(vertexIndex[2]-1);
            texturesIndex    .push_back(uvIndex[0]-1);
            texturesIndex    .push_back(uvIndex[1]-1);
            texturesIndex    .push_back(uvIndex[2]-1);
            normalIndices.push_back(normalIndex[0]-1);
            normalIndices.push_back(normalIndex[1]-1);
            normalIndices.push_back(normalIndex[2]-1);
        }
    }
}


void Mesh3D::Translate(QVector3D vector)
{
    for (int i = 0; i < verticePosition.size(); i ++)
    {
        verticePosition[i] = verticePosition[i] + vector;
    }
}



