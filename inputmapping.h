#ifndef INPUTMAPPING_H
#define INPUTMAPPING_H
#include "QMap"
#include "QString"

class InputMapping
{
public:
    InputMapping();
    QMap<QString,float> inputMap;
    QList<QString> list = {"up","down","left","right","jump","gravity","axisHori","axisVerti","cameraZoom","cameraInertie","cameraZ"};
    void reset();
    void printMap();
};  
#endif // INPUTMAPPING_H
