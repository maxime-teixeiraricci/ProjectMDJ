#ifndef INPUTMAPPING_H
#define INPUTMAPPING_H
#include "QMap"
#include "QString"
#include "iostream"

class InputMapping
{
public:
    InputMapping();
    static QMap<QString,float> inputMap;
    static void Reset()
    {
        for (int i = 0; i < inputMap.size(); i ++)
        {
            QString s = inputMap.keys()[i];
            inputMap[s] = 0;
        }
    }
    static void Print()
    {
        QMapIterator<QString, float> i(inputMap);
        while (i.hasNext()) {
            i.next();
            std::cout << i.key().toLatin1().constData() << ":" << i.value() << std::endl;
        }
        for (int i = 0; i < inputMap.size(); i ++)
        {
            QString s = inputMap.keys()[i];
            std::cout << s.constData() << ":" << inputMap[s] << std::endl;
        }
    }
};  
#endif // INPUTMAPPING_H
