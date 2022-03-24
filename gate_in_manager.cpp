#include "gate_in_manager.h"

Gate_In_Manager::Gate_In_Manager(QObject *parent) : QThread(parent)
{
    for(int i = 0; i < MAX_Y; i++)
        for(int j = 0; j < MAX_X; j++)
            this->map[i][j] = nullptr;

    this->mine_initialization();
    this->left_initialization();
    this->platform_initialization();
    this->right_initialization();
    this->mine_hand_initialization();
    this->left_hand_initialization();
    this->platform_hand_initialization();
    this->right_hand_initialization();
    in = map[0][MAX_X-1];
    out = map[2][MAX_X-1];
}

void Gate_In_Manager::run()
{
    while(true)
    {
        QMutex m;
        m.lock();
        qDebug() << timer;
        timer++;

        // kurangin stay duration setiap kereta di platform dan mine
        for(int i = 0; i < 3; i++)
        {
            for(unsigned int j = 0; j < mine_group[i].size(); j++)
            {
                if(mine_group[i].at(j)->getTrain() != nullptr)
                {
                    if(mine_group[i].at(j)->getTrain()->getStop_duration() > 0)
                        mine_group[i].at(j)->getTrain()->stop_reduction();
                    if(mine_group[i].at(j)->getTrain()->getStop_duration() == 0 && mine_group[i].at(j)->getTrain()->getOut_waiting_list() == false)
                    {
                        outcoming_train_pathway.push_back(mine_group[i].at(j));
                        mine_group[i].at(j)->getTrain()->setOut_waiting_list(true);
                        emit notify_change_color(mine_group[i].at(j)->getTrain());
                    }
                }
            }
        }

        for(int i = 0; i < PLATFORM_SUM; i++)
        {
            if(platform_list[i]->getTrain() != nullptr)
            {
                if(platform_list[i]->getTrain()->getStop_duration() > 0)
                    platform_list[i]->getTrain()->stop_reduction();
                if(platform_list[i]->getTrain()->getStop_duration() == 0 && platform_list[i]->getTrain()->getOut_waiting_list() == false)
                {
                    if(platform_list[i]->getTrain()->getDirection() == ENTERING)
                        outcoming_train_pathway.push_back(platform_list[i]);
                    else if(platform_list[i]->getTrain()->getDirection() == EXITING)
                        outcoming_train_gate.push_back(platform_list[i]);
                    platform_list[i]->getTrain()->setOut_waiting_list(true);
                    // emit change_color_to_red(i);
                }
            }
        }

        // kalau ada yang di queue siap gerak
        if(!outcoming_train_gate.empty() && gate_out_ready == true)
            if(this->train_depart(outcoming_train_gate.front()))
                outcoming_train_gate.pop_front();
        if(!outcoming_train_pathway.empty())
        {
            for(unsigned int i = 0; i < this->outcoming_train_pathway.size(); i++)
            {
                if(this->train_depart(outcoming_train_pathway[i]))
                {
                    this->outcoming_train_pathway.erase(this->outcoming_train_pathway.begin() + i);
                    break;
                }
            }
        }

        // kalo ada kereta yang mau masuk, dan gate in ready, dan ada platform kosong, masukin ke platform
        if(!incoming_train.empty() && gate_in_ready)
        {
            gate_in_ready = false;
            this->put_train_at_entrance();
        }
        this->msleep(1000 / multiplier);
        m.unlock();
    }
}

void Gate_In_Manager::notified_train_arrived(Infrastructure *destination)
{
    if(destination == out)
    {
        emit notify_train_label_detach(destination->getTrain());
        delete destination->getTrain();
        destination->setTrain(nullptr);
        destination->setOccupied(false);
        gate_out_ready = true;
        return;
    }
    else if(destination->getType() == PLATFORM && destination->getTrain()->getDirection() == ENTERING)
    {
        this->gate_in_ready = true;
        qDebug() << QString::fromStdString("Train ") + QString::number(destination->getTrain()->getId()) + " arrived on Platform";
    }
    else if(destination->getType() == MINE && destination->getTrain()->getDirection() == ENTERING)
    {
        destination->getTrain()->setDirection(EXITING);
        qDebug() << QString::fromStdString("Train ") + QString::number(destination->getTrain()->getId()) + " arrived on Mine";
    }
    else if(destination->getType() == PLATFORM && destination->getTrain()->getDirection() == EXITING)
    {
        qDebug() << QString::fromStdString("Train ") + QString::number(destination->getTrain()->getId()) + " arrived on Platform";
    }
    return;
}

void Gate_In_Manager::notified_train_incoming(Train *train_input)
{
    incoming_train.push_back(train_input);
    emit notify_train_label_attach(train_input);
    return;
}

void Gate_In_Manager::put_train_at_entrance()
{
    Train* tmp = incoming_train.front();
    std::deque <Infrastructure*> *path = this->navigate(in, this->check_free_platform(), tmp->getDirection());
    if(path)
    {
        in->setTrain(tmp);
        tmp->add_duration(path->at(path->size()-1)->getStay());
        incoming_train.pop_front();
        emit notify_put_train_on_canvas(tmp);
        emit notify_train_depart(path);
    }
    else
        gate_in_ready = true;
    return;
}

bool Gate_In_Manager::train_depart(Infrastructure* start) // signal the train to move to its destination
{
    if(start->getTrain()->getDirection() == ENTERING) // kalo masuk dari platform ke mine
    {
        std::pair<Infrastructure*, int>* available_mine = this->check_free_mine();
        if(available_mine != nullptr)
        {
            std::deque <Infrastructure*> *path = this->navigate(start, available_mine->first, start->getTrain()->getDirection());
            if(path)
            {
                start->getTrain()->setOut_waiting_list(false);
                start->getTrain()->add_duration(available_mine->first->getStay());
                qDebug() << QString::fromStdString("Train ") + QString::number(start->getTrain()->getId()) + " departed from Platform";
                emit notify_train_depart(path);
                delete available_mine;
                return true;
            }
            else
                delete available_mine;
        }
    }
    else if(start->getTrain()->getDirection() == EXITING && start->getType() == PLATFORM) // kalo keluar dari platform ke out
    {
        std::deque <Infrastructure*> *path = this->navigate(start, out, start->getTrain()->getDirection());
        if(path)
        {
            start->getTrain()->setOut_waiting_list(false);
            qDebug() << QString::fromStdString("Train ") + QString::number(start->getTrain()->getId()) + " departed from Platform";
            emit notify_train_depart(path);
            gate_out_ready = false;
            return true;
        }
        else
            gate_out_ready = true;
    }
    else if(start->getTrain()->getDirection() == EXITING) // kalo keluar dari mine ke platform
    {
        for(int i = 0; i < PLATFORM_SUM; i++)
        {
            if(platform_list[i]->getOccupied() == false)
            {
                std::deque <Infrastructure*> *path = this->navigate(start, platform_list[i], start->getTrain()->getDirection());
                if(path)
                {
                    start->getTrain()->add_duration(platform_list[i]->getStay());
                    start->getTrain()->setOut_waiting_list(false);
                    qDebug() << QString::fromStdString("Train ") + QString::number(start->getTrain()->getId()) + " departed from Mine";
                    emit notify_train_depart(path);
                    return true;
                }
            }
        }
    }
    return false;
}

std::deque<Infrastructure *> *Gate_In_Manager::navigate(Infrastructure *start_pos, Infrastructure *end_pos, bool direction)
{
    Infrastructure *current = start_pos, *before, *backtrack = end_pos;
    std::vector<std::pair<Infrastructure *, Infrastructure *>> before_after_list;
    std::stack<Infrastructure *> branches;

    while(current != end_pos)
    {
        before = current;
        if(direction == ENTERING)
        {
            if(current->getLeft_list().size() > 0)
            {

                if(current->getLeft_list().size() > 1)
                    for(unsigned int i = 1; i < current->getLeft_list().size(); i++)
                    {
                        if(current->getLeft_list().at(i)->getOccupied() == false)
                        {
                            branches.push(current->getLeft_list().at(i));
                            before_after_list.push_back({current, current->getLeft_list().at(i)});
                        }
                    }
                if(current->getLeft_list().at(0)->getOccupied() == false)
                {
                    before_after_list.push_back({current, current->getLeft_list().at(0)});
                    current = current->getLeft_list().at(0);
                }
            }
        }
        else
        {
            if(current->getRight_list().size() > 0)
            {

                if(current->getRight_list().size() > 1)
                    for(unsigned int i = 1; i < current->getRight_list().size(); i++)
                    {
                        if(current->getRight_list().at(i)->getOccupied() == false)
                        {
                            branches.push(current->getRight_list().at(i));
                            before_after_list.push_back({current, current->getRight_list().at(i)});
                        }
                    }
                if(current->getRight_list().at(0)->getOccupied() == false)
                {
                    before_after_list.push_back({current, current->getRight_list().at(0)});
                    current = current->getRight_list().at(0);
                }
            }
        }
        if(current->getType() == end_pos->getType() && end_pos->getType() == PLATFORM)
        {
            if(current != end_pos || end_pos->getOccupied() == true)
            {
                if(branches.empty()) // if it is empty, that means no path to that way right now or not possible
                    return nullptr;
                current = branches.top();
                branches.pop();
            }
        }
        else if(current->getLeft_list().size() > 1 && end_pos->getType() == MINE)
        {
            for(unsigned int i = 0; i < current->getLeft_list().size(); i++)
            {
                if(current->getLeft_list().at(i) == end_pos && end_pos->getOccupied() == false)
                {
                    before_after_list.push_back({current, current->getLeft_list().at(i)});
                    current = current->getLeft_list().at(i);
                    break;
                }
            }
        }
        if(before == current)
        {
            if(branches.empty()) // if it is empty, that means no path to that way right now or not possible
                return nullptr;
            current = branches.top();
            branches.pop();
        }
    }

    std::deque<Infrastructure *> *path = new std::deque<Infrastructure *>;

    for(int i = before_after_list.size() - 1; i >= 0; i--)
    {
        if(backtrack == before_after_list[i].second)
        {
            path->push_front(backtrack);
            backtrack = before_after_list[i].first;
        }
        if(backtrack == start_pos)
            break;
    }

    path->push_front(backtrack);

    for(unsigned int i = 0; i < path->size(); i++)
    {
        path->at(i)->setOccupied(true);
    }
    return path;
}

Infrastructure* Gate_In_Manager::check_free_platform() // check available platform that leads to an available mine group
{
    std::pair<Infrastructure*, int>* available_mine = this->check_free_mine();
    if(available_mine == nullptr)
        return nullptr;
    for(int i = 0; i < PLATFORM_SUM; i++)
    {
        if(platform_list[i]->getOccupied() == false)
        {
            for(unsigned int j = 0; j < platform_list[i]->getMines()->size(); j++)
            {
                if(platform_list[i]->getMines()->at(j) == available_mine->second)
                {
                    delete available_mine;
                    return platform_list[i];
                }
            }
        }
    }
    return nullptr;
}

std::pair<Infrastructure*, int>* Gate_In_Manager::check_free_mine() // return mine group that are available
{
    for(int i = 0; i < 3; i++)
    {
        for(unsigned int j = 0; j < mine_group[i].size(); j++)
        {
            if(mine_group[i].at(j)->getOccupied() == false)
            {
                std::pair<Infrastructure*, int>* location = new std::pair<Infrastructure*, int> {mine_group[i].at(j), i};
                return location;
            }
        }
    }
    return nullptr;
}

void Gate_In_Manager::left_initialization()
{
    int index_y = 0;
    while(!fill_left.empty())
    {
        int tmp = fill_left.front();
        fill_left.pop_front();
        if(tmp == -1)
        {
            index_y++;
            continue;
        }
        this->map[index_y][tmp] = new Infrastructure(RAIL, index_y, tmp);
    }
}

void Gate_In_Manager::left_hand_initialization()
{
    // Line I & II
    for(int i = 2; i < 22; i++)
    {
        this->map[0][i]->addRight(this->map[0][i+1]);
        this->map[2][i]->addRight(this->map[2][i+1]);
        this->map[0][i]->addLeft(this->map[0][i-1]);
        this->map[2][i]->addLeft(this->map[2][i-1]);
    }
    // Line III
    for(int i = 2; i < 7; i++)
    {
        this->map[4][i]->addLeft(this->map[4][i-1]);
        this->map[4][i]->addRight(this->map[4][i+1]);
    }
    for(int i = 19; i < 22; i++)
    {
        this->map[4][i]->addLeft(this->map[4][i-1]);
        this->map[4][i]->addRight(this->map[4][i+1]);
    }
    // Line IV
    for(int i = 2; i < 22; i++)
    {
        this->map[6][i]->addLeft(this->map[6][i-1]);
        this->map[6][i]->addRight(this->map[6][i+1]);
    }
    // Line V
    for(int i = 10; i < 22; i++)
    {
        this->map[8][i]->addLeft(this->map[8][i-1]);
        this->map[8][i]->addRight(this->map[8][i+1]);
    }
    //Line VI
    for(int i = 2; i < 22; i++){
        this->map[10][i]->addLeft(this->map[10][i-1]);
        this->map[10][i]->addRight(this->map[10][i+1]);
    }

    // Line VII
    for(int i = 2; i < 22; i++){
        this->map[12][i]->addLeft(this->map[12][i-1]);
        this->map[12][i]->addRight(this->map[12][i+1]);
    }

    // Line VIII
    for(int i = 16;i < 22; i++){
        this->map[14][i]->addLeft(this->map[14][i-1]);
        this->map[14][i]->addRight(this->map[14][i+1]);
    }

    // Branches
    // Line I
    this->map[0][10]->addLeft(this->map[1][9]); // kiri bawah
    this->map[0][10]->addRight(this->map[1][11]); // kanan bawah
    // Line II
    this->map[2][5]->addLeft(this->map[3][4]); // kiri bawah
    this->map[2][5]->addRight(this->map[3][6]); // kanan bawah
    this->map[2][8]->addRight(this->map[1][9]); // kanan atas
    this->map[2][12]->addLeft(this->map[1][11]); // kiri atas
    this->map[2][12]->addRight(this->map[3][13]); // kanan bawah
    this->map[2][16]->addRight(this->map[3][17]); // kanan bawah
    // Line III
    this->map[4][3]->addRight(this->map[3][4]); // kanan atas
    this->map[4][7]->addLeft(this->map[4][6]); // kiri kiri
    this->map[4][7]->addLeft(this->map[3][6]); // kiri atas
    this->map[4][7]->addRight(this->map[5][8]); // kanan bawah
    this->map[4][14]->addLeft(this->map[3][13]); // kiri atas
    this->map[4][14]->addRight(this->map[5][15]); // kanan bawah
    this->map[4][18]->addLeft(this->map[3][17]); // kiri atas
    this->map[4][18]->addRight(this->map[4][19]); // kanan kanan
    this->map[4][20]->addLeft(this->map[5][19]); // kiri bawah
    // Line IV
    this->map[6][7]->addLeft(this->map[5][6]); // kiri atas
    this->map[6][7]->addRight(this->map[7][8]); // kanan bawah
    this->map[6][9]->addLeft(this->map[5][8]); // kiri atas
    this->map[6][9]->addRight(this->map[7][10]); // kanan bawah
    this->map[6][16]->addLeft(this->map[5][15]); // kiri atas
    this->map[6][18]->addLeft(this->map[7][17]); // kiri bawah
    this->map[6][18]->addRight(this->map[5][19]); // kanan atas
    // Line V
    this->map[8][9]->addLeft(this->map[7][8]); // kiri atas
    this->map[8][9]->addRight(this->map[8][10]); // kanan kanan
    this->map[8][9]->addRight(this->map[7][10]); // kanan atas
    this->map[8][11]->addLeft(this->map[7][10]); // kiri atas
    this->map[8][11]->addRight(this->map[9][12]); // kanan bawah
    this->map[8][16]->addLeft(this->map[9][15]); // kiri bawah
    this->map[8][16]->addRight(this->map[7][17]); // kanan atas
    // Line VI
    this->map[10][11]->addLeft(this->map[9][10]); // kiri atas
    this->map[10][11]->addRight(this->map[11][12]); // kanan bawah
    this->map[10][13]->addLeft(this->map[9][12]); // kiri atas
    this->map[10][13]->addRight(this->map[11][14]); // kanan bawah
    this->map[10][14]->addRight(this->map[9][15]); // kanan atas
    this->map[10][17]->addLeft(this->map[11][16]); // kiri bawah
    // Line VII
    this->map[12][13]->addLeft(this->map[11][12]); // kiri atas
    this->map[12][13]->addRight(this->map[13][14]); // kanan bawah
    this->map[12][15]->addLeft(this->map[11][14]); // kiri atas
    this->map[12][15]->addRight(this->map[11][16]); // kanan atas
    this->map[12][15]->addRight(this->map[13][16]); // kanan bawah
    // Line VIII
    this->map[14][17]->addLeft(this->map[13][16]); // kiri atas
    this->map[14][15]->addRight(this->map[14][16]); // kanan kanan
    this->map[14][15]->addLeft(this->map[13][14]); // kiri atas

    // 2nd Branches
    // Line I-II
    this->map[1][9]->addLeft(this->map[2][8]); // kiri bawah
    this->map[1][9]->addRight(this->map[0][10]); // kanan atas
    this->map[1][11]->addLeft(this->map[0][10]); // kiri atas
    this->map[1][11]->addRight(this->map[2][12]); // kanan bawah
    // Line II-III
    this->map[3][4]->addLeft(this->map[4][3]); // kiri bawah
    this->map[3][4]->addRight(this->map[2][5]); // kanan atas
    this->map[3][6]->addLeft(this->map[2][5]); // kiri atas
    this->map[3][6]->addRight(this->map[4][7]); // kanan bawah
    this->map[3][13]->addLeft(this->map[2][12]); // kiri atas
    this->map[3][13]->addRight(this->map[4][14]); // kanan bawah
    this->map[3][17]->addLeft(this->map[2][16]); // kiri atas
    this->map[3][17]->addRight(this->map[4][18]); // kanan bawah
    // Line III-IV
    this->map[5][6]->addLeft(this->map[4][5]); // kiri atas
    this->map[5][6]->addRight(this->map[6][7]); // kanan bawah
    this->map[5][8]->addLeft(this->map[4][7]); // kiri atas
    this->map[5][8]->addRight(this->map[6][9]); // kanan bawah
    this->map[5][15]->addLeft(this->map[4][14]); // kiri atas
    this->map[5][15]->addRight(this->map[6][16]); // kanan bawah
    this->map[5][19]->addLeft(this->map[6][18]); // kiri bawah
    this->map[5][19]->addRight(this->map[4][20]); // kanan atas
    // Line IV-V
    this->map[7][8]->addLeft(this->map[6][7]); // kiri atas
    this->map[7][8]->addRight(this->map[8][9]); // kanan bawah
    this->map[7][10]->addLeft(this->map[6][9]); // kiri atas
    this->map[7][10]->addRight(this->map[8][11]); // kanan bawah
    this->map[7][17]->addLeft(this->map[8][16]); // kiri bawah
    this->map[7][17]->addRight(this->map[6][18]); // kanan atas
    // Line V-VI
    this->map[9][10]->addLeft(this->map[8][9]); // kiri atas
    this->map[9][10]->addRight(this->map[10][11]); // kanan bawah
    this->map[9][12]->addLeft(this->map[8][11]); // kiri atas
    this->map[9][12]->addRight(this->map[10][13]); // kanan bawah
    this->map[9][15]->addLeft(this->map[10][14]); // kiri bawah
    this->map[9][15]->addRight(this->map[8][16]); // kanan atas
    // Line VI - VII
    this->map[11][12]->addLeft(this->map[10][11]); // kiri atas
    this->map[11][12]->addRight(this->map[12][13]); // kanan bawah
    this->map[11][14]->addLeft(this->map[10][13]); // kiri atas
    this->map[11][14]->addRight(this->map[12][15]); // kanan bawah
    this->map[11][16]->addLeft(this->map[12][15]); // kiri bawah
    this->map[11][16]->addRight(this->map[10][17]); // kanan atas
    // Line VII - VIII
    this->map[13][14]->addLeft(this->map[12][13]); // kiri atas
    this->map[13][14]->addRight(this->map[14][15]); // kanan bawah
    this->map[13][16]->addLeft(this->map[12][15]); // kiri atas
    this->map[13][16]->addRight(this->map[14][17]); // kanan bawah

    // Mine entrance
    // Group 1
    this->map[0][1]->addRight(this->map[0][2]);
    this->map[0][1]->addLeft(this->map[1][0]);
    this->map[0][1]->addLeft(this->map[2][0]);
    this->map[0][1]->addLeft(this->map[3][0]);
    this->map[2][1]->addRight(this->map[2][2]);
    this->map[2][1]->addLeft(this->map[1][0]);
    this->map[2][1]->addLeft(this->map[2][0]);
    this->map[2][1]->addLeft(this->map[3][0]);
    // Group 2
    this->map[4][1]->addRight(this->map[4][2]);
    this->map[4][1]->addLeft(this->map[5][0]);
    this->map[4][1]->addLeft(this->map[6][0]);
    this->map[4][1]->addLeft(this->map[7][0]);
    this->map[6][1]->addRight(this->map[6][2]);
    this->map[6][1]->addLeft(this->map[5][0]);
    this->map[6][1]->addLeft(this->map[6][0]);
    this->map[6][1]->addLeft(this->map[7][0]);
    // Group 3
    this->map[10][1]->addRight(this->map[10][2]);
    this->map[10][1]->addLeft(this->map[11][0]);
    this->map[10][1]->addLeft(this->map[12][0]);
    this->map[12][1]->addRight(this->map[12][2]);
    this->map[12][1]->addLeft(this->map[11][0]);
    this->map[12][1]->addLeft(this->map[12][0]);
}

void Gate_In_Manager::right_initialization()
{
    int index_y = 0;
    while(!fill_right.empty())
    {
        int tmp = fill_right.front();
        fill_right.pop_front();
        if(tmp == -1)
        {
            index_y++;
            continue;
        }
        this->map[index_y][tmp] = new Infrastructure(RAIL, index_y, tmp);
    }
}

void Gate_In_Manager::right_hand_initialization()
{
    // Line I & II
    for(int i = 23; i < MAX_X; i++) // dari 23 -> 38
    {
        if(i != 38)
        {
            this->map[0][i]->addRight(this->map[0][i+1]);
            this->map[2][i]->addRight(this->map[2][i+1]);
        }
        this->map[0][i]->addLeft(this->map[0][i-1]);
        this->map[2][i]->addLeft(this->map[2][i-1]);
    }

    // Line III
    for(int i = 23; i < 30; i++) // dari 23 -> 29
    {
        this->map[4][i]->addLeft(this->map[4][i-1]);
        this->map[4][i]->addRight(this->map[4][i+1]);
    }
    // Line IV
    for(int i = 23; i < 28; i++) // dari 23 -> 27
    {
        this->map[6][i]->addLeft(this->map[6][i-1]);
        this->map[6][i]->addRight(this->map[6][i+1]);
    }

    // Line V
    for(int i = 23; i < 26; i++) // dari 23 -> 25
    {
        this->map[8][i]->addLeft(this->map[8][i-1]);
        this->map[8][i]->addRight(this->map[8][i+1]);
    }

    // Line VI
    for(int i = 23; i < 27; i++) // dari 23 -> 26
    {
        this->map[10][i]->addLeft(this->map[10][i-1]);
        this->map[10][i]->addRight(this->map[10][i+1]);
    }

    // Line VII
    for(int i = 23; i < 25; i++) // dari 23 -> 24
    {
        this->map[12][i]->addLeft(this->map[12][i-1]);
        this->map[12][i]->addRight(this->map[12][i+1]);
    }

    // Branches
    // Line I
    this->map[0][33]->addRight(this->map[1][34]); // kanan bawah
    this->map[0][34]->addLeft(this->map[1][33]); // kiri bawah
    this->map[0][37]->addLeft(this->map[1][36]); // kiri bawah

    // Line II
    this->map[2][32]->addLeft(this->map[3][31]); // kiri bawah
    this->map[2][32]->addRight(this->map[1][33]); // kanan atas
    this->map[2][35]->addLeft(this->map[1][34]); // kiri atas
    this->map[2][35]->addLeft(this->map[3][34]); // kiri bawah
    this->map[2][35]->addRight(this->map[1][36]); // kanan atas

    // Line III
    this->map[4][30]->addLeft(this->map[4][29]);
    this->map[4][30]->addLeft(this->map[5][29]);
    this->map[4][30]->addRight(this->map[3][31]);
    this->map[4][33]->addLeft(this->map[5][32]); // bawah
    this->map[4][33]->addRight(this->map[3][34]); // atas

    // Line IV
    this->map[6][28]->addLeft(this->map[6][27]);
    this->map[6][28]->addLeft(this->map[7][27]);
    this->map[6][28]->addRight(this->map[5][29]);
    this->map[6][31]->addLeft(this->map[7][30]);
    this->map[6][31]->addRight(this->map[5][32]);

    // Line V
    this->map[8][26]->addLeft(this->map[8][25]);
    this->map[8][26]->addLeft(this->map[9][25]);
    this->map[8][26]->addRight(this->map[7][27]);
    this->map[8][29]->addLeft(this->map[9][28]);
    this->map[8][29]->addRight(this->map[7][30]);

    // Line VI
    this->map[10][24]->addRight(this->map[9][25]);
    this->map[10][27]->addLeft(this->map[10][26]);
    this->map[10][27]->addLeft(this->map[11][26]);
    this->map[10][27]->addRight(this->map[9][28]);

    // Line VII
    this->map[12][25]->addLeft(this->map[12][24]);
    this->map[12][25]->addRight(this->map[11][26]);

    // Line VIII
    this->map[14][23]->addLeft(this->map[14][22]);
    this->map[14][23]->addRight(this->map[13][24]);

    // 2nd Branches
    // Line I-II
    this->map[1][33]->addLeft(this->map[2][32]); // kiri bawah
    this->map[1][33]->addRight(this->map[0][34]); // kanan atas
    this->map[1][34]->addLeft(this->map[0][33]); // kiri atas
    this->map[1][34]->addRight(this->map[2][35]); // kanan bawah
    this->map[1][36]->addLeft(this->map[2][35]); // kiri bawah
    this->map[1][36]->addRight(this->map[0][37]); // kanan atas

    // Line II-III
    this->map[3][31]->addLeft(this->map[4][30]); // kiri bawah
    this->map[3][31]->addRight(this->map[2][32]); // kanan atas
    this->map[3][34]->addLeft(this->map[4][33]); // kiri bawah
    this->map[3][34]->addRight(this->map[2][35]); // kanan atas

    // Line III-IV
    this->map[5][29]->addLeft(this->map[6][28]); // kiri bawah
    this->map[5][29]->addRight(this->map[4][30]); // kanan atas
    this->map[5][32]->addLeft(this->map[6][31]); // kiri bawah
    this->map[5][32]->addRight(this->map[4][33]); // kanan atas

    // Line IV-V
    this->map[7][27]->addLeft(this->map[8][26]); // kiri bawah
    this->map[7][27]->addRight(this->map[6][28]); // kanan atas
    this->map[7][30]->addLeft(this->map[8][29]); // kiri bawah
    this->map[7][30]->addRight(this->map[6][31]); // kanan atas

    // Line V-VI
    this->map[9][25]->addLeft(this->map[10][24]); // kiri bawah
    this->map[9][25]->addRight(this->map[8][26]); // kanan atas
    this->map[9][28]->addLeft(this->map[10][27]); // kiri bawah
    this->map[9][28]->addRight(this->map[8][29]); // kanan atas

    // Line VI-VII
    this->map[11][26]->addLeft(this->map[12][25]); // kiri bawah
    this->map[11][26]->addRight(this->map[10][27]); // kanan atas

    // Line VII-VIII
    this->map[13][24]->addLeft(this->map[14][23]); // kiri bawah
    this->map[13][24]->addRight(this->map[12][25]); // kanan atas
}

void Gate_In_Manager::mine_initialization()
{
    int counter = 0;
    while(counter < 3)
    {
        Infrastructure* tmp = new Infrastructure(MINE, 1+counter, 0);
        this->mine_group[0].push_back(tmp);
        this->map[1+counter][0] = tmp;
        counter++;
    }
    counter = 0;
    while(counter < 3)
    {
        Infrastructure* tmp = new Infrastructure(MINE, 5+counter, 0);
        this->mine_group[1].push_back(tmp);
        this->map[5+counter][0] = tmp;
        counter++;
    }
    counter = 0;
    while(counter < 2)
    {
        Infrastructure* tmp = new Infrastructure(MINE, 11+counter, 0);
        this->mine_group[2].push_back(tmp);
        this->map[11+counter][0] = tmp;
        counter++;
    }
}

void Gate_In_Manager::mine_hand_initialization()
{
    // Group 1
    this->map[1][0]->addRight(this->map[0][1]);
    this->map[1][0]->addRight(this->map[2][1]);
    this->map[2][0]->addRight(this->map[0][1]);
    this->map[2][0]->addRight(this->map[2][1]);
    this->map[3][0]->addRight(this->map[0][1]);
    this->map[3][0]->addRight(this->map[2][1]);

    // Group 2
    this->map[5][0]->addRight(this->map[4][1]);
    this->map[5][0]->addRight(this->map[6][1]);
    this->map[6][0]->addRight(this->map[4][1]);
    this->map[6][0]->addRight(this->map[6][1]);
    this->map[7][0]->addRight(this->map[4][1]);
    this->map[7][0]->addRight(this->map[6][1]);

    // Group 3
    this->map[11][0]->addRight(this->map[10][1]);
    this->map[11][0]->addRight(this->map[12][1]);
    this->map[12][0]->addRight(this->map[10][1]);
    this->map[12][0]->addRight(this->map[12][1]);
}

void Gate_In_Manager::platform_initialization()
{
    for(int i = 0; i < PLATFORM_SUM; i++)
    {
        this->platform_list[i] = new Infrastructure(PLATFORM, 2*i, 22);
        this->map[2*i][22] = this->platform_list[i];
        if(i < 2)
        {
            this->platform_list[i]->setMines(0);
            this->platform_list[i]->setMines(1);
        }
        else
        {
            this->platform_list[i]->setMines(0);
            this->platform_list[i]->setMines(1);
            this->platform_list[i]->setMines(2);
        }
    }
}

void Gate_In_Manager::platform_hand_initialization()
{
    for(int i = 0; i < PLATFORM_SUM; i++)
    {
        this->map[2*i][22]->addLeft(this->map[2*i][21]);
        this->map[2*i][22]->addRight(this->map[2*i][23]);
    }
}

void Gate_In_Manager::map_coloring()
{
    for(int i = 0; i < MAX_Y; i++)
    {
        for(int j = 0; j < MAX_X; j++)
        {
            if(this->map[i][j])
            {
                emit notify_color(j, i, this->map[i][j]->getType());
            }
        }
    }
}
