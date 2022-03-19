#include "animation.h"

Animation::Animation(QObject *parent) : QThread(parent)
{

}

void Animation::run()
{
    while(true)
    {
        QMutex m;
        m.lock();
        if(this->first_animating == true)
        {
            this->msleep(1000 / multiplier);
            this->currently_animating = true;
            this->first_animating = false;
        }

        if(entering && duration_in != 0 && this->currently_animating)
        {
            emit move_entering_on_canvas(pos_in);
            duration_in--;
            if(duration_in == 0)
            {
                emit train_arrived_on_platform(pos_in, train_in);
                entering = false;
                pos_in = -1;
                train_in = nullptr;
            }
        }
        if(exiting && duration_out != 0 && this->currently_animating)
        {
            emit move_exiting_on_canvas(pos_out);
            duration_out--;
            if(duration_out == 0)
            {
                emit destroy_train(pos_out);
                exiting = false;
                pos_out = -1;
                train_out = nullptr;
            }
        }

        this->msleep(100 / multiplier);
        if(!entering && duration_in == 0 && !exiting && duration_out == 0)
            this->currently_animating = false;
        m.unlock();
    }
}

void Animation::start_animating(int pos, bool gate_in, Train* input)
{
    if(this->currently_animating != true)
        this->first_animating = true;
    if(gate_in)
    {
        this->entering = true;
        pos_in = pos;
        duration_in = GATE_IN_DURATION;
        train_in = input;
    }
    else
    {
        this->exiting =  true;
        pos_out = pos;
        duration_out = GATE_OUT_DURATION;
        train_out = input;
    }
}
