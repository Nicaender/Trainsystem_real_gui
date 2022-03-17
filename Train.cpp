#include "Train.h"

Train::Train(int _duration)
    :
      id(++id_counter),
      stop_duration(_duration)
{
}

int Train::getStop_duration() const
{
    return stop_duration;
}

int Train::getId() const
{
    return id;
}

void Train::setStop_duration(int newStop_duration)
{
    stop_duration = newStop_duration;
}

void Train::execute_sleep()
{
    sleep(stop_duration);
    stop_duration = 0;
}
