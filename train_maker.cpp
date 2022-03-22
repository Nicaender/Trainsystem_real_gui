#include "train_maker.h"

Train_maker::Train_maker(QObject *parent) : QThread(parent)
{

}

void Train_maker::run()
{
    LARGE_INTEGER cicles;
    QueryPerformanceCounter(&cicles);
    srand(cicles.QuadPart);
    int counter = 0;
    while(true)
    {
        QMutex m;
        m.lock();
        if(counter != 0)
            counter--;
        if(counter == 0)
        {
            Train* new_train = new Train((1+rand()%999));
            counter = this->train_interval;
            emit notify_gate_in(new_train);
        }
        this->msleep(1000 / multiplier);
        m.unlock();
    }
}

void Train_maker::setMultiplier(int newMultiplier)
{
    this->multiplier = newMultiplier;
}

void Train_maker::setStay_duration(int newStay_duration)
{
    stay_duration = newStay_duration;
}

void Train_maker::setTrain_interval(int newTrain_interval)
{
    train_interval = newTrain_interval;
}
