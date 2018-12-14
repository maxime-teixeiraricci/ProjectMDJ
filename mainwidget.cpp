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
#include "playercomponent.h"
#include "mapmaker.h"

double MainWidget::deltaTime = 0;
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
    inputMapping = new InputMapping();
    setMouseTracking(true);
    applicationTime = 0;
    MainWidget::deltaTime = 0;


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
    //inputMapping->reset();
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *ke = static_cast<QKeyEvent *>(event);
        if (ke->key() == Qt::Key_Z)
        {
            inputMapping->inputMap["up"] = 1;
        }
        else
        {
            inputMapping->inputMap["up"] = 0;
        }
        if (ke->key() == Qt::Key_S)
        {
            inputMapping->inputMap["down"] = 1;
        }
        else
        {
            inputMapping->inputMap["down"] = 0;
        }
        if (ke->key() == Qt::Key_Q)
        {
            inputMapping->inputMap["left"] = 1;
        }
        else
        {
            inputMapping->inputMap["left"] = 0;
        }
        if (ke->key() == Qt::Key_D)
        {
            inputMapping->inputMap["right"] = 1;
        }
        else
        {
            inputMapping->inputMap["right"] = 0;
        }

        if (ke->key() == Qt::Key_Up)
        {
            inputMapping->inputMap["cameraZ"] = 1;
        }
        if (ke->key() == Qt::Key_Down)
        {
            inputMapping->inputMap["cameraZ"] = -1;
        }
        if (ke->key() == Qt::Key_Left)
        {
            inputMapping->inputMap["cameraHorizontal"] = 1;
        }
        if (ke->key() == Qt::Key_Right)
        {
            inputMapping->inputMap["cameraHorizontal"] = -1;
        }

        if (ke->key() == Qt::Key_Plus)
        {
            inputMapping->inputMap["cameraZoom"] = inputMapping->inputMap["cameraZoom"] - 0.5;
        }

        if (ke->key() == Qt::Key_Minus)
        {
            inputMapping->inputMap["cameraZoom"] = inputMapping->inputMap["cameraZoom"] + 0.5;
        }
        return true;
    } else if (event->type() == QEvent::MouseMove) {
        /*QMouseEvent *mouse = static_cast<QMouseEvent *>(event);
        inputMapping->inputMap["axisHori"] = mouse->x()/(width()*1.0);
        inputMapping->inputMap["axisVerti"] = mouse->y()/(height()*1.0);
        inputMapping->printMap();
        return true;*/
    }

    return QWidget::event(event);
}

void MainWidget::DrawMesh(GameObject *gameObject)
{
    gameObject->Draw(&program);
    for (unsigned int i = 0; i < gameObject->numberChildren();i++)
    {
       gameObject->getChild(i)->Draw(&program);
    }

}

void MainWidget::timerEvent(QTimerEvent *)
{
    applicationTime += 0 * timeScale;
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


/*
    // Use QBasicTimer because its faster than QTimer
   timer.start(timeFrequence, this);
   Mesh3D *m1 = new Mesh3D();
   Mesh3D *m2 = new Mesh3D();
   Mesh3D *m3 = new Mesh3D();
   Mesh3D *m4 = new Mesh3D();
   Mesh3D *m5 = new Mesh3D();
   m1->Load("../ProjectMDJ/cube.obj");
   m2->Load("../ProjectMDJ/block.obj");
   m3->Load("../ProjectMDJ/skybox.obj");
   // Test LOD :
   m4->Load("../ProjectMDJ/block.obj");
   m5->Load("../ProjectMDJ/block.obj");
   //


   //
   m3->texture = new QOpenGLTexture(QImage(":/Daylight Box UV.png").mirrored());

   gravity.gravity = QVector3D(0,0,-0.25f);
   GameObject *G1 = new GameObject(m1);

  G1->transform->SetScale(QVector3D(5,5,5));
  m1->LoadTexture("../ProjectMDJ/mud.png");
  m4->LoadTexture("../ProjectMDJ/grass.png");
  m5->LoadTexture("../ProjectMDJ/PlayerTexture.png");
  unsigned int index =0;

  int col = 9;
  int lin = 9;

  for (int i = 0 ; i < lin * col ; i ++)
  {
      if ((i%lin) == 0 || (i%lin) == lin - 1 || (i/lin) == 0 || (i/lin) == col - 1)
      {
      gameObjects.push_back(new GameObject(m1));
      //gameObjects[index]->SetScale(QVector3D(0.5,0.5,0.5));
      float X = ((i%lin) - (lin/2))*2.0f;
      float Y = ((i/lin) - (lin/2))*2.0f;
      gameObjects[index++]->SetPosition(QVector3D(X, Y, -3));
      }
  }


  for (int i = 0 ; i < lin * col ; i ++)
  {
      gameObjects.push_back(new GameObject(m4));
      //gameObjects[index]->SetScale(QVector3D(0.5,0.5,0.5));
      float X = ((i%lin) - (lin/2))*2.0f;
      float Y = ((i/lin) - (lin/2))*2.0f;
      gameObjects[index++]->SetPosition(QVector3D(X, Y, -1));
  }

  m2->LoadTexture("../ProjectMDJ/wood.png");
  gameObjects.push_back(new GameObject(m2));
  gameObjects[gameObjects.size() - 1]->SetScale(QVector3D((lin/2)+1,(col/2)+1,0.5));
  gameObjects[gameObjects.size() - 1]->SetPosition(QVector3D(0, 0, -4.5));

   // gameObjects.push_back(G1);


   //gameObjects.push_back(G2);
   //gameObjects.push_back(G4);*/
    PlayerComponent *pc = new PlayerComponent();
    pc->input = inputMapping;
    Mesh3D *m5 = new Mesh3D();
    m5->Load("../ProjectMDJ/block.obj");
    m5->LoadTexture("../ProjectMDJ/PlayerTexture.png");
    playerObject = new GameObject(m5);
    pc->gameObject = playerObject;
    playerObject->SetScale(QVector3D(0.5,0.5,0.5));
    playerObject->components.push_back(pc);
    playerObject->SetPosition(QVector3D(0, 0, 3));
   MapMaker mapMaker;
   //gameObjects =
   mapMaker.CreateLevel("../ProjectMDJ/level02.txt", &gameObjects);

   Mesh3D *m3 = new Mesh3D();
   m3->Load("../ProjectMDJ/skybox.obj");
   m3->texture = new QOpenGLTexture(QImage(":/Daylight Box UV.png").mirrored());
   skybox = new GameObject(m3);
   m_time.start();

}

void MainWidget::seasonChange()
{
    float deltaTime = m_time.elapsed();
}

//! [3]
void MainWidget::initShaders()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
    {
        program.log();
        close();
    }

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
   // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    int MatSpec [4] = {1,1,1,1};
    //glMaterialiv(GL_FRONT_AND_BACK,GL_SPECULAR,MatSpec);
    //glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,100);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glMatrixMode(GL_MODELVIEW);
    texture->bind();
    MainWidget::deltaTime = m_time.elapsed() / 1000.0f;

//! [6]
    // Calculate model view transformation
    QMatrix4x4 matrix;
    //matrix.translate(0.0, 0, .0);
    //matrix.rotate(rotation);

    applicationTime += inputMapping->inputMap["cameraHorizontal"] * MainWidget::deltaTime;
    posCamera = QVector3D(35*sin(applicationTime),35*cos(applicationTime),15);
    matrix.lookAt(posCamera, // Eye
                  QVector3D(0,0,0), // Center
                  QVector3D(0,0,1)); // Normal

    Mesh3D::vectorCamera = (QVector3D(0,0,0) - posCamera).normalized();
    // Set modelview-projection matrixç
    program.setUniformValue("mvp_matrix", projection * matrix);
//! [6]

    // Use texture unit 0 which contains cube.png
    program.setUniformValue("texture", 0);

    skybox->Draw(&program);


    /*QQuaternion q = gameObjects[0]->transform->GetRotation() + QQuaternion(100,1,0,0);
    gameObjects[0]->transform->SetRotation(q.normalized());*/
    playerObject->components[0]->Do();
    //std::cout <<"Size: " << playerObject->components.size() << std::endl;
    playerObject->Draw(&program);

    for (unsigned int i = 0; i < gameObjects.size(); i++)
    {
        std::cout <<i<<"/"<< gameObjects.size() << std::endl;
        gameObjects[i]->Draw(&program);
    }


    inputMapping->inputMap["cameraInertie"] = inputMapping->inputMap["cameraInertie"] + (inputMapping->inputMap["axisHori"] * (deltaTime/1000.0)*5);
    inputMapping->inputMap["cameraInertie"] = inputMapping->inputMap["cameraInertie"] * 0.97;

    //applicationTime += inputMapping->inputMap["cameraInertie"];


    //
    m_time.restart();
    update();

}
