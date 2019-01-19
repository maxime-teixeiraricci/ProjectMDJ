#include "meshrenderer.h"
#include "mainwidget.h"

MeshRenderer* MeshRenderer::instance = new MeshRenderer();

MeshRenderer::MeshRenderer()
{
}

void MeshRenderer::Draw()
{
    initializeOpenGLFunctions();

    for (unsigned int i = 0; i < transitions.size(); i++)
    {

        int numberObjects = transitions[i].size();
        if (numberObjects > 0)
        {
            Mesh3D *mesh = meshes[i];
            unsigned int VAO = VAOs[i];
            unsigned int EBO = EBOs[i];


            unsigned int instanceVBO = instanceVBOs[i];

            glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(QMatrix4x4) * numberObjects, &transitions[i][0], GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            mesh->texture->bind();
            glBindVertexArray(VAO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glDrawArraysInstanced(GL_TRIANGLES, 0, mesh->outIndexData.size(), numberObjects);
            glBindVertexArray(0);
        }
    }
}

void MeshRenderer::Init()
{
    initializeOpenGLFunctions();
    if (!done)
    {
        done = true;
        VAOs = new unsigned int[transitions.size()];
        EBOs = new unsigned int[transitions.size()];
        instanceVBOs = new unsigned int[transitions.size()];
        vertexVBOs = new unsigned int[transitions.size()];

        glGenVertexArrays(transitions.size(), VAOs);
        glGenBuffers(transitions.size(), EBOs);
        glGenBuffers(transitions.size(), instanceVBOs);
        glGenBuffers(transitions.size(), vertexVBOs);
    }
    else
    {
        /*glDeleteVertexArrays(transitions.size(), VAOs);
        glDeleteBuffers(transitions.size(), EBOs);
        glDeleteBuffers(transitions.size(), instanceVBOs);
        glDeleteBuffers(transitions.size(), vertexVBOs);
        glGenVertexArrays(transitions.size(), VAOs);
        glGenBuffers(transitions.size(), EBOs);
        glGenBuffers(transitions.size(), instanceVBOs);
        glGenBuffers(transitions.size(), vertexVBOs);*/
    }
    for (unsigned int i = 0; i < transitions.size(); i++)
    {
        qDebug() << "Mesh: " << i << ": " << transitions[i].size();
        int numberObjects = transitions[i].size();
        if (numberObjects > -1)
        {
            Mesh3D *mesh = meshes[i];
            // Buffer de translations
            if (numberObjects == 0)
            {
                QMatrix4x4 mat;
                mat.setToIdentity();
                transitions[i] = {mat};
                numberObjects = 1;
            }



            int stride = sizeof(VertexData);
            unsigned int vertexVBO=vertexVBOs[i];
            unsigned int VAO = VAOs[i];
            unsigned int instanceVBO = instanceVBOs[i];

            //glGenBuffers(1, &vertexVBO);
            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData) * mesh->outVertexData.size(), mesh->outVertexData.data(), GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);


            glBindBuffer(GL_ARRAY_BUFFER, vertexVBO); // OPEN VBO
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)sizeof(QVector3D));
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(sizeof(QVector3D)+sizeof(QVector2D)));
            glEnableVertexAttribArray(3);
            glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(2*sizeof(QVector3D)+sizeof(QVector2D)));
            glBindBuffer(GL_ARRAY_BUFFER, 0);  // CLOSE VBO

            // Buffer de Matrix
            //unsigned int instanceVBO;
            //glGenBuffers(1, &instanceVBO);
            glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(QMatrix4x4) * numberObjects, &transitions[i][0], GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
            glEnableVertexAttribArray(4);
            glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(QMatrix4x4), (void*)0);
            glEnableVertexAttribArray(5);
            glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(QMatrix4x4), (void*)(sizeof(QVector4D)));
            glEnableVertexAttribArray(6);
            glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(QMatrix4x4), (void*)(2*sizeof(QVector4D)));
            glEnableVertexAttribArray(7);
            glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(QMatrix4x4), (void*)(3*sizeof(QVector4D)));

            glVertexAttribDivisor(4, 1);
            glVertexAttribDivisor(5, 1);
            glVertexAttribDivisor(6, 1);
            glVertexAttribDivisor(7, 1);

            glBindBuffer(GL_ARRAY_BUFFER, 0);

            unsigned int EBO = EBOs[i];
            //glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(VertexData) * mesh->outVertexData.size(), mesh->outVertexData.data(), GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        }
    }
}



void MeshRenderer::ComputeGameObject()
{
    transitions.clear();
    for (unsigned int i = 0; i < meshes.size(); i++)
    {
        transitions.push_back(std::vector<QMatrix4x4>());
    }

    for (unsigned int i = 0; i < MainWidget::gameObjects.size(); i++)
    {
        GameObject *gameObject = MainWidget::gameObjects.at(i);
        gameObject->meshInstanceId = -1;
        if (gameObject->meshId >= 0 && gameObject->meshId < meshes.size() && gameObject->isDrawable)
        {
            gameObject->transform->getMatrix();
            gameObject->meshInstanceId = transitions[gameObject->meshId].size();
            transitions[gameObject->meshId].push_back(gameObject->transform->transformMatrix);
        }
    }



}


