#include "train.h"

Train::Train(int id, int stop)
{
    this->id = id;
    this->stop_duration = stop;
}

void Train::stop_reduction()
{
    this->stop_duration--;
}

int Train::getId() const
{
    return id;
}

int Train::getStop_duration() const
{
    return stop_duration;
}
