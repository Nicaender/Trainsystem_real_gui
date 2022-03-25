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
                        if(path_list[i].first.second[j]->getType() == 0)
                            emit notify_color(path_list[i].first.second[j]->getX(), path_list[i].first.second[j]->getY(), path_list[i].first.second[j]->getType());
                    }
                    path_list[i].first.first.front()->setOccupied(true);
                    path_list[i].second->add_duration(path_list[i].first.first.front()->getStay());
                    emit notify_train_arrived(path_list[i].second, path_list[i].first.second.front(), path_list[i].first.first.front());
                    path_list.erase(path_list.begin() + i);
                    i--;
                }
            }
            this->usleep((1000000 / block_per_second) / multiplier);
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

void Animation::set_block_per_second(int new_block_per_second)
{
    block_per_second = new_block_per_second;
}

void Animation::set_multiplier(int new_multiplier)
{
    multiplier = new_multiplier;
}
