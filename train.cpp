#include "train.h"

Train::Train(int id)
{
    this->id = id;
}

void Train::stop_reduction()
{
    this->stop_duration--;
}

int Train::getId() const
{
    return id;
}

void Train::add_duration(int duration)
{
    this->stop_duration += duration;
}

int Train::getStop_duration() const
{
    return stop_duration;
}

bool Train::getOut_waiting_list() const
{
    return out_waiting_list;
}

void Train::setOut_waiting_list(bool newOut_waiting_list)
{
    out_waiting_list = newOut_waiting_list;
}
