#include "gate_in_manager.h"

Gate_In_Manager::Gate_In_Manager(QObject *parent) : QThread(parent)
{
    for(int i = 0; i < PLATFORM_SUM; i++)
        platforms[i] = nullptr;
}

void Gate_In_Manager::run()
{
    int tmp_cooldown = -1;
    while(true)
    {
        QMutex m;
        m.lock();
        emit time_update(this->timer);
        timer++;
        tmp_cooldown = train_out_cooldown;
        if(tmp_cooldown == 1)
        {
            gate_out_ready = true;
        }
        if(tmp_cooldown == 0)
            train_out_cooldown = -1;

        // kurangin stay duration setiap kereta di platform
        for(int i = 0; i < PLATFORM_SUM; i++)
        {
            if(platforms[i])
            {
                if(platforms[i]->getStop_duration() > 0)
                    platforms[i]->stop_reduction();
                if(platforms[i]->getStop_duration() == 0 && platforms[i]->getOut_waiting_list() == false)
                {
                    outcoming_train_pos.push_back(i);
                    platforms[i]->setOut_waiting_list(true);
                    emit change_color_to_red(i);
                }
            }
        }

        // kalo ada kereta yang mau masuk, dan gate in ready, dan ada platform kosong, masukin ke platform
        if(!incoming_train.empty() && gate_in_ready && this->check_free_platform() != -1)
        {
            this->notify_train_into_platform(this->check_free_platform());
            gate_in_ready = false;
        }

        // kalau ada yang di queue keluar
        if(!outcoming_train_pos.empty() && gate_out_ready)
        {
            this->notify_train_exiting_platform(outcoming_train_pos.front(), platforms[outcoming_train_pos.front()]);
            gate_out_ready = false;
        }

        if(tmp_cooldown > 0)
        {
            tmp_cooldown--;
            train_out_cooldown--;
            emit update_cooldown_canvas(tmp_cooldown);
        }
        this->msleep(1000 / multiplier);
        m.unlock();
    }
}

void Gate_In_Manager::notify_train_into_platform(int pos) // finished - tell animation and mainwindow to move the train
{
    std::string in_waiting_list = "Next Train: ";
    Train* tmp = incoming_train.front();
    incoming_train.pop_front();
    emit train_in_entrance(pos, tmp);
    for(unsigned int i = 0; i < incoming_train.size(); i++)
        in_waiting_list.append("Train " + std::to_string(incoming_train[i]->getId()) + ", ");
    emit update_in_waiting_list(QString::fromStdString(in_waiting_list));
    return;
}

void Gate_In_Manager::notify_train_exiting_platform(int pos, Train* input) // finished - tell animation and mainwindow to move the train
{
    emit notify_animation(pos, false, input);
    outcoming_train_pos.pop_front();
    return;
}

void Gate_In_Manager::setGate_out_cooldown(int newGate_out_cooldown)
{
    gate_out_cooldown = newGate_out_cooldown;
}

void Gate_In_Manager::notified_to_remove_train(int pos) // finished - delete the train after the train leaves the station
{
    delete platforms[pos];
    platforms[pos] = nullptr;
    train_out_cooldown = gate_out_cooldown;
    emit update_cooldown_canvas(train_out_cooldown);
    return;
}

void Gate_In_Manager::on_new_train_notified(Train* input) // finished - put a train in waiting list
{
    incoming_train.push_back(input);
    std::string in_waiting_list = "Next Train: ";
    for(unsigned int i = 0; i < incoming_train.size(); i++)
        in_waiting_list.append("Train " + std::to_string(incoming_train[i]->getId()) + ", ");
    emit update_in_waiting_list(QString::fromStdString(in_waiting_list));
    return;
}

void Gate_In_Manager::set_train_on_platform(int pos, Train* input) // help function - akan dipanggil oleh animation kalau sudah sampai kesana
{
    platforms[pos] = input;
    gate_in_ready = true;
    return;
}

int Gate_In_Manager::check_free_platform() // help function - check available platform
{
    // cari platform yang kosong
    for(int i = 0; i < PLATFORM_SUM; i++)
    {
        if(!platforms[i])
        {
            return i;
        }
    }
    return -1;
}

void Gate_In_Manager::setMultiplier(int newMultiplier)
{
    this->multiplier = newMultiplier;
}
