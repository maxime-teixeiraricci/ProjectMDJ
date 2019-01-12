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

            if (max.x()< X) max.setX(X);
            if (max.y()< Y) max.setY(Y);
            if (max.z()< Z) max.setZ(Z);
            if (min.x()> X) min.setX(X);
            if (min.y()> Y) min.setY(Y);
            if (min.z()> Z) min.setZ(Z);
            center += vertex;
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

    center/=lod->verticePosition.size();
    sphereBoundDistance = 0;
    for (int i = 0; i <lod-> verticePosition.size(); i ++)
    {
        double d = (center - lod->verticePosition[i]).length();
        if (d > sphereBoundDistance) sphereBoundDistance = d;
    }
    for( unsigned int i=0; i < lod->trianglesIndex.size(); i+=3 )
    {
        unsigned int k = i/3;
        QVector3D A = lod->normals[lod->normalsIndex[lod->trianglesIndex[3*k]]];
        QVector3D B = lod->normals[lod->normalsIndex[lod->trianglesIndex[3*k+1]]];
        QVector3D C = lod->normals[lod->normalsIndex[lod->trianglesIndex[3*k+2]]];
        lod->normalsTriangles.push_back(normalTriangle(A,B,C));

    }

    meshesLOD.push_back(lod);
}


void Mesh3D::Translate(QVector3D vector)
{
    MeshIdentity *mesh = meshesLOD[lodIndex];
    max += vector;
    min += vector;
    center += vector;
    sphereBoundDistance = 0;
    for (unsigned int i = 0; i < mesh->verticePosition.size(); i ++)
    {
        double d = (center-mesh->verticePosition[i]).length();
        if (d > sphereBoundDistance) sphereBoundDistance = d;
    }
}

void Mesh3D::Rotate(QQuaternion rotation)
{
    MeshIdentity *mesh = meshesLOD[lodIndex];
    for (unsigned int i = 0; i < mesh->verticePosition.size(); i ++)
    {
        QGenericMatrix<1,3, float> m1;
        m1(0, 0) = mesh->verticePosition[i].x();
        m1(1, 0) = mesh->verticePosition[i].y();
        m1(2,0) = mesh->verticePosition[i].z();
        /*QGenericMatrix<1,3, float> matrixNormal;
        matrixNormal(0, 0) = mesh->normals[i].x();
        matrixNormal(1, 0) = mesh->normals[i].y();
        matrixNormal(2,0) = mesh->normals[i].z();*/
        QGenericMatrix<3,3, float> m2(rotation.toRotationMatrix());



        QGenericMatrix<1,3,float> result = m2*m1;
        mesh->verticePosition[i] = QVector3D(result.data()[0],result.data()[1],result.data()[2] );

        //QGenericMatrix<1,3,float> result2 = m2*matrixNormal;

        //mesh->normals[i] = QVector3D(result2.data()[0],result2.data()[1],result2.data()[2] );
    }

    for (unsigned int i = 0; i < mesh->normals.size(); i ++)
    {
        QGenericMatrix<3,3, float> m2(rotation.toRotationMatrix());
        QGenericMatrix<1,3, float> matrixNormal;
        matrixNormal(0, 0) = mesh->normals[i].x();
        matrixNormal(1, 0) = mesh->normals[i].y();
        matrixNormal(2,0) = mesh->normals[i].z();
        QGenericMatrix<1,3,float> result2 = m2*matrixNormal;
        mesh->normals[i] = QVector3D(result2.data()[0],result2.data()[1],result2.data()[2] );
    }


}

void Mesh3D::Scale(double scale)
{
    MeshIdentity *mesh = meshesLOD[lodIndex];
    for (unsigned int i = 0; i < mesh->verticePosition.size(); i ++)
    {
        mesh->verticePosition[i] = mesh->verticePosition[i] * scale;
    }
    max *=scale;
    min *=scale;
    center *=scale;
    sphereBoundDistance = 0;
    for (int i = 0; i < mesh->verticePosition.size(); i ++)
    {
        double d = (center- mesh->verticePosition[i]).length();
        if (d > sphereBoundDistance) sphereBoundDistance = d;
    }
}


void Mesh3D::StaticLoad(const QString fileName)
{
    Load(fileName,0);
}

void Mesh3D::KDopCompute()
{
    MeshIdentity *mesh = meshesLOD[lodIndex];
    /* {1,1,0},	{-1,1,0},{1,-1,0},{-1,-1,0},{1,	0,1},{-1,0,1},{1,0,-1},{-1,0,-1},{0,1,1},{0,-1,1},{0,1,-1},{0,-1,-1} */
    std::vector<QVector3D> axis = {QVector3D(1,1,0),QVector3D(-1,1,0),QVector3D(1,-1,0),QVector3D(-1,-1,0),
                                   QVector3D(1,0,1),QVector3D(-1,0,1),QVector3D(1,0,-1),QVector3D(-1,0,-1),
                                   QVector3D(0,1,1),QVector3D(0,-1,1),QVector3D(0,1,-1),QVector3D(0,-1,-1)};

    kdopMax = {};
    kdopMin = {};
    for (unsigned int v = 0; v < mesh->verticePosition.size(); v ++)
    {
        QVector3D vertex = mesh->verticePosition[v] + origin;
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

QVector3D Mesh3D::normalTriangle(QVector3D verticeA, QVector3D verticeB,QVector3D verticeC)
{
    return ((verticeA + verticeB + verticeC) / 3.0f).normalized();
}

void Mesh3D::Compute()
{
    Compute(new Transform());
}

void Mesh3D::Compute(Transform *transform)
{
    MeshIdentity *mesh = meshesLOD[lodIndex];
    int j =0;

    QVector3D vectCam = Mesh3D::vectorCamera;
    //QVector3D vectCam(1,-1,-1);
    vectCam.normalize();
    int index = 0;
    outVertexData = {};
    outIndexData = {};
    color = QColor(255,255,255);
    QVector3D *offsets = new QVector3D[3]{QVector3D(0,0,0), QVector3D(2,0,1), QVector3D(0,-2,-3)};
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


void Mesh3D::Draw(QOpenGLShaderProgram *program, Transform *transform)
{

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
    //glDrawElementsInstanced()
    glDrawElements(GL_TRIANGLES, outIndexData.size(), GL_UNSIGNED_SHORT, nullptr);

}


/*
void Mesh3D::Draw(QOpenGLShaderProgram *program, Transform *transform)
{
    initializeOpenGLFunctions();
    int numberObjects = 1;
    QMatrix4x4 *translations = new QMatrix4x4[numberObjects];
    for (unsigned int i = 0 ; i < numberObjects; i ++)
    {
        QMatrix4x4 mat;
        mat.setToIdentity();
        translations[i] = mat;//Identity();
    }
    // Buffer de translations
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    int stride = sizeof(VertexData);
    unsigned int vertexVBO;

    glGenBuffers(1, &vertexVBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData) * outVertexData.size(), outVertexData.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO); // OPEN VBO
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)sizeof(QVector3D));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(sizeof(QVector3D)+sizeof(QVector2D)));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(2*sizeof(QVector3D)+sizeof(QVector2D)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);  // CLOSE VBO

    // Buffer de Matrix
    unsigned int instanceVBO;
    glGenBuffers(1, &instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(QMatrix4x4) * numberObjects, &translations[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(QMatrix4x4), (void*)0);
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(QMatrix4x4), (void*)(sizeof(QVector4D)));
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE,sizeof(QMatrix4x4), (void*)(2*sizeof(QVector4D)));
    glEnableVertexAttribArray(7);
    glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(QMatrix4x4), (void*)(3*sizeof(QVector4D)));

    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);
    glVertexAttribDivisor(7, 1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(VertexData) * outVertexData.size(), outVertexData.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    texture->bind();

    glBindVertexArray(VAO);
    glDrawArraysInstanced(GL_TRIANGLES, 0, outIndexData.size(), numberObjects);
    glBindVertexArray(0);


}


void Mesh3D::Draw(QOpenGLShaderProgram *program, Transform *transform)
{
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
        int vertexLocation = program->attributeLocation("aPos");
        program->enableAttributeArray(vertexLocation);
        program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

        offset += sizeof(QVector3D);

        int texcoordLocation = program->attributeLocation("aText");
        program->enableAttributeArray(texcoordLocation);
        program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

        offset += sizeof(QVector2D);

        int normalLocation = program->attributeLocation("aNormal");
        program->enableAttributeArray(normalLocation);
        program->setAttributeBuffer(normalLocation, GL_FLOAT, offset, 3, sizeof(VertexData));
        //meshes[m].texture->bind();

        offset += sizeof(QVector3D);

        int colorLocation = program->attributeLocation("aColor");
        program->enableAttributeArray(colorLocation);
        program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 3, sizeof(VertexData));


        int offsetLocation = program->attributeLocation("aOffset");
        program->enableAttributeArray(offsetLocation);
        //program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 3, sizeof(VertexData));
        QMatrix4x4 mat;
        mat.setToIdentity();
        //program->setUniformValue(offsetLocation, mat);


        texture->bind();
        //glDrawElementsInstanced()
        glDrawElements(GL_TRIANGLES, outIndexData.size(), GL_UNSIGNED_SHORT, nullptr);
}


*/
