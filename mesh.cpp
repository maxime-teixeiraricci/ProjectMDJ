#include "mesh.h"
#include <iostream>
#include <QFile>
#include <QOpenGLFunctions>
#include <QGenericMatrix>

struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
    QVector3D normal;
    QVector3D color;
};


Mesh3D::Mesh3D()
{
   verticePosition ={};
    texturePosition={};
    normals={};

    trianglesIndex={};
    texturesIndex={};
    normalsIndex={};
    texture = new QOpenGLTexture(QImage(":/PaletteTest.png").mirrored());
    color = QColor(255,255,255);
}

void Mesh3D::Load(const char *fileName)
{
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

            if (max.x()< X) max.setX(X);
            if (max.y()< Y) max.setY(Y);
            if (max.z()< Z) max.setZ(Z);
            if (min.x()> X) min.setX(X);
            if (min.y()> Y) min.setY(Y);
            if (min.z()> Z) min.setZ(Z);
            center += vertex;
            verticePosition.push_back(vertex);
        }else if ( lineHeader[0] == 'v' && lineHeader[1] == 't'){
            float X,Y;
            QVector2D uv;
            sscanf_s(lineHeader, "vt %f %f\n", &X, &Y );
            uv.setX(X);
            uv.setY(Y);
            texturePosition.push_back(uv);
        }else if ( lineHeader[0] == 'v' && lineHeader[1] == 'n'){
            float X,Y,Z;
            QVector3D normal;
            sscanf_s(lineHeader, "vn %f %f %f\n", &X, &Y, &Z );
            normal.setX(X);
            normal.setY(Y);
            normal.setZ(Z);
            normals.push_back(normal);
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
            normalsIndex.push_back(normalIndex[0]-1);
            normalsIndex.push_back(normalIndex[1]-1);
            normalsIndex.push_back(normalIndex[2]-1);
        }
    }
    printf("Mesh : %s\n", fileName);
    center/=verticePosition.size();
    sphereBoundDistance = 0;
    for (int i = 0; i < verticePosition.size(); i ++)
    {
        double d = (center-verticePosition[i]).length();
        if (d > sphereBoundDistance) sphereBoundDistance = d;
    }
}


void Mesh3D::Translate(QVector3D vector)
{


    max += vector;
    min += vector;
    center += vector;
    sphereBoundDistance = 0;
    for (int i = 0; i < verticePosition.size(); i ++)
    {
        double d = (center-verticePosition[i]).length();
        if (d > sphereBoundDistance) sphereBoundDistance = d;
    }
}

void Mesh3D::Rotate(QQuaternion rotation)
{
    for (int i = 0; i < verticePosition.size(); i ++)
    {
        QGenericMatrix<1,3, float> m1;
        m1(0, 0) = verticePosition[i].x();
        m1(0, 1) = verticePosition[i].y();
        m1(0, 2) = verticePosition[i].z();

        QGenericMatrix<3,3, float> m2(rotation.toRotationMatrix());



        QGenericMatrix<1,3,float> result = m2 * m1;

        //verticePosition[i] = ;
    }
    sphereBoundDistance = 0;
    for (int i = 0; i < verticePosition.size(); i ++)
    {
        double d = (center-verticePosition[i]).length();
        if (d > sphereBoundDistance) sphereBoundDistance = d;
    }
}

void Mesh3D::Scale(double scale)
{
    for (int i = 0; i < verticePosition.size(); i ++)
    {
        verticePosition[i] = verticePosition[i] * scale;
    }
    max *=scale;
    min *=scale;
    center *=scale;
    sphereBoundDistance = 0;
    for (int i = 0; i < verticePosition.size(); i ++)
    {
        double d = (center-verticePosition[i]).length();
        if (d > sphereBoundDistance) sphereBoundDistance = d;
    }
}

void Mesh3D::Draw(QOpenGLShaderProgram *program, QVector3D relativePosition)
{

    int j =0;
    std::vector<VertexData> outVertexData;
    std::vector<GLushort> outIndexData;
    for( unsigned int i=0; i < trianglesIndex.size(); i++ )
    {

        int I = trianglesIndex[i];
        int J = texturesIndex[i];
        int K = normalsIndex[i];
       QVector3D vertex = verticePosition[ I ]+relativePosition;
       QVector2D texture = texturePosition[ J ];
       QVector3D normal = normals[K];
       QVector3D colorTexture = QVector3D(color.red() /255.0f, color.green()/255.0f, color.blue()/255.0f);
       outVertexData.push_back( {vertex, texture,normal,colorTexture});
       outIndexData.push_back(i);


    }
    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf(QOpenGLBuffer::IndexBuffer);
    initializeOpenGLFunctions();
    arrayBuf.create();
    indexBuf.create();

    arrayBuf.bind();
    arrayBuf.allocate(outVertexData.data(), outVertexData.size() * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(outIndexData.data(), outIndexData.size() * sizeof(GLushort));

    quintptr offset = 0;
    //program->setAttributeValue(program->attributeLocation("snow"), snow);
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    offset += sizeof(QVector3D);

    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    offset += sizeof(QVector2D);

    int normalLocation = program->attributeLocation("a_normal");
    program->enableAttributeArray(normalLocation);
    program->setAttributeBuffer(normalLocation, GL_FLOAT, offset, 3, sizeof(VertexData));
    //meshes[m].texture->bind();

    offset += sizeof(QVector3D);

    int colorLocation = program->attributeLocation("a_color");
    program->enableAttributeArray(colorLocation);
    program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 3, sizeof(VertexData));
    texture->bind();

    glDrawElements(GL_TRIANGLES, outIndexData.size(), GL_UNSIGNED_SHORT, nullptr);
}

void Mesh3D::KDopCompute()
{
    /* {1,1,0},	{-1,1,0},{1,-1,0},{-1,-1,0},{1,	0,1},{-1,0,1},{1,0,-1},{-1,0,-1},{0,1,1},{0,-1,1},{0,1,-1},{0,-1,-1} */
    std::vector<QVector3D> axis = {QVector3D(1,1,0),QVector3D(-1,1,0),QVector3D(1,-1,0),QVector3D(-1,-1,0),
                                  QVector3D(1,0,1),QVector3D(-1,0,1),QVector3D(1,0,-1),QVector3D(-1,0,-1),
                                  QVector3D(0,1,1),QVector3D(0,-1,1),QVector3D(0,1,-1),QVector3D(0,-1,-1)};

    kdopMax = {};
    kdopMin = {};
    for (unsigned int v = 0; v < verticePosition.size(); v ++)
    {
        QVector3D vertex = verticePosition[v] + origin;
        for (unsigned int i = 0; i < axis.size(); i ++)
        {
            float fScore = axis[i].normalized().x() * vertex.x() + axis[i].normalized().y() * vertex.y() +axis[i].normalized().z() * vertex.z();
            if (v == 0)
            {
                kdopMax.push_back(fScore);
                kdopMin.push_back(fScore);
            }
            else
            {
                kdopMax[i] = std::max(kdopMax[i],fScore);
                kdopMin[i] = std::min(kdopMin[i],fScore);
            }
        }
    }

}
