#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    gate_in = new Gate_In_Manager(this);
    train_create = new Train_maker(this);
    canvas_animation = new Animation(this);

    map_labels = new QLabel*[MAX_X * MAX_Y];
    for(int i = 0; i < MAX_X * MAX_Y; i++)
    {
        this->map_labels[i] = new QLabel(this);
        int x = i % MAX_X;
        int y = i / MAX_X;
        this->map_labels[i]->setGeometry(BLOCK_X*x, 300 + BLOCK_Y*y, BLOCK_X, BLOCK_Y);
        this->map_labels[i]->setAutoFillBackground(true);
    }

    train_labels = new std::pair<QLabel*, Train*>*[PLATFORM_SUM+PLATFORM_SUM];
    for(int i = 0; i < PLATFORM_SUM+PLATFORM_SUM; i++)
    {
        this->train_labels[i] = new std::pair<QLabel*, Train*>;
        this->train_labels[i]->first = new QLabel(this);
        this->train_labels[i]->second = nullptr;
        this->train_labels[i]->first->setGeometry(BLOCK_X*(MAX_X-1), 300, BLOCK_X, BLOCK_Y);
        this->train_labels[i]->first->setStyleSheet("font: 10pt; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border: 2px solid black");
        train_labels[i]->first->setAutoFillBackground(true);
        this->train_labels[i]->first->hide();
    }

    connect(train_create, SIGNAL(notify_train_incoming(Train*)), gate_in, SLOT(notified_train_incoming(Train*)));

    connect(canvas_animation, SIGNAL(notify_move_train(Train*,Infrastructure*)), this, SLOT(notified_move_train(Train*,Infrastructure*)));
    connect(canvas_animation, SIGNAL(notify_train_arrived(Train*,Infrastructure*,Infrastructure*)), gate_in, SLOT(notified_train_arrived(Train*,Infrastructure*,Infrastructure*)));

    connect(gate_in, SIGNAL(notify_incoming_train_full(bool)), train_create, SLOT(notified_incoming_train_full(bool)));
    connect(gate_in, SIGNAL(notify_update_incoming_train(QString)), this, SLOT(notified_update_incoming_train(QString)));
    connect(gate_in, SIGNAL(notify_color(int,int,int)), this, SLOT(notified_color(int,int,int)));
    connect(gate_in, SIGNAL(notify_train_label_attach(Train*)), this, SLOT(notified_train_label_attach(Train*)));
    connect(gate_in, SIGNAL(notify_put_train_on_canvas(Train*)), this, SLOT(notified_put_train_on_canvas(Train*)));
    connect(gate_in, SIGNAL(notify_train_depart(std::deque<Infrastructure*>*)), canvas_animation, SLOT(notified_train_depart(std::deque<Infrastructure*>*)));
    connect(gate_in, SIGNAL(notify_change_color(Train*)), this, SLOT(notified_change_color(Train*)));
    connect(gate_in, SIGNAL(notify_train_label_detach(Train*)), this, SLOT(notified_train_label_detach(Train*)));

    this->gate_in->map_coloring();
    this->start_simulation();
}

MainWindow::~MainWindow()
{
    gate_in->terminate();
    train_create->terminate();
    canvas_animation->terminate();
    delete ui;
}

void MainWindow::notified_train_label_attach(Train *train_input)
{
    for(unsigned int i = 0; i < PLATFORM_SUM+PLATFORM_SUM; i++)
    {
        if(this->train_labels[i]->second == nullptr)
        {
            this->train_labels[i]->second = train_input;
            return;
        }
    }
}

void MainWindow::notified_put_train_on_canvas(Train *train_input)
{
    for(unsigned int i = 0; i < PLATFORM_SUM+PLATFORM_SUM; i++)
    {
        if(this->train_labels[i]->second == train_input)
        {
            train_labels[i]->first->setText(QString::number(train_input->getId()));
            this->train_labels[i]->first->show();
            return;
        }
    }
}

void MainWindow::notified_move_train(Train* train_input,Infrastructure* now)
{
    for(unsigned int i = 0; i < PLATFORM_SUM+PLATFORM_SUM; i++)
    {
        if(this->train_labels[i]->second == train_input)
        {
            this->train_labels[i]->first->move(now->getX()*BLOCK_X, 300 + now->getY()*BLOCK_Y);
            return;
        }
    }
}

void MainWindow::notified_train_label_detach(Train *train_input)
{
    for(unsigned int i = 0; i < PLATFORM_SUM+PLATFORM_SUM; i++)
    {
        if(this->train_labels[i]->second == train_input)
        {
            this->train_labels[i]->second = nullptr;
            train_labels[i]->first->move(BLOCK_X*(MAX_X-1), 300);
            train_labels[i]->first->setStyleSheet("font: 10pt; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border: 2px solid black");
            train_labels[i]->first->setText("");
            train_labels[i]->first->hide();
            return;
        }
    }
}

void MainWindow::notified_color(int x, int y, int type)
{
    int y2 = (39) * y;
    if(type == 0)
        this->map_labels[y2 + x]->setStyleSheet("background-color: rgb(205, 255, 205); border: 1px solid black");
    else if(type == 1)
        this->map_labels[y2 + x]->setStyleSheet("background-color: rgb(205, 205, 255); border: 1px solid black");
    else
        this->map_labels[y2 + x]->setStyleSheet("background-color: rgb(255, 205, 205); border: 1px solid black");
}

void MainWindow::notified_change_color(Train *train_input)
{
    for(unsigned int i = 0; i < PLATFORM_SUM+PLATFORM_SUM; i++)
    {
        if(this->train_labels[i]->second == train_input)
        {
            this->train_labels[i]->first->setStyleSheet("font: 10pt; color: rgb(0, 0, 0); background-color: rgb(255, 155, 155); border: 2px solid black");
            return;
        }
    }
}

void MainWindow::notified_update_incoming_train(QString input)
{
    ui->incoming_train_text->setText(input);
}

void MainWindow::start_simulation()
{
    gate_in->start();
    canvas_animation->start();
    train_create->start();
}

void MainWindow::on_multiplier_button_clicked()
{
    int multi = ui->multiplier_spinbox->value();
    gate_in->set_multiplier(multi);
    canvas_animation->set_multiplier(multi);
    train_create->set_multiplier(multi);
}


void MainWindow::on_platform_stay_button_clicked()
{
    gate_in->change_platform_duration(true, ui->platform_stay_spinbox->value());
}


void MainWindow::on_mine_duration_button_clicked()
{
    gate_in->change_platform_duration(false, ui->mine_duration_spinbox->value());
}

