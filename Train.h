#ifndef TRAIN_H
#define TRAIN_H

#include <unistd.h>

static int id_counter = 0;

class Train
{
public:
    Train(int _duration);

    int getStop_duration() const;

    int getId() const;

    void setStop_duration(int newStop_duration);

    int platform;

    void execute_sleep();

private:
    int id;
    int stop_duration;
};

#endif // TRAIN_H
