#include "mapmaker.h"
#include <iostream>
#include <QFile>


MapMaker::MapMaker()
{

}

void  MapMaker::CreateLevel(QString mapfile,std::vector<GameObject*> *resList)
{

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
            std::cout <<"Z : "<< Z << std::endl;
        }
        else
        {
            std::cout <<"J : "<< j << std::endl;
            for (unsigned int i = 0; i < X; i++)
            {
                char c = lineHeader[i];

                if ((int) c == 13)
                {
                    std::cout <<"OK"<< std::endl;
                    break;
                }
                if (c != 'O')
                {

                    Mesh3D *m = new Mesh3D();
                    switch (c)
                    {
                    case 'H':  // Block d'herbe
                        m->Load("../ProjectMDJ/block.obj");
                        m->LoadTexture("../ProjectMDJ/grass.png");
                        break;
                    case 'W':  // Block d'eau
                        m->Load("../ProjectMDJ/block.obj");
                        m->LoadTexture("../ProjectMDJ/grass.png");
                        break;
                    case 'S':  // Block en pente
                        m->Load("../ProjectMDJ/slope.obj");
                        m->LoadTexture("../ProjectMDJ/grass.png");
                        break;
                    case 'T':  // Block en pente
                        m->Load("../ProjectMDJ/block.obj");
                        m->LoadTexture("../ProjectMDJ/mud.png");
                        break;
                    }
                    resList->push_back(new GameObject(m));
                    std::cout << c <<" " << (int)c << " - "<<resList->size() << std::endl;
                    float x = i;//-(X/2) + i;
                    float y = j;//-(Y/2) + j;
                    resList->at(resList->size() - 1)->transform->position = QVector3D(x*2, y*2, Z*2);
                }


            }
            j++;


        }

    }
    std::cout << "Taille liste : " << resList->size() << std::endl;

}
