#include "inputmapping.h"

InputMapping::InputMapping()
{
    for (int i = 0; i < list.size(); ++i) {
        inputMap[list[i]] = 0.0;
    }
    inputMap["cameraZoom"] = 20.0;
}

void InputMapping::printMap()
{
    QMapIterator<QString, float> i(inputMap);
    while (i.hasNext()) {
        i.next();
        printf("%s : %f\n",i.key().toLatin1().constData(),i.value());
    }
}
