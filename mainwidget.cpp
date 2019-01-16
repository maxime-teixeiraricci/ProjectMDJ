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
#include "switchcomponent.h"

#include "meshrenderer.h"

double MainWidget::deltaTime = 0;
GameObject* MainWidget::playerObject = nullptr;
std::vector<GameObject *> MainWidget::gameObjects;
QVector3D MainWidget::startPosition = QVector3D(0,0,0);
int MainWidget::score = 0;
int MainWidget::levelNumber = 0;
QList<QString> MainWidget::listLevels;
float MainWidget::coefTrackPlayer = 1.0f;
QVector3D MainWidget::centerMap = QVector3D(0,0,0);
float MainWidget::size = 45.0f;

MainWidget::MainWidget(double frequence, int seasonStart,QWidget *parent) :
    QOpenGLWidget(parent),
    texture(0),
    angularSpeed(0),
    timeScale(1.0f)
{
    timeFrequence = 1.0/frequence*1000;
    setMouseTracking(true);
    applicationTime = 0;
    rotate = 0;
    heightCamera = 25;
    MainWidget::deltaTime = 0;
    radiusCamera = 45;

}

MainWidget::~MainWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete texture;
    doneCurrent();
}

void MainWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Z)
    {
        InputMapping::inputMap["HorizontalAxis"] = 1.0;
    }
    else if (event->key() == Qt::Key_S)
    {
        InputMapping::inputMap["HorizontalAxis"] = -1.0;
    }
    if (event->key() == Qt::Key_D)
    {
        InputMapping::inputMap["VerticalAxis"] = 1.0;
    }
    else if (event->key() == Qt::Key_Q)
    {
        InputMapping::inputMap["VerticalAxis"] = -1.0;
    }

    if (event->key() == Qt::Key_Left)
    {
        InputMapping::inputMap["CameraHorizontalAxis"] = -1.0;
    }
    else if (event->key() == Qt::Key_Right)
    {
        InputMapping::inputMap["CameraHorizontalAxis"] = 1.0;
    }

    if (event->key() == Qt::Key_Down)
    {
        InputMapping::inputMap["CameraVerticalAxis"] = -1.0;
    }
    else if (event->key() == Qt::Key_Up)
    {
        InputMapping::inputMap["CameraVerticalAxis"] = 1.0;
    }

    if (event->key() == Qt::Key_Space)
    {
        GravityComponent::gravity *= -1;
    }

    if (event->key() == Qt::Key_Minus)
    {
        radiusCamera -= 0.5f;
    }
    else if (event->key() == Qt::Key_Plus)
    {
        radiusCamera += 0.5f;
    }


    QWidget::keyPressEvent(event);
}

void MainWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Z)
    {
        InputMapping::inputMap["HorizontalAxis"] = 0.0;
    }
    else if (event->key() == Qt::Key_S)
    {
        InputMapping::inputMap["HorizontalAxis"] = 0.0;
    }
    if (event->key() == Qt::Key_D)
    {
        InputMapping::inputMap["VerticalAxis"] = 0.0;
    }
    else if (event->key() == Qt::Key_Q)
    {
        InputMapping::inputMap["VerticalAxis"] = 0.0;
    }

    if (event->key() == Qt::Key_Left)
    {
        InputMapping::inputMap["CameraHorizontalAxis"] = 0.0;
    }
    else if (event->key() == Qt::Key_Right)
    {
        InputMapping::inputMap["CameraHorizontalAxis"] = 0.0;
    }

    if (event->key() == Qt::Key_Down)
    {
        InputMapping::inputMap["CameraVerticalAxis"] = 0.0;
    }
    else if (event->key() == Qt::Key_Up)
    {
        InputMapping::inputMap["CameraVerticalAxis"] = 0.0;
    }

    if (event->key() == Qt::Key_Space)
    {
        GravityComponent::gravity *= 1;
    }



    QWidget::keyReleaseEvent(event);
}

void MainWidget::timerEvent(QTimerEvent *)
{
    update();
}

void MainWidget::ChangeLevel(QString level)
{

    MainWidget::score = 0;
    if (GravityComponent::GetDirection() > 0) GravityComponent::gravity *= -1;
    SwitchComponent::activate = false;

    // Creation du niveau
    MapMaker mapMaker;
    mapMaker.CreateLevel(level);

    playerObject = new GameObject();

    Mesh3D *m5 = new Mesh3D();
    m5->Load("../ProjectMDJ/Model/player.obj");
    m5->LoadTexture("../ProjectMDJ/Texture/player.png");
    playerObject->meshId = MeshRenderer::instance->meshes.size();
    m5->Compute();
    MeshRenderer::instance->meshes.push_back(m5);
    PlayerComponent *pc = new PlayerComponent();
    pc->gameObject = playerObject;
    playerObject->components.push_back(pc);
    GravityComponent *gc = new GravityComponent();
    gc->gameObject = playerObject;
    playerObject->components.push_back(gc);

    playerObject->transform->SetPosition(startPosition);
    BoxColliderComponent *bc = new BoxColliderComponent();
    bc->size = QVector3D(1,1,1)*0.7f;
    playerObject->transform->scale *= 0.7f;
    //bc->gameObjects = &gameObjects;
    bc->center = playerObject->transform->position;
    playerObject->collider = bc;


    bc->gameObject = playerObject;

    Mesh3D *m3 = new Mesh3D();
    m3->Load("../ProjectMDJ/Model/skybox.obj");
    m3->LoadTexture("../ProjectMDJ/Texture/Daylight Box UV.png");
    m3->Compute();

    skybox = new GameObject();
    skybox->transform->scale *= 3;
    skybox->meshId = MeshRenderer::instance->meshes.size();
    MeshRenderer::instance->meshes.push_back(m3);


    // PLAYER



    MeshRenderer::instance->ComputeGameObject();
    //MeshRenderer::instance->transitions[skybox->meshId].push_back(skybox->transform->transformMatrix);
    //MeshRenderer::instance->transitions[playerObject->meshId].push_back(playerObject->transform->transformMatrix);

    gameObjects.push_back(playerObject);
    gameObjects.push_back(skybox);
    MeshRenderer::instance->Init(&program);
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
//!
//!
    listLevels = {"../ProjectMDJ/Levels/level03.txt",
                  "../ProjectMDJ/Levels/level10.txt",
                  "../ProjectMDJ/Levels/level04.txt",
                  "../ProjectMDJ/Levels/level08.txt",
                  "../ProjectMDJ/Levels/level02.txt",
                  "../ProjectMDJ/Levels/level01.txt",
                  "../ProjectMDJ/Levels/level05.txt",
                  "../ProjectMDJ/Levels/level07.txt"};

    //gameObjects.push_back(playerObject);

    //MeshRenderer::instance->meshes.push_back(m5);



    ChangeLevel(MainWidget::listLevels[MainWidget::levelNumber]);


    m_time.start();
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


    m_frameCount = 0 ;
}
//! [4]

void MainWidget::Joypad()
{

    auto gamepads = QGamepadManager::instance()->connectedGamepads();
    if (gamepads.isEmpty()) {
        return;
    }

    gamepad = new QGamepad(*gamepads.begin(), this);
    //qDebug() << gamepad;
    connect(gamepad, &QGamepad::axisRightXChanged, this, [](double value)
        {
            InputMapping::inputMap["CameraHorizontalAxis"] = -value;
        }
        );
    connect(gamepad, &QGamepad::axisRightYChanged, this, [](double value)
        {
            InputMapping::inputMap["CameraVerticalAxis"] = value;
        }
        );
    connect(gamepad, &QGamepad::axisLeftYChanged, this, [](double value)
        {
            InputMapping::inputMap["HorizontalAxis"] = -value;
        }
        );
    connect(gamepad, &QGamepad::axisLeftXChanged, this, [](double value)
        {
            InputMapping::inputMap["VerticalAxis"] = value;
        }
        );
    connect(gamepad, &QGamepad::buttonStartChanged, this, [](bool value)
        {
            if (value) MainWidget::levelNumber = (MainWidget::levelNumber + 1) % MainWidget::listLevels.size();
        }
        );
    connect(gamepad, &QGamepad::buttonSelectChanged, this, [](bool value)
        {
            if (value)
            {
                MainWidget::score = 5;
            }
        }
        );
    connect(gamepad, &QGamepad::buttonAChanged, this, [](bool value)
        {
            if (value) GravityComponent::gravity *= -1;
        }
        );
    connect(gamepad, &QGamepad::buttonL1Changed, this, [](bool value)
        {
            if (value) MainWidget::coefTrackPlayer = 0.0f;
            else MainWidget::coefTrackPlayer = 1.0f;
        }
        );
    connect(gamepad, &QGamepad::buttonL2Changed, this, [](bool value)
        {
            MainWidget::size -=0.5f;
        }
        );
    connect(gamepad, &QGamepad::buttonR2Changed, this, [](bool value)
        {
            MainWidget::size +=0.5f;
        }
        );
}


//! [5]
void MainWidget::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 1.0, zFar = 1000.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}
//! [5]

void MainWidget::paintGL()
{
    QTime paintTime = QTime();
    paintTime.start();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 matrix;
    matrix.lookAt(posCamera,                                            // Eye
                  targetCamera,                                         // Center
                  QVector3D(0,0,1) * -GravityComponent::GetDirection()); // Normal
    Mesh3D::vectorCamera = (targetCamera - posCamera).normalized();

    program.setUniformValue("mvp_matrix", projection * matrix);
    // Use texture unit 0 which contains cube.png
    program.setUniformValue("texture", 0);

    MeshRenderer::instance->ComputeGameObject();
    MeshRenderer::instance->Draw(&program);
    update();

}

void MainWidget::Update()
{
    // Chronometre pour calculer le temps d'éxécution.
    QTime updateTime = QTime();
    updateTime.start();

    // Si aucun gamepad n'a pas été trouvé
    if(gamepad == nullptr) Joypad();

    MainWidget::deltaTime = m_time.elapsed() / 1000.0f;
    deltaTimeFPS += deltaTime;
    m_time.restart();



    applicationTime += -GravityComponent::GetDirection() * InputMapping::inputMap["CameraHorizontalAxis"] *0.035 ;
    heightCamera += -GravityComponent::GetDirection() * InputMapping::inputMap["CameraVerticalAxis"] * 0.035;
    if (heightCamera > 1.3) heightCamera = 1.3;
    if (heightCamera < -1.3) heightCamera = -1.3;
    float radius = 45.0f;


    // CAMERA
    posCamera = QVector3D(size * cos(applicationTime)*cos(heightCamera),
                          size * sin(applicationTime)*cos(heightCamera),
                          size * sin(heightCamera));


    targetCamera += ((MainWidget::centerMap *(1-coefTrackPlayer) + playerObject->transform->position * coefTrackPlayer)  - targetCamera) *0.05f;

    // Activation des composantas du joueur
    for (unsigned int i = 0; i < playerObject->components.size(); i++) playerObject->components[i]->Do();

    // Activation des composants des autres gameobjects
    for (unsigned int i = 0; i < gameObjects.size(); i++)
        for (unsigned int j = 0; j < gameObjects[i]->components.size(); j++)
            gameObjects[i]->components[j]->Do();



    // Si le joueur sort des limites du niveau : Perdu (Recommencer)
    if (playerObject->transform->position.z() < -15 || playerObject->transform->position.z() > 45)
        ChangeLevel(MainWidget::listLevels[MainWidget::levelNumber]);


    // Si le joueur a les 5 étoiles : Gagner (Niveau suivant)
    if (MainWidget::score == 5)
    {
        MainWidget::levelNumber  = (MainWidget::levelNumber + 1) % MainWidget::listLevels.size();
        ChangeLevel(MainWidget::listLevels[MainWidget::levelNumber]);
    }


    updateTime.restart();
    frameNumber ++;



    if (frameNumber % 50 == 0)
    {
        std::cout << "Update Time : " << deltaTimeFPS/50.0 << "ms [FPS " << 1.0/(deltaTimeFPS/50.0)<<"]"<< std::endl;
        deltaTimeFPS = 0;
    }

}
