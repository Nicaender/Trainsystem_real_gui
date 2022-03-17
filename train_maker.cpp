#include "train_maker.h"

Train_maker::Train_maker(QObject *parent) : QThread(parent)
{

}

void Train_maker::run()
{
    while(true)
    {
        qDebug() << train_interval << '\n';
        this->sleep(train_interval);
        Train* new_train = new Train(1+rand()%100, 20);
//        qDebug() << "Kereta masuk" << '\n';
        emit notify_gate_in(new_train);
    }
}
