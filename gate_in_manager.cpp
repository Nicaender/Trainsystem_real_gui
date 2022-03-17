#include "gate_in_manager.h"

Gate_In_Manager::Gate_In_Manager(QObject *parent) : QThread(parent)
{

}

void Gate_In_Manager::run()
{
//    while(true)
//    {
//        m.lock();
//        if(incoming_train.empty())
//        {
//            qDebug() << "Ga ada kereta" << '\n';
//        }
//        else
//        {
//            qDebug() << "Kereta otw platform" << '\n';
//            this->add_train();
//        }
//        m.unlock();
//        this->sleep(2);
//    }
}

void Gate_In_Manager::add_train()
{
    for(int i = 0; i < PLATFORM_SUM; i++)
    {
        if(!platforms[i])
        {
            qDebug() << "Kereta masuk ke Platform" << '\n';
            emit train_coming(i,incoming_train.front());
            qDebug() << "masukin ke canvas" << '\n';
            platforms[i] = incoming_train.front();
            qDebug() << "cabut dari queue incoming_train" << '\n';
            incoming_train.pop();
//            this->sleep(GATE_IN_DURATION);
            return;
        }
    }
}

void Gate_In_Manager::on_new_train_notified(Train * input)
{
    incoming_train.push(input);
    this->add_train();
//    this->sleep(2);
}
