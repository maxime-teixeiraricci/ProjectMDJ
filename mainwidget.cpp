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
#include "boxcollidercomponent.h"

double MainWidget::deltaTime = 0;
GameObject* MainWidget::playerObject = nullptr;
std::vector<GameObject *> MainWidget::gameObjects;

MainWidget::MainWidget(double frequence, int seasonStart,QWidget *parent) :
    QOpenGLWidget(parent),
    texture(0),
    angularSpeed(0),
    timeScale(1.0f)
{
    timeFrequence = 1.0/frequence*1000;
    season = seasonStart;
    z = 0;
    setMouseTracking(true);
    applicationTime = 0;
    rotate = 0;
    heightCamera = 25;
    MainWidget::deltaTime = 0;
}

MainWidget::~MainWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete texture;
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
            InputMapping::inputMap["HorizontalAxis"] = 1.0;
        }
        else if (ke->key() == Qt::Key_S)
        {
            InputMapping::inputMap["HorizontalAxis"] = -1.0;
        }

        if (ke->key() == Qt::Key_D)
        {
            InputMapping::inputMap["VerticalAxis"] = 1.0;
        }
        else if (ke->key() == Qt::Key_Q)
        {
            InputMapping::inputMap["VerticalAxis"] = -1.0;
        }

        if (ke->key() == Qt::Key_Left)
        {
            InputMapping::inputMap["CameraHorizontalAxis"] = -1.0;
        }
        else if (ke->key() == Qt::Key_Right)
        {
            InputMapping::inputMap["CameraHorizontalAxis"] = 1.0;
        }

        if (ke->key() == Qt::Key_Down)
        {
            InputMapping::inputMap["CameraVerticalAxis"] = -1.0;
        }
        else if (ke->key() == Qt::Key_Up)
        {
            InputMapping::inputMap["CameraVerticalAxis"] = 1.0;
        }

        if (ke->key() == Qt::Key_Space)
        {
            GravityComponent::gravity *= -1;
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


    PlayerComponent *pc = new PlayerComponent();
    Mesh3D *m5 = new Mesh3D();
    m5->Load("../ProjectMDJ/block.obj");
    m5->LoadTexture("../ProjectMDJ/PlayerTexture.png");

    playerObject = new GameObject(m5);

    pc->gameObject = playerObject;
    playerObject->components.push_back(pc);

    GravityComponent *gc = new GravityComponent();
    gc->gameObject = playerObject;
    playerObject->components.push_back(gc);

    playerObject->transform->position = QVector3D(0, 0, 15);
    MapMaker mapMaker;


    // Creation du niveau
    mapMaker.CreateLevel("../ProjectMDJ/level02.txt");
/*
    for (unsigned int i = 0 ; i < gameObjects.size(); i ++)
    {
        BoxColliderComponent *bc = new BoxColliderComponent();
        bc->size = QVector3D(1,1,1);


        bc->gameObjects = &gameObjects;
        bc->center = gameObjects[i]->transform->position;
        gameObjects[i]->collider = bc;
        bc->gameObject = gameObjects[i];
    }
*/


    BoxColliderComponent *bc = new BoxColliderComponent();
    bc->size = QVector3D(1,1,1)*0.875f;
    playerObject->transform->scale *= 0.875f;
    //bc->gameObjects = &gameObjects;
    bc->center = playerObject->transform->position;
    playerObject->collider = bc;
    bc->gameObject = playerObject;

    Mesh3D *m3 = new Mesh3D();
    m3->Load("../ProjectMDJ/skybox.obj");
    m3->texture = new QOpenGLTexture(QImage(":/Daylight Box UV.png").mirrored());
    skybox = new GameObject(m3);
    skybox->transform->scale *= 3;
    m3->Compute(skybox->transform);
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
    const qreal zNear = 1.0, zFar = 500.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}
//! [5]

void MainWidget::paintGL()
{


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    texture->bind();
    MainWidget::deltaTime = m_time.elapsed() / 1000.0f;

    QMatrix4x4 matrix;

    rotate += InputMapping::inputMap["CameraHorizontalAxis"] *0.25 ;
    applicationTime += (rotate - applicationTime) * 0.1;

    heightCamera += InputMapping::inputMap["CameraVerticalAxis"] * -GravityComponent::GetDirection() ;
    posCamera = QVector3D(25*sin(applicationTime),-25*cos(applicationTime),heightCamera);
    targetCamera += (playerObject->transform->position - targetCamera) *0.05f;


    matrix.lookAt(posCamera, // Eye
                  targetCamera, // Center
                  QVector3D(0,0,1) * -GravityComponent::GetDirection()); // Normal


    Mesh3D::vectorCamera = (targetCamera - posCamera).normalized();

    program.setUniformValue("mvp_matrix", projection * matrix);

    // Use texture unit 0 which contains cube.png
    program.setUniformValue("texture", 0);

    skybox->Draw(&program);



    for (unsigned int i = 0; i < playerObject->components.size(); i++)
    {
        playerObject->components[i]->Do();
    }

    playerObject->mesh->Compute(playerObject->transform);
    playerObject->Draw(&program);


    //playerObject->transform->position += QVector3D(InputMapping::inputMap["HorizontalAxis"], InputMapping::inputMap["VerticalAxis"],0);
    for (unsigned int i = 0; i < gameObjects.size(); i++)
    {

        for (unsigned int j = 0; j < gameObjects[i]->components.size(); j++)
        {

            gameObjects[i]->components[j]->Do();
        }
        gameObjects[i]->Draw(&program);
    }

    if (playerObject->transform->position.z() < -5 || playerObject->transform->position.z() > 20)
    {
        playerObject->collider->Teleport(QVector3D(0,0,18));
        if (GravityComponent::GetDirection() > 0) GravityComponent::gravity *= -1;
    }

    InputMapping::Reset();
    m_time.restart();
    update();

}
