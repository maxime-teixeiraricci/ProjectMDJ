#include "mapmaker.h"
#include <iostream>
#include <QFile>

#include "rotationcomponent.h"
#include "starcollectcomponent.h"
#include "boxcollidercomponent.h"
#include "switchcomponent.h"
#include "colorblockcomponent.h"
#include "invisibiltycomponent.h"
#include "meshrenderer.h"

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
    InstantiateMesh();
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

                    //Mesh3D *m = new Mesh3D();
                    GameObject *gameObject = new GameObject();
                    float x = -(X/2.0) + i;
                    float y = -(Y/2.0) + j;
                    gameObject->transform->position = QVector3D(x*2, y*2, Z*2);
                    BoxColliderComponent *bc = new BoxColliderComponent();
                    bc->size = QVector3D(1,1,1);


                    bc->center = gameObject->transform->position;

                    if (c == 'H')
                    {
                        gameObject->collider = bc;
                        gameObject->meshId = 0;
                        bc->gameObject = gameObject;
                        gameObject->transform->getMatrix();
                        (MainWidget::gameObjects).push_back(gameObject);
                        //m->Compute(gameObject->transform);
                    }
                    else if (c == 'X')
                    {

                        gameObject->collider = bc;
                        bc->size = QVector3D(1,1,1)*0.99f;

                        bc->gameObject = gameObject;
                        GravityComponent *gc = new GravityComponent();
                        gc->gameObject = gameObject;
                        gameObject->components.push_back(gc);
                        gameObject->transform->scale *= 0.99f;
                        gameObject->meshId = 1;
                        (MainWidget::gameObjects).push_back(gameObject);
                    }
                    else if (c == 'Q')
                    {
                        //m->Load("../ProjectMDJ/switchUp.obj");
                        //m->LoadTexture("../ProjectMDJ/redSwitch.png");
                        SwitchComponent *sc = new SwitchComponent();
                        sc->gameObject = gameObject;
                        sc->startState = false;
                        sc->ChangeColor();
                        gameObject->collider = bc;
                        bc->gameObject = gameObject;
                        bc->size = QVector3D(1,1,1)*0.75f;
                        bc->isTrigger = true;
                        gameObject->meshId = 6;
                        gameObject->components.push_back(sc);
                        (MainWidget::gameObjects).push_back(gameObject);

                    }
                    else if (c == 'Z')
                    {
                        //m->Load("../ProjectMDJ/switchUp.obj");
                        //m->LoadTexture("../ProjectMDJ/blueSwitch.png");
                        SwitchComponent *sc = new SwitchComponent();
                        sc->gameObject = gameObject;
                        sc->startState = true;
                        sc->ChangeColor();
                        gameObject->collider = bc;
                        bc->gameObject = gameObject;
                        bc->size = QVector3D(1,1,1)*0.75f;
                        bc->isTrigger = true;
                        gameObject->meshId =7;
                        gameObject->components.push_back(sc);
                        (MainWidget::gameObjects).push_back(gameObject);
                        //m->Compute(gameObject->transform);
                    }
                    else if (c == 'I')
                    {

                        InvisibiltyComponent *ic = new InvisibiltyComponent();
                        ic->gameObject = gameObject;
                        gameObject->components.push_back(ic);
                        gameObject->meshId = 9;
                        gameObject->collider = bc;
                        bc->gameObject = gameObject;
                        (MainWidget::gameObjects).push_back(gameObject);
                        //m->Compute(gameObject->transform);
                    }
                    else if (c == '1')
                    {
                        //m->Load("../ProjectMDJ/fullCube.obj");
                        //m->LoadTexture("../ProjectMDJ/redBlock.png");

                        ColorBlockComponent *cbc = new ColorBlockComponent();


                        gameObject->components.push_back(cbc);
                        cbc->gameObject = gameObject;
                        cbc->startState = false;

                        gameObject->collider = bc;
                        bc->gameObject = gameObject;
                        bc->isTrigger= true;
                        (MainWidget::gameObjects).push_back(gameObject);
                        //m->Compute(gameObject->transform);
                    }
                    else if (c == '2')
                    {
                        //m->Load("../ProjectMDJ/fullCube.obj");
                        //m->LoadTexture("../ProjectMDJ/blueBlock.png");

                        ColorBlockComponent *cbc = new ColorBlockComponent();


                        gameObject->components.push_back(cbc);
                        cbc->gameObject = gameObject;
                        cbc->startState = true;


                        gameObject->collider = bc;
                        bc->gameObject = gameObject;
                        bc->isTrigger= true;
                        (MainWidget::gameObjects).push_back(gameObject);
                        //m->Compute(gameObject->transform);
                    }
                    else if (c == 'C')
                    {
                        //m->Load("../ProjectMDJ/star.obj");
                        //m->LoadTexture("../ProjectMDJ/gold.png");

                        gameObject->transform->eulerAngle = QVector3D(0,0,rand() * 50);
                        RotationComponent *rc = new RotationComponent();
                        rc->gameObject = gameObject;
                        gameObject->components.push_back(rc);

                        StarCollectComponent *scc = new StarCollectComponent();
                        scc->gameObject = gameObject;

                        gameObject->components.push_back(scc);

                        gameObject->meshId = 8;
                        (MainWidget::gameObjects).push_back(gameObject);
                        //m->Compute(gameObject->transform);

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

void MapMaker::InstantiateMesh()
{
    Mesh3D *m;
    Transform *t = new Transform();
    t->position = QVector3D(0,0,0);

    // 0 - GRASS BLOCK (H)
    MeshRenderer::instance->meshes.push_back(new Mesh3D());
    m = MeshRenderer::instance->meshes[MeshRenderer::instance->meshes.size()-1];
    m->Load("../ProjectMDJ/block.obj");
    m->LoadTexture("../ProjectMDJ/grass.png");
    m->Compute(t);


    // 1 - MOVABLE BLOCK (X)
    MeshRenderer::instance->meshes.push_back(new Mesh3D());
    m = MeshRenderer::instance->meshes[MeshRenderer::instance->meshes.size()-1];
    t->position = QVector3D(0,0,0);
    m->Load("../ProjectMDJ/block.obj");
    m->LoadTexture("../ProjectMDJ/block.png");
    m->Compute(t);


    // 2 - WIRED BLOCK BLUE (2)
    MeshRenderer::instance->meshes.push_back(new Mesh3D());
    m = MeshRenderer::instance->meshes[MeshRenderer::instance->meshes.size()-1];
    m->Load("../ProjectMDJ/wiredCube.obj");
    m->LoadTexture("../ProjectMDJ/blueBlock.png");
    m->Compute(t);

    // 3 - FULL BLOCK BLUE (3)
    MeshRenderer::instance->meshes.push_back(new Mesh3D());
    m = MeshRenderer::instance->meshes[MeshRenderer::instance->meshes.size()-1];
    m->Load("../ProjectMDJ/fullCube.obj");
    m->LoadTexture("../ProjectMDJ/blueBlock.png");
    m->Compute(t);

    // 4 - WIRED BLOCK RED (?)
    MeshRenderer::instance->meshes.push_back(new Mesh3D());
    m = MeshRenderer::instance->meshes[MeshRenderer::instance->meshes.size()-1];
    m->Load("../ProjectMDJ/wiredCube.obj");
    m->LoadTexture("../ProjectMDJ/redBlock.png");
    m->Compute(t);

    // 5 - FULL BLOCK RED (?)
    MeshRenderer::instance->meshes.push_back(new Mesh3D());
    m = MeshRenderer::instance->meshes[MeshRenderer::instance->meshes.size()-1];
    m->Load("../ProjectMDJ/fullCube.obj");
    m->LoadTexture("../ProjectMDJ/redBlock.png");
    m->Compute(t);

    // 6 - SWITCH UP RED (Q)
    MeshRenderer::instance->meshes.push_back(new Mesh3D());
    m = MeshRenderer::instance->meshes[MeshRenderer::instance->meshes.size()-1];
    m->Load("../ProjectMDJ/switchUp.obj");
    m->LoadTexture("../ProjectMDJ/redSwitch.png");
    m->Compute(t);

    // 7 - SWITCH UP BLUE (Z)
    MeshRenderer::instance->meshes.push_back(new Mesh3D());
    m = MeshRenderer::instance->meshes[MeshRenderer::instance->meshes.size()-1];
    m->Load("../ProjectMDJ/switchUp.obj");
    m->LoadTexture("../ProjectMDJ/blueSwitch.png");
    m->Compute(t);

    // 8 - STAR (C)
    MeshRenderer::instance->meshes.push_back(new Mesh3D());
    m = MeshRenderer::instance->meshes[MeshRenderer::instance->meshes.size()-1];
    m->Load("../ProjectMDJ/star.obj");
    m->LoadTexture("../ProjectMDJ/gold.png");
    m->Compute(t);

    // 9 - INVISIBLE BLOCK (I)
    MeshRenderer::instance->meshes.push_back(new Mesh3D());
    m = MeshRenderer::instance->meshes[MeshRenderer::instance->meshes.size()-1];
    m->Load("../ProjectMDJ/cloud.obj");
    m->LoadTexture("../ProjectMDJ/white.png");
    m->Compute(t);

}
