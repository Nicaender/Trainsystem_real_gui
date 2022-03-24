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
        if(!this->path_list.empty())
        {
            Infrastructure *tmp_before, *tmp_after;
            for(unsigned int i = 0; i < path_list.size(); i++)
            {
                tmp_before = path_list[i].front();
                path_list[i].pop_front();
                tmp_after = path_list[i].front();
                tmp_after->setTrain(tmp_before->getTrain());
                tmp_before->setTrain(nullptr);
                if(path_list[i].size() == 1)
                {
                    while(!copy_path_list[i].empty())
                    {
                        copy_path_list[i].front()->setOccupied(false);
                        copy_path_list[i].pop_front();
                    }
                    copy_path_list.erase(copy_path_list.begin() + i);
                    path_list.erase(path_list.begin() + i);
                    emit notify_train_arrived(tmp_after);
                    i--;
                }
            }
            this->msleep(1000 / multiplier);
        }
        m.unlock();
    }
}

void Animation::notified_train_depart(std::deque<Infrastructure *> *path)
{
    this->path_list.push_back(*path);
    this->copy_path_list.push_back(*path);
    delete path;
    return;
}

void Animation::setMultiplier(int newMultiplier)
{
    this->multiplier = newMultiplier;
}
