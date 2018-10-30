#ifndef TIMER_MANAGER_H
#define TIMER_MANAGER_H

#include <QBasicTimer>

class timer_manager : QBasicTimer
{
public:
    timer_manager(double value);
    //~timer_manager();
    void startTimer(QObject *obj);
    void stopTimer();
    bool isActive();
    int getID();
    int getValue();
    void setLabel(QString str);

private:
    QBasicTimer timer;
    double value;

};

#endif // TIMER_MANAGER_H
