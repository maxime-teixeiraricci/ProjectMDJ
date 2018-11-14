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

#include <QApplication>
#include <QLabel>
#include <QSurfaceFormat>

#ifndef QT_NO_OPENGL
#include "mainwidget.h"
#include <QTimer>
#include <QGridLayout>
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    app.setApplicationName("cube");
    app.setApplicationVersion("0.1");
#ifndef QT_NO_OPENGL
    // Création du Layout pour mettre les scenes sous forme de grille
    QGridLayout *mainLayout = new QGridLayout;
    // Création du widget principal, qui va contenir les 4 autres widgets
    QWidget *window = new QWidget;

    //Création des 4 widgets;
    MainWidget *widget1 = new MainWidget(60,0);
    MainWidget *widget2 = new MainWidget(60,1);
    MainWidget *widget3 = new MainWidget(60,2);
    MainWidget *widget4 = new MainWidget(60,3);

    //Ajout des 4 widgets au grid Layout
    mainLayout->addWidget(widget1,0,0);
    mainLayout->addWidget(widget2,1,0);
    mainLayout->addWidget(widget3,1,1);
    mainLayout->addWidget(widget4,0,1);

    //Timer permettant de faire changer les saisons
    QTimer *timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), widget1, SLOT(seasonChange()));
    QObject::connect(timer, SIGNAL(timeout()), widget2, SLOT(seasonChange()));
    QObject::connect(timer, SIGNAL(timeout()), widget3, SLOT(seasonChange()));
    QObject::connect(timer, SIGNAL(timeout()), widget4, SLOT(seasonChange()));

    timer->start(2500);

    window->setLayout(mainLayout);
    window->showMaximized(); // <- Permet de mettre la fenetre en grand.
#else
    QLabel note("OpenGL Support required");
    note.show();
#endif
    return app.exec();
}
