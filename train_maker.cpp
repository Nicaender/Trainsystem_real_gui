#include "train_maker.h"

Train_maker::Train_maker(QObject *parent) : QThread(parent)
{

}

void Train_maker::run()
{
    while(true)
    {
        this->sleep(5);
        Train* new_train = new Train(1+rand()%100, 1+rand()%10);
        qDebug() << "Kereta masuk" << '\n';
        emit notify_new_train(new_train);
//        m.lock();
//        incoming_train.push(new_train);
//        m.unlock();
    }
}
