#include "animation.h"

Animation::Animation(QObject *parent) : QThread(parent)
{

}

void Animation::run()
{
    while(true)
    {
        if(entering && duration_in != 0)
        {
            emit move_entering_on_canvas(pos_in);
            duration_in--;
//            qDebug() << "Duration-in: " << duration_in << '\n';
            if(duration_in == 0)
            {
                entering = false;
                pos_in = -1;
            }
        }
        if(exiting && duration_out != 0)
        {
            emit move_exiting_on_canvas(pos_out);
            duration_out--;
//            qDebug() << "Duration-out: " << duration_in << '\n';
            if(duration_out == 0)
            {
                emit destroy_train(pos_out);
                exiting = false;
                pos_out = -1;
            }
        }

        this->sleep(1);
    }
}

void Animation::start_animating(int pos, bool gate_in)
{
    qDebug() << "start_animation_entering received" << '\n';
    if(gate_in)
    {
        this->entering = true;
        pos_in = pos;
        duration_in = GATE_IN_DURATION;
    }
    else
    {
        this->exiting =  true;
        pos_out = pos;
        duration_out = GATE_OUT_DURATION;
    }
}
