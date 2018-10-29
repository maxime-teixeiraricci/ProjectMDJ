/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "geometryengine.h"
#include <iostream>
#include <QFile>
#include <stdio.h>
using namespace std;
#include <QVector2D>
#include <QVector3D>
#include <QColor>
#include <QImage>
#include <QPainter>

struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
    QVector3D normal;
};

//! [0]
GeometryEngine::GeometryEngine()
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    Mesh3D m = Mesh3D();
    snow = 0;
    /*Mesh3D m1 = Mesh3D();
    Mesh3D m2 = Mesh3D();

    for (int i = 0; i < 25; i++)
    {
        Mesh3D m = Mesh3D();
        m.Load();
        m.Translate(QVector3D(2-i%5,2-i/5,0));
        meshes.push_back(m);

    }*/
    m.Load();
    m.Scale(0.25);

    meshes.push_back(m);
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();
}

GeometryEngine::~GeometryEngine()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}
//! [0]

void GeometryEngine::Draw(QOpenGLShaderProgram *program)
{
    // For each vertex of each triangle
   /* vector<VertexData> outVertexData;
    vector<GLushort> outIndexData;*/

    for (int m = 0; m < meshes.size(); m++)
    {
        Mesh3D mesh = meshes[m];

        int j =0;
        vector<VertexData> outVertexData;
        vector<GLushort> outIndexData;
        for( unsigned int i=0; i < mesh.trianglesIndex.size(); i++ )
        {

            int I = mesh.trianglesIndex[i];
            int J = mesh.texturesIndex[i];
            int K = mesh.normalsIndex[i];
           QVector3D vertex = mesh.verticePosition[ I ];
           QVector2D texture = mesh.texturePosition[ J ];
           QVector3D normal = mesh.normals[K];
           //printf("3D<%d,%d,%d>\n",normal.x(), normal.y(), normal.z());
           outVertexData.push_back( {vertex, texture,normal});
           outIndexData.push_back(i);


        }

        arrayBuf.bind();
        arrayBuf.allocate(outVertexData.data(), outVertexData.size() * sizeof(VertexData));

        // Transfer index data to VBO 1
        indexBuf.bind();
        indexBuf.allocate(outIndexData.data(), outIndexData.size() * sizeof(GLushort));
        numberVertices = outIndexData.size();





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
        meshes[m].texture->bind();



        glDrawElements(GL_TRIANGLES, numberVertices*3, GL_UNSIGNED_SHORT, 0);

    }

}


void GeometryEngine::DrawBB(Mesh3D mesh,QOpenGLShaderProgram *program)
{
    VertexData pos[] =
    {
        {QVector3D(mesh.min.x(),mesh.min.y(),mesh.min.z()), QVector2D(0,0)}, // [0]
        {QVector3D(mesh.max.x(),mesh.min.y(),mesh.min.z()), QVector2D(0,0)}, // [1]
        {QVector3D(mesh.min.x(),mesh.max.y(),mesh.min.z()), QVector2D(0,0)}, // [2]
        {QVector3D(mesh.max.x(),mesh.max.y(),mesh.min.z()), QVector2D(0,0)}, // [3]
        {QVector3D(mesh.min.x(),mesh.min.y(),mesh.max.z()), QVector2D(0,0)}, // [4]
        {QVector3D(mesh.max.x(),mesh.min.y(),mesh.max.z()), QVector2D(0,0)}, // [5]
        {QVector3D(mesh.min.x(),mesh.max.y(),mesh.max.z()), QVector2D(0,0)}, // [6]
        {QVector3D(mesh.max.x(),mesh.max.y(),mesh.max.z()), QVector2D(0,0)}  // [7]
    };
    int index[] =
    {
        0,2,
        0,1,
        2,3,
        1,3,
        4,6,
        4,5,
        6,7,
        5,7,
        0,4,
        5,1,
        7,3,
        6,2
    };
    arrayBuf.bind();
    arrayBuf.allocate(pos, 8 * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(index, 24 * sizeof(int));
    quintptr offset = 0;
    //program->setAttributeValue(program->attributeLocation("snow"), snow);
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    offset += sizeof(QVector3D);

    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    glDrawElements(GL_LINES, 24*2, GL_UNSIGNED_SHORT, 0);

}

