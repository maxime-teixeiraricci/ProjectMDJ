#include "inputmapping.h"
#include "iostream"

InputMapping::InputMapping()
{
    for (int i = 0; i < list.size(); ++i) {
        inputMap[list[i]] = 0.0;
    }
    inputMap["cameraZoom"] = 20.0;
}

void InputMapping::reset()
{
    for (int i = 0; i < inputMap.size(); i ++)
    {
        QString s = inputMap.keys()[i];
        inputMap[s] = 0;
    }
}


void InputMapping::printMap()
{
    QMapIterator<QString, float> i(inputMap);
    while (i.hasNext()) {
        i.next();
        std::cout << i.key().toLatin1().constData() << ":" << i.value() << std::endl;
    }
}
