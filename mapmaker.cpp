#include "mapmaker.h"
#include <iostream>
#include <QFile>

#include "rotationcomponent.h"
#include "starcollectcomponent.h"
#include "boxcollidercomponent.h"

#include <stdlib.h>

MapMaker::MapMaker()
{

}

void  MapMaker::CreateLevel(QString mapfile)
{

    MainWidget::gameObjects.clear();
    QFile file(mapfile);
    file.open(QFile::ReadOnly);

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


                    switch (c)
                    {
                    case 'H':  // Block d'herbe
                        m->Load("../ProjectMDJ/block.obj");
                        m->LoadTexture("../ProjectMDJ/grass.png");
                        gameObject->collider = bc;
                        bc->gameObject = gameObject;

                        break;
                    case 'W':  // Block d'eau
                        m->Load("../ProjectMDJ/block.obj");
                        m->LoadTexture("../ProjectMDJ/grass.png");
                        gameObject->collider = bc;
                        bc->gameObject = gameObject;
                        break;
                    case 'S':  // Block en pente
                        m->Load("../ProjectMDJ/slope.obj");
                        m->LoadTexture("../ProjectMDJ/grass.png");
                        gameObject->collider = bc;
                        bc->gameObject = gameObject;
                        break;
                    case 'T':  // Block en terre
                        m->Load("../ProjectMDJ/block.obj");
                        m->LoadTexture("../ProjectMDJ/mud.png");
                        gameObject->collider = bc;
                        bc->gameObject = gameObject;
                        break;
                    case '1':
                        m->Load("../ProjectMDJ/wiredCube.obj");
                        m->LoadTexture("../ProjectMDJ/redBlock.png");

                        break;
                    case '2':
                        m->Load("../ProjectMDJ/wiredCube.obj");
                        m->LoadTexture("../ProjectMDJ/blueBlock.png");

                        break;
                    case 'C':
                        m->Load("../ProjectMDJ/star.obj");
                        m->LoadTexture("../ProjectMDJ/gold.png");

                        gameObject->transform->eulerAngle = QVector3D(0,0,rand() * 50);
                        RotationComponent *rc = new RotationComponent();
                        rc->gameObject = gameObject;
                        gameObject->components.push_back(rc);

                        StarCollectComponent *scc = new StarCollectComponent();
                        scc->gameObject = gameObject;
                        gameObject->components.push_back(scc);
                        break;

                    }
                    (MainWidget::gameObjects).push_back(gameObject);
                    m->Compute(gameObject->transform);
                }


            }
            j++;


        }

    }

}
