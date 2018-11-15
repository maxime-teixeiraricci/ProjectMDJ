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

#include "mainwidget.h"

#include <QMouseEvent>
#include <iostream>
#include <collider.h>

//#include <math.h>

MainWidget::MainWidget(double frequence, int seasonStart,QWidget *parent) :
    QOpenGLWidget(parent),
    geometries1(0),
    geometries2(0),
    texture(0),
    angularSpeed(0),
    timeScale(1.0f)

{
    timeFrequence = 1.0/frequence*1000;
    season = seasonStart;
    z = 0;
    inputMapping = InputMapping();
    setMouseTracking(true);
    applicationTime = 0;


}

MainWidget::~MainWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete texture;
    delete geometries1;
    delete geometries2;
    doneCurrent();
}

bool MainWidget::event(QEvent *event)
{
    QMapIterator<QString, float> i(inputMapping.inputMap);
    while (i.hasNext()) {
        i.next();
        inputMapping.inputMap[i.key()] = 0;
    }

    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *ke = static_cast<QKeyEvent *>(event);
        if (ke->key() == Qt::Key_Z) {
            inputMapping.inputMap["up"] = 1;
            inputMapping.printMap();
            return true;
        }else if (ke->key() == Qt::Key_Q) {
            inputMapping.inputMap["right"] = 1;
            inputMapping.printMap();
            return true;
        }else if (ke->key() == Qt::Key_S) {
            inputMapping.inputMap["down"] = 1;
            inputMapping.printMap();
            return true;
        }else if (ke->key() == Qt::Key_D) {
            inputMapping.inputMap["left"] = 1;
            inputMapping.printMap();
            return true;
        }else if (ke->key() == Qt::Key_Space) {
            inputMapping.inputMap["jump"] = 1;
            inputMapping.printMap();
            return true;
        }else if (ke->key() == Qt::Key_E) {
            inputMapping.inputMap["gravity"] = 1;
            inputMapping.printMap();
            return true;
        }
    } else if (event->type() == QEvent::MouseMove) {
        QMouseEvent *mouse = static_cast<QMouseEvent *>(event);
        inputMapping.inputMap["axisHori"] = mouse->x()/(width()*1.0);
        inputMapping.inputMap["axisVerti"] = mouse->y()/(height()*1.0);
        inputMapping.printMap();
        return true;
    }

    return QWidget::event(event);
}

//! [0]
void MainWidget::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());
}

void MainWidget::DrawMesh(GameObject *gameObject)
{
    gameObject->Draw(&program);
    for (unsigned int i = 0; i < gameObject->numberChildren();i++)
    {
       gameObject->getChild(i)->Draw(&program);
    }

}

void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{

    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();
    //rotationAxis = QVector3D(0.0,0.0,1.0).normalized();

    // Increase angular speed
    angularSpeed += acc;
}
//! [0]

//! [1]
void MainWidget::timerEvent(QTimerEvent *)
{
    applicationTime += 0 * timeScale;
    update();
}
//! [1]

void MainWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Up)
    {
        timeScale += 0.05;
    }
    else if (event->key() == Qt::Key_Down)
    {
        timeScale -= 0.05;
    }
    update();
}

void MainWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    initShaders();
    initTextures();

//! [2]
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable( GL_FRONT);
//! [2]

    geometries1 = new GeometryEngine;
    geometries2 = new GeometryEngine;

    // Use QBasicTimer because its faster than QTimer
   timer.start(timeFrequence, this);
   Mesh3D *m1 = new Mesh3D();
   Mesh3D *m2 = new Mesh3D();
   Mesh3D *m3 = new Mesh3D();
   Mesh3D *m4 = new Mesh3D();
   m1->Load("../ProjectMDJ/slope.obj");
   m2->Load("../ProjectMDJ/cube.obj");
   m3->Load("../ProjectMDJ/skybox.obj");
   // Test LOD :
   m4->Load("../ProjectMDJ/SuzaneLOD0.obj",0);
   m4->Load("../ProjectMDJ/SuzaneLOD1.obj",1);
   m4->Load("../ProjectMDJ/SuzaneLOD2.obj",2);
   m4->Load("../ProjectMDJ/SuzaneLOD3.obj",3);
   m4->Load("../ProjectMDJ/SuzaneLOD4.obj",4);
   //


   //
   m3->texture = new QOpenGLTexture(QImage(":/Daylight Box UV.png").mirrored());

   gravity.gravity = QVector3D(0,0,-0.25f);
   GameObject *G1 = new GameObject(m1);
   GameObject *G2 = new GameObject(m2);
   GameObject *G3 = new GameObject(m3);
   GameObject *G4 = new GameObject(m4);

   G1->SetPosition( QVector3D(0,0,0));
   G2->SetPosition( QVector3D(2.5,0,2.5));

   G4->SetPosition( QVector3D(-5,0,0));

   G2->addChild(G4);
   gameObjects.push_back(G1);
   gameObjects.push_back(G2);
   //gameObjects.push_back(G4);
   skybox = G3;
   m_time.start();
   seasonChange();
}

void MainWidget::seasonChange()
{
   season = (season + 1) % 4;
   QColor seasonColor = seasonColors[season];
   for (unsigned int i =0; i < gameObjects.size(); i ++)
   {
       gameObjects[i]->mesh->color = seasonColor;
   }


}

//! [3]
void MainWidget::initShaders()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}
//! [3]

//! [4]
void MainWidget::initTextures()
{
    // Load cube.png image
    texture = new QOpenGLTexture(QImage(":/TextureDegrade.png").mirrored());
    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);


    textures.push_back(new QOpenGLTexture(QImage(":/spring.png").mirrored()));
    textures.push_back(new QOpenGLTexture(QImage(":/summer.png").mirrored()));
    textures.push_back(new QOpenGLTexture(QImage(":/fall.png").mirrored()));
    textures.push_back(new QOpenGLTexture(QImage(":/winter.png").mirrored()));
    for (unsigned i=0; i < 4; i ++)
    {
        textures[i]->setMinificationFilter(QOpenGLTexture::Nearest);
        textures[i]->setMagnificationFilter(QOpenGLTexture::Linear);
        textures[i]->setWrapMode(QOpenGLTexture::Repeat);
    }

    m_frameCount = 0 ;
}
//! [4]

//! [5]
void MainWidget::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 1.0, zFar = 100.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}
//! [5]

void MainWidget::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texture->bind();

//! [6]
    // Calculate model view transformation
    QMatrix4x4 matrix;
    //matrix.translate(0.0, 0, .0);
    //matrix.rotate(rotation);

    posCamera = QVector3D(20*sin(applicationTime),20*cos(applicationTime),3);
    matrix.lookAt(posCamera, // Eye
                  QVector3D(0,0,0), // Center
                  QVector3D(0,0,1)); // Normal

    // Set modelview-projection matrixç
    program.setUniformValue("mvp_matrix", projection * matrix);
//! [6]

    // Use texture unit 0 which contains cube.png
    program.setUniformValue("texture", 0);

    skybox->Draw(&program);
    for (int i = 0; i < gameObjects.size(); i++)
    {
        gameObjects[i]->Draw(&program);
    }
    std::cout << "Application Time : " << applicationTime << std::endl;
    applicationTime += m_time.elapsed() * 0.00025 * timeScale;
    if(!gameObjects[1]->collider->IsCollide(gameObjects[0]->collider) && gameObjects[1]->position.z() > -2)
    {
        gravity.ApplyGravity(gameObjects[1]);
    }
    else
    {
        gameObjects[1]->SetPosition(QVector3D(gameObjects[1]->position.x(),0,2.5));
        gameObjects[1]->SetPosition(gameObjects[1]->position + QVector3D(-0.25,0,0));
        if (gameObjects[1]->position.x() < -2.5)
        {
            gameObjects[1]->SetPosition(QVector3D(2.5,0,2.5));
        }
    }


    float distanceRatio = (posCamera - gameObjects[1]->getChild(0)->position).length()/30;
    gameObjects[1]->getChild(0)->mesh->lodIndex = (int) (distanceRatio / 0.25f);

    if (distanceRatio < 0.1f) gameObjects[1]->getChild(0)->mesh->lodIndex = 0;
    else if (distanceRatio < 0.25f) gameObjects[1]->getChild(0)->mesh->lodIndex = 1;
    else if (distanceRatio < 0.5f) gameObjects[1]->getChild(0)->mesh->lodIndex = 2;
    else if (distanceRatio < 0.75f) gameObjects[1]->getChild(0)->mesh->lodIndex = 3;
    else  gameObjects[1]->getChild(0)->mesh->lodIndex = 4;

    std::cout << "Season Change !" << std::endl;





    m_time.restart();

}
