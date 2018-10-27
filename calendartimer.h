#ifndef CALENDARTIMER_H
#define CALENDARTIMER_H
#include <QObject>

class CalendarTimer : public QObject
{
public:
    CalendarTimer();
    float value;
    float changeValue;

private:
    void AddTime();


signals:
     void valueChanged(int newValeur);
};

#endif // CALENDARTIMER_H
