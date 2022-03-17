#include "gate_in_manager.h"

Gate_In_Manager::Gate_In_Manager(QObject *parent) : QThread(parent)
{

}

void Gate_In_Manager::run()
{
    while(true)
    {
        // cek kereta masuk && pintu masuk free && ada platform free
        if(!incoming_train.empty() && train_in_cooldown == 0 && this->check_free_platform() != -1)
        {
            qDebug() << "Kereta otw platform" << '\n';
            this->notify_train_into_platform(this->check_free_platform());
            train_in_cooldown = GATE_IN_DURATION;
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

        // kalau ada yang di queue keluar
        if(!outcoming_train_pos.empty() && train_out_cooldown == 0)
        {
            qDebug() << "Kereta keluar dari platform" << '\n';
            this->notify_train_exiting_platform(outcoming_train_pos.front());
            train_out_cooldown = GATE_OUT_DURATION + GATE_OUT_OUT;
        }

        qDebug() << "Urutan keluar: ";
        for(unsigned int i = 0; i < outcoming_train_pos.size(); i++)
        {
            if(platforms[i])
                qDebug() << "Train " << platforms[outcoming_train_pos[i]]->getId();
        }
        qDebug() << '\n';
        this->sleep(1);
        if(train_in_cooldown > 0)
            train_in_cooldown--;
        if(train_out_cooldown > 0)
            train_out_cooldown--;
    }
}

void Gate_In_Manager::notify_train_into_platform(int pos)
{
    platforms[pos] = incoming_train.front();
    incoming_train.pop();
    emit train_in_entrance(pos, platforms[pos]);
    platforms[pos]->add_duration(GATE_IN_DURATION);
    emit notify_animation(pos, true);
    return;
}

void Gate_In_Manager::notify_train_exiting_platform(int pos)
{
    emit notify_animation(pos, false);
    return;
}

void Gate_In_Manager::notified_to_remove_train(int pos) // delete kalo udah disuruh animation
{
    delete platforms[pos];
    platforms[pos] = nullptr;
    outcoming_train_pos.pop_front();
    emit notify_canvas_to_destroy_train(pos);
    return;
}

void Gate_In_Manager::on_new_train_notified(Train * input)
{
    incoming_train.push(input);
}

void Gate_In_Manager::path_clear(bool)
{

}

int Gate_In_Manager::check_free_platform()
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
