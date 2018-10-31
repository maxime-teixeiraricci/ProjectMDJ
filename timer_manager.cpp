#include "timer_manager.h"
#include <QTimer>

timer_manager::timer_manager(double value)
{
    this->value = 1.0/value*1000;
}

// Start the FPS timer
void timer_manager::startTimer(QObject *obj)
{
    timer.start(value, obj);
}

// Stop the timer
void timer_manager::stopTimer()
{
    timer.stop();
}

// Check if the timer is active. True if it is, false if it isn't
bool timer_manager::isActive()
{
    return timer.isActive();
}

// Return the ID of the timer
int timer_manager::getID()
{
    return timer.timerId();
}

// Get the frequency
int timer_manager::getValue()
{
   return value;
}
