#include "mapmaker.h"
#include <iostream>
#include <QFile>

#include "rotationcomponent.h"
#include "starcollectcomponent.h"
#include "boxcollidercomponent.h"
#include "switchcomponent.h"
#include "colorblockcomponent.h"
#include "invisibiltycomponent.h"

#include <stdlib.h>

MapMaker::MapMaker()
{

}

void  MapMaker::CreateLevel(QString mapfile)
{

    MainWidget::gameObjects.clear();
    QFile file(mapfile);
    file.open(QFile::ReadOnly);

    QOpenGLTexture *texture = new QOpenGLTexture(QImage("../ProjectMDJ/grass.png").mirrored());

    if( file.exists() == NULL )
    {
        std::cout<<"Impossible to open the file ! " << std::endl;
    }
    int done = 1;
    char lineHeader[128];
    int res = file.readLine(lineHeader, 128);
    // read the first word of the line
    int X,Y,Z; // Dimension du monde
    int x,y;
    int t = sscanf_s(lineHeader, "%d%d%d\n", &X,&Y,&Z);
    std::cout << X << ", " << Y << ", "<< Z << std::endl;
    if (t != 3)
    {
        std::cout<<"Mauvais type! " << std::endl;
    }
    int j = 0;
    int I = 0;
    while( done )
    {
        res = file.readLine(lineHeader, 128);


        if (res == EOF)
        {
            done = 0; // EOF = End Of File. Quit the loop.
        }

        else if ( lineHeader[0] == '.')
        {
            Z --;
            j = 0;
        }
        else
        {
            for (unsigned int i = 0; i < X; i++)
            {
                char c = lineHeader[i];

                if ((int) c == 13)
                {
                    break;
                }
                if (c != 'O')
                {

                    Mesh3D *m = new Mesh3D();
                    GameObject *gameObject = new GameObject(m);
                    float x = -(X/2.0) + i;
                    float y = -(Y/2.0) + j;
                    gameObject->transform->position = QVector3D(x*2, y*2, Z*2);
                    BoxColliderComponent *bc = new BoxColliderComponent();
                    bc->size = QVector3D(1,1,1);


                    bc->center = gameObject->transform->position;

                    if (c == 'H')
                    {
                        m->Load("../ProjectMDJ/block.obj");
                        m->texture = texture;
                        //m->LoadTexture("../ProjectMDJ/grass.png");
                        gameObject->collider = bc;
                        bc->gameObject = gameObject;
                        (MainWidget::gameObjects).push_back(gameObject);
                        m->Compute(gameObject->transform);
                    }
                    else if (c == 'W')
                    {
                        m->Load("../ProjectMDJ/block.obj");
                        m->texture = texture;
                        //m->LoadTexture("../ProjectMDJ/grass.png");
                        gameObject->collider = bc;
                        bc->gameObject = gameObject;
                        (MainWidget::gameObjects).push_back(gameObject);
                        m->Compute(gameObject->transform);
                    }
                    else if (c == 'X')
                    {
                        m->Load("../ProjectMDJ/block.obj");
                        m->texture = texture;
                        //m->LoadTexture("../ProjectMDJ/block.png");
                        gameObject->collider = bc;
                        bc->size = QVector3D(1,1,1)*0.98f;

                        bc->gameObject = gameObject;
                        GravityComponent *gc = new GravityComponent();
                        gc->gameObject = gameObject;
                        gameObject->components.push_back(gc);
                        gameObject->transform->scale *= 0.98f;
                        (MainWidget::gameObjects).push_back(gameObject);
                        m->Compute(gameObject->transform);
                    }

                    else if (c == 'Q')
                    {
                        m->Load("../ProjectMDJ/switchUp.obj");
                        m->LoadTexture("../ProjectMDJ/redSwitch.png");
                        SwitchComponent *sc = new SwitchComponent();
                        sc->gameObject = gameObject;
                        sc->startState = false;
                        sc->ChangeColor();
                        gameObject->collider = bc;
                        bc->gameObject = gameObject;
                        bc->size = QVector3D(1,1,1)*0.75f;
                        bc->isTrigger = true;
                        gameObject->components.push_back(sc);
                        (MainWidget::gameObjects).push_back(gameObject);
                        m->Compute(gameObject->transform);
                    }
                    else if (c == 'Z')
                    {
                        m->Load("../ProjectMDJ/switchUp.obj");
                        m->LoadTexture("../ProjectMDJ/blueSwitch.png");
                        SwitchComponent *sc = new SwitchComponent();
                        sc->gameObject = gameObject;
                        sc->startState = true;
                        sc->ChangeColor();
                        gameObject->collider = bc;
                        bc->gameObject = gameObject;
                        bc->size = QVector3D(1,1,1)*0.75f;
                        bc->isTrigger = true;
                        gameObject->components.push_back(sc);
                        (MainWidget::gameObjects).push_back(gameObject);
                        m->Compute(gameObject->transform);
                    }
                    else if (c == 'T')
                    {
                        m->Load("../ProjectMDJ/block.obj");
                        m->LoadTexture("../ProjectMDJ/mud.png");
                        gameObject->collider = bc;
                        bc->gameObject = gameObject;
                        (MainWidget::gameObjects).push_back(gameObject);
                        m->Compute(gameObject->transform);
                    }
                    else if (c == 'I')
                    {
                        m->Load("../ProjectMDJ/cloud.obj");
                        m->LoadTexture("../ProjectMDJ/white.png");

                        InvisibiltyComponent *ic = new InvisibiltyComponent();
                        ic->gameObject = gameObject;
                        gameObject->components.push_back(ic);

                        gameObject->collider = bc;
                        bc->gameObject = gameObject;
                        (MainWidget::gameObjects).push_back(gameObject);
                        m->Compute(gameObject->transform);
                    }
                    else if (c == '1')
                    {
                        m->Load("../ProjectMDJ/fullCube.obj");
                        m->LoadTexture("../ProjectMDJ/redBlock.png");

                        ColorBlockComponent *cbc = new ColorBlockComponent();

                        Mesh3D *m1 = new Mesh3D();
                        m1->Load("../ProjectMDJ/wiredCube.obj");
                        m1->LoadTexture("../ProjectMDJ/redBlock.png");
                        cbc->meshes.push_back(m1);

                        Mesh3D *m2 = new Mesh3D();
                        m2->Load("../ProjectMDJ/fullCube.obj");
                        m2->LoadTexture("../ProjectMDJ/redBlock.png");
                        cbc->meshes.push_back(m2);
                        gameObject->components.push_back(cbc);
                        cbc->gameObject = gameObject;
                        cbc->startState = false;

                        gameObject->collider = bc;
                        bc->gameObject = gameObject;
                        bc->isTrigger= true;
                        (MainWidget::gameObjects).push_back(gameObject);
                        m->Compute(gameObject->transform);
                    }
                    else if (c == '2')
                    {
                        m->Load("../ProjectMDJ/fullCube.obj");
                        m->LoadTexture("../ProjectMDJ/blueBlock.png");

                        ColorBlockComponent *cbc = new ColorBlockComponent();

                        Mesh3D *m1 = new Mesh3D();
                        m1->Load("../ProjectMDJ/wiredCube.obj");
                        m1->LoadTexture("../ProjectMDJ/blueBlock.png");
                        cbc->meshes.push_back(m1);

                        Mesh3D *m2 = new Mesh3D();
                        m2->Load("../ProjectMDJ/fullCube.obj");
                        m2->LoadTexture("../ProjectMDJ/blueBlock.png");
                        cbc->meshes.push_back(m2);
                        gameObject->components.push_back(cbc);
                        cbc->gameObject = gameObject;
                        cbc->startState = true;



                        gameObject->collider = bc;
                        bc->gameObject = gameObject;
                        bc->isTrigger= true;
                        (MainWidget::gameObjects).push_back(gameObject);
                        m->Compute(gameObject->transform);
                    }
                    else if (c == 'C')
                    {
                        m->Load("../ProjectMDJ/star.obj");
                        m->LoadTexture("../ProjectMDJ/gold.png");

                        gameObject->transform->eulerAngle = QVector3D(0,0,rand() * 50);
                        RotationComponent *rc = new RotationComponent();
                        rc->gameObject = gameObject;
                        gameObject->components.push_back(rc);

                        StarCollectComponent *scc = new StarCollectComponent();
                        scc->gameObject = gameObject;
                        gameObject->components.push_back(scc);
                        (MainWidget::gameObjects).push_back(gameObject);
                        m->Compute(gameObject->transform);
                    }
                    else if (c == 'c')
                    {
                        m->Load("../ProjectMDJ/star.obj");
                        m->LoadTexture("../ProjectMDJ/gold.png");

                        gameObject->transform->eulerAngle = QVector3D(0,0,rand() * 50);
                        RotationComponent *rc = new RotationComponent();
                        rc->gameObject = gameObject;
                        gameObject->components.push_back(rc);


                        InvisibiltyComponent *ic = new InvisibiltyComponent();
                        ic->gameObject = gameObject;
                        gameObject->components.push_back(ic);

                        StarCollectComponent *scc = new StarCollectComponent();
                        scc->gameObject = gameObject;
                        gameObject->components.push_back(scc);
                        (MainWidget::gameObjects).push_back(gameObject);
                        m->Compute(gameObject->transform);
                    }
                    else if (c == 'P')
                    {
                        MainWidget::startPosition = QVector3D(x*2, y*2, Z*2);

                    }
                    else {
                        std::cout << c << " letter not known ! " << std::endl;

                    }


                }


            }
            j++;


        }

    }

}
