#include "gate_in_manager.h"

Gate_In_Manager::Gate_In_Manager(QObject *parent) : QThread(parent)
{
    for(int i = 0; i < PLATFORM_SUM; i++)
        platforms[i] = nullptr;
}

void Gate_In_Manager::run()
{
    while(true)
    {
        if(train_out_cooldown == 0)
        {
            gate_out_ready = true;
            train_out_cooldown = -1;
        }

        // kurangin stay duration setiap kereta di platform
        for(int i = 0; i < PLATFORM_SUM; i++)
        {
            if(platforms[i])
            {
                platforms[i]->stop_reduction();
                if(platforms[i]->getStop_duration() == 0)
                {
                    outcoming_train_pos.push_back(i);
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
        if(train_out_cooldown >= 0)
            emit update_cooldown_canvas(train_out_cooldown);
        this->sleep(1);
        if(train_out_cooldown > 0)
        {
            train_out_cooldown--;
            emit update_cooldown_canvas(train_out_cooldown);
        }
    }
}

void Gate_In_Manager::notify_train_into_platform(int pos) // finished - tell animation and mainwindow to move the train
{
    Train* tmp = incoming_train.front();
    incoming_train.pop();
    emit train_in_entrance(pos, tmp);
    emit notify_animation(pos, true, tmp);
    return;
}

void Gate_In_Manager::notify_train_exiting_platform(int pos, Train* input) // finished - tell animation and mainwindow to move the train
{
    emit notify_animation(pos, false, input);
    outcoming_train_pos.pop_front();
    return;
}

void Gate_In_Manager::notified_to_remove_train(int pos) // unfinished - delete the train after the train leaves the station
{
    delete platforms[pos];
    platforms[pos] = nullptr;
    train_out_cooldown = GATE_OUT_COOLDOWN;
    emit update_cooldown_canvas(train_out_cooldown);
    return;
}

void Gate_In_Manager::on_new_train_notified(Train* input) // finished - put a train in waiting list
{
    incoming_train.push(input);
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
