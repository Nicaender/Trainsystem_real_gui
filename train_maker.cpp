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
            Train* new_train = new Train((1+rand()%999), (7 * rand()) % 100); //
            counter = this->trail_interval;
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
