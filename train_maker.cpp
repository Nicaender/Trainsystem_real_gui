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
        while(pause)
        {
            this->msleep(20);
        }
        QMutex m;
        m.lock();
        if(counter > 0)
            counter--;
        if(counter == 0 && !halt)
        {
            Train* new_train = new Train((1+rand()%999));
            counter = this->train_interval;
            qDebug() << QString::fromStdString("Train ") + QString::number(new_train->getId()) + " is coming";
            emit notify_train_incoming(new_train);
        }
        this->usleep(1000000 / multiplier);
        m.unlock();
    }
}

void Train_maker::setTrain_interval(int newTrain_interval)
{
    train_interval = newTrain_interval;
}

void Train_maker::notified_incoming_train_full(bool input)
{
    this->halt = input;
}

bool Train_maker::get_pause() const
{
    return pause;
}

void Train_maker::set_pause(bool new_pause)
{
    pause = new_pause;
}

void Train_maker::set_multiplier(int new_multiplier)
{
    multiplier = new_multiplier;
}
