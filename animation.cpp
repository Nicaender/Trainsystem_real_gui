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
            Infrastructure *before;
            for(unsigned int i = 0; i < path_list.size(); i++)
            {
                if(path_list[i].first.first.size() != 1)
                {
                before = path_list[i].first.first.front();
                path_list[i].first.first.pop_front();
                path_list[i].second->setBefore_x(before->getX());
                path_list[i].second->setBefore_y(before->getY());
                emit notify_move_train(path_list[i].second, path_list[i].first.first.front());
                }
            }
            for(unsigned int i = 0; i < path_list.size(); i++)
            {
                if(path_list[i].first.first.size() == 1)
                {
                    for(unsigned int j = 0; j < path_list[i].first.second.size(); j++)
                    {
                        path_list[i].first.second[j]->setOccupied(false);
                    }
                    path_list[i].first.first.front()->setOccupied(true);
                    path_list[i].second->add_duration(path_list[i].first.first.front()->getStay());
                    emit notify_train_arrived(path_list[i].second, path_list[i].first.second.front(), path_list[i].first.first.front());
                    path_list.erase(path_list.begin() + i);
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
    this->path_list.push_back({{*path, *path}, path->front()->getTrain()});
    delete path;
    return;
}

void Animation::setMultiplier(int newMultiplier)
{
    this->multiplier = newMultiplier;
}
