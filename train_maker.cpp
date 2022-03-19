#include "train_maker.h"

Train_maker::Train_maker(QObject *parent) : QThread(parent)
{

}

void Train_maker::run()
{
    LARGE_INTEGER cicles;
    QueryPerformanceCounter(&cicles);
    srand(cicles.QuadPart);
    while(true)
    {
        QMutex m;
        m.lock();
        Train* new_train = new Train((1+rand()%99), rand()%30);
        emit notify_gate_in(new_train);
        this->msleep(this->trail_interval / multiplier);
        m.unlock();
    }
}
