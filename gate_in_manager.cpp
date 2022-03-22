#include "gate_in_manager.h"

Gate_In_Manager::Gate_In_Manager(QObject *parent) : QThread(parent)
{
    for(int i = 0; i < MAX_Y; i++)
        for(int j = 0; j < MAX_X; j++)
            this->map[i][j] = nullptr;

    this->right_initialization();
    this->mine_initialization();
    this->platform_initialization();
    std::string cout;
    for(int i = 0; i < MAX_Y; i++)
    {
        for(int j = 0; j < MAX_X; j++)
        {
            if(this->map[i][j] && this->map[i][j]->getType() == RAIL)
                cout.append("Rail");
            else if(this->map[i][j] && this->map[i][j]->getType() == MINE)
                cout.append("Mine");
            else if(this->map[i][j] && this->map[i][j]->getType() == PLATFORM)
                cout.append("Plat");
            else
                cout.append("    ");
        }
        qDebug() << QString::fromStdString(cout);
        cout.clear();
    }
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
//        for(int i = 0; i < PLATFORM_SUM; i++)
//        {
//            if(platforms[i])
//            {
//                if(platforms[i]->getStop_duration() > 0)
//                    platforms[i]->stop_reduction();
//                if(platforms[i]->getStop_duration() == 0 && platforms[i]->getOut_waiting_list() == false)
//                {
//                    outcoming_train_pos.push_back(i);
//                    platforms[i]->setOut_waiting_list(true);
//                    emit change_color_to_red(i);
//                }
//            }
//        }

        // kalo ada kereta yang mau masuk, dan gate in ready, dan ada platform kosong, masukin ke platform
        if(!incoming_train.empty() && gate_in_ready && this->check_free_platform() != -1)
        {
            this->notify_train_into_platform(this->check_free_platform());
            gate_in_ready = false;
        }

        // kalau ada yang di queue keluar
        if(!outcoming_train_pos.empty() && gate_out_ready)
        {
//            this->notify_train_exiting_platform(outcoming_train_pos.front(), platforms[outcoming_train_pos.front()]);
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
//    delete platforms[pos];
//    platforms[pos] = nullptr;
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
//    platforms[pos] = input;
    gate_in_ready = true;
    return;
}

int Gate_In_Manager::check_free_platform() // help function - check available platform
{
    // cari platform yang kosong
//    for(int i = 0; i < PLATFORM_SUM; i++)
//    {
//        if(!platforms[i])
//        {
//            return i;
//        }
//    }
    return -1;
}

void Gate_In_Manager::right_initialization()
{
    // Line I & II
    for(int i = 23; i < MAX_X; i++) // dari 23 -> 38
    {
        this->map[0][i] = new Infrastructure(RAIL);
        this->map[0][i]->setLeft_list(this->map[0][i-1]);
        this->map[0][i]->setRight_list(this->map[0][i+1]);
        this->map[2][i] = new Infrastructure(RAIL);
        this->map[2][i]->setLeft_list(this->map[2][i-1]);
        this->map[2][i]->setRight_list(this->map[2][i+1]);
    }

    // Line III
    for(int i = 23; i < 30; i++) // dari 23 -> 29
    {
        this->map[4][i] = new Infrastructure(RAIL);
        this->map[4][i]->setLeft_list(this->map[4][i-1]);
        this->map[4][i]->setRight_list(this->map[4][i+1]);
    }

    // Line IV
    for(int i = 23; i < 28; i++) // dari 23 -> 27
    {
        this->map[6][i] = new Infrastructure(RAIL);
        this->map[6][i]->setLeft_list(this->map[6][i-1]);
        this->map[6][i]->setRight_list(this->map[6][i+1]);
    }

    // Line V
    for(int i = 23; i < 26; i++) // dari 23 -> 25
    {
        this->map[8][i] = new Infrastructure(RAIL);
        this->map[8][i]->setLeft_list(this->map[8][i-1]);
        this->map[8][i]->setRight_list(this->map[8][i+1]);
    }

    // Line VI
    for(int i = 23; i < 27; i++) // dari 23 -> 26
    {
        this->map[10][i] = new Infrastructure(RAIL);
        this->map[10][i]->setLeft_list(this->map[10][i-1]);
        this->map[10][i]->setRight_list(this->map[10][i+1]);
    }

    // Line VII
    for(int i = 23; i < 25; i++) // dari 23 -> 24
    {
        this->map[12][i] = new Infrastructure(RAIL);
        this->map[12][i]->setLeft_list(this->map[12][i-1]);
        this->map[12][i]->setRight_list(this->map[12][i+1]);
    }

    // Branches
    // Line I
    this->map[0][33]->setRight_list(this->map[1][34]); // kanan bawah
    this->map[0][34]->setLeft_list(this->map[1][33]); // kiri bawah
    this->map[0][37]->setLeft_list(this->map[1][36]); // kiri bawah

    // Line II
    this->map[2][32]->setLeft_list(this->map[3][31]); // kiri bawah
    this->map[2][32]->setRight_list(this->map[1][33]); // kanan atas
    this->map[2][35]->setLeft_list(this->map[1][34]); // kiri atas
    this->map[2][35]->setLeft_list(this->map[3][34]); // kiri bawah
    this->map[2][35]->setRight_list(this->map[1][36]); // kanan atas

    // Line III
    this->map[4][30] = new Infrastructure(RAIL);
    this->map[4][30]->setLeft_list(this->map[4][29]);
    this->map[4][30]->setLeft_list(this->map[5][29]);
    this->map[4][30]->setRight_list(this->map[3][31]);
    this->map[4][33] = new Infrastructure(RAIL);
    this->map[4][33]->setLeft_list(this->map[5][32]); // bawah
    this->map[4][33]->setRight_list(this->map[3][34]); // atas

    // Line IV
    this->map[6][28] = new Infrastructure(RAIL);
    this->map[6][28]->setLeft_list(this->map[6][27]);
    this->map[6][28]->setLeft_list(this->map[7][27]);
    this->map[6][28]->setRight_list(this->map[5][29]);
    this->map[6][31] = new Infrastructure(RAIL);
    this->map[6][31]->setLeft_list(this->map[7][30]);
    this->map[6][31]->setRight_list(this->map[5][32]);

    // Line V
    this->map[8][26] = new Infrastructure(RAIL);
    this->map[8][26]->setLeft_list(this->map[8][25]);
    this->map[8][26]->setLeft_list(this->map[9][25]);
    this->map[8][26]->setRight_list(this->map[7][27]);
    this->map[8][29] = new Infrastructure(RAIL);
    this->map[8][29]->setLeft_list(this->map[9][28]);
    this->map[8][29]->setRight_list(this->map[7][30]);

    // Line VI
    this->map[10][24]->setRight_list(this->map[9][25]);
    this->map[10][27] = new Infrastructure(RAIL);
    this->map[10][27]->setLeft_list(this->map[10][26]);
    this->map[10][27]->setLeft_list(this->map[11][26]);
    this->map[10][27]->setRight_list(this->map[9][28]);

    // Line VII
    this->map[12][25] = new Infrastructure(RAIL);
    this->map[12][25]->setLeft_list(this->map[12][24]);
    this->map[12][25]->setRight_list(this->map[11][26]);

    // Line VIII
    this->map[14][23] = new Infrastructure(RAIL);
    this->map[14][23]->setLeft_list(this->map[14][22]);
    this->map[14][23]->setRight_list(this->map[13][24]);

    // 2nd Branches
    // Line I-II
    this->map[1][33] = new Infrastructure(RAIL);
    this->map[1][33]->setLeft_list(this->map[2][32]);
    this->map[1][33]->setRight_list(this->map[0][34]);
    this->map[1][34] = new Infrastructure(RAIL);
    this->map[1][34]->setLeft_list(this->map[2][33]);
    this->map[1][34]->setRight_list(this->map[0][35]);
    this->map[1][36] = new Infrastructure(RAIL);
    this->map[1][36]->setLeft_list(this->map[2][35]);
    this->map[1][36]->setRight_list(this->map[0][37]);

    // Line II-III
    this->map[3][31] = new Infrastructure(RAIL);
    this->map[3][31]->setLeft_list(this->map[4][30]); // kiri bawah
    this->map[3][31]->setRight_list(this->map[2][32]); // kanan atas
    this->map[3][34] = new Infrastructure(RAIL);
    this->map[3][34]->setLeft_list(this->map[4][33]); // kiri bawah
    this->map[3][34]->setRight_list(this->map[2][35]); // kanan atas

    // Line III-IV
    this->map[5][29] = new Infrastructure(RAIL);
    this->map[5][29]->setLeft_list(this->map[6][28]); // kiri bawah
    this->map[5][29]->setRight_list(this->map[4][30]); // kanan atas
    this->map[5][32] = new Infrastructure(RAIL);
    this->map[5][32]->setLeft_list(this->map[6][31]); // kiri bawah
    this->map[5][32]->setRight_list(this->map[4][33]); // kanan atas

    // Line IV-V
    this->map[7][27] = new Infrastructure(RAIL);
    this->map[7][27]->setLeft_list(this->map[8][26]); // kiri bawah
    this->map[7][27]->setRight_list(this->map[6][28]); // kanan atas
    this->map[7][30] = new Infrastructure(RAIL);
    this->map[7][30]->setLeft_list(this->map[8][29]); // kiri bawah
    this->map[7][30]->setRight_list(this->map[6][31]); // kanan atas

    // Line V-VI
    this->map[9][25] = new Infrastructure(RAIL);
    this->map[9][25]->setLeft_list(this->map[10][24]); // kiri bawah
    this->map[9][25]->setRight_list(this->map[8][26]); // kanan atas
    this->map[9][28] = new Infrastructure(RAIL);
    this->map[9][28]->setLeft_list(this->map[10][27]); // kiri bawah
    this->map[9][28]->setRight_list(this->map[8][29]); // kanan atas

    // Line VI-VII
    this->map[11][26] = new Infrastructure(RAIL);
    this->map[11][26]->setLeft_list(this->map[12][25]); // kiri bawah
    this->map[11][26]->setRight_list(this->map[10][27]); // kanan atas

    // Line VII-VIII
    this->map[13][24] = new Infrastructure(RAIL);
    this->map[13][24]->setLeft_list(this->map[14][23]); // kiri bawah
    this->map[13][24]->setRight_list(this->map[12][25]); // kanan atas
}

void Gate_In_Manager::mine_initialization()
{
    int counter = 0;
    while(counter < 3)
    {
        Infrastructure* tmp = new Infrastructure(MINE);
        this->Mine_group[0].push_back(tmp);
        this->map[1+counter][0] = tmp;
        counter++;
    }
    counter = 0;
    while(counter < 3)
    {
        Infrastructure* tmp = new Infrastructure(MINE);
        this->Mine_group[1].push_back(tmp);
        this->map[5+counter][0] = tmp;
        counter++;
    }
    counter = 0;
    while(counter < 2)
    {
        Infrastructure* tmp = new Infrastructure(MINE);
        this->Mine_group[2].push_back(tmp);
        this->map[11+counter][0] = tmp;
        counter++;
    }
}

void Gate_In_Manager::platform_initialization()
{
    for(int i = 0; i < PLATFORM_SUM; i++)
    {
        this->platform_list[i] = new Infrastructure(PLATFORM);
        this->map[0 + 2*i][22] = this->platform_list[i];
    }
}

void Gate_In_Manager::setMultiplier(int newMultiplier)
{
    this->multiplier = newMultiplier;
}
