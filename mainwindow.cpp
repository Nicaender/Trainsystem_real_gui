#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QCoreApplication::setApplicationName( QString("Train System Simulator") );
    setWindowTitle( QCoreApplication::applicationName() );
    this->setFixedSize(this->width(), this->height());
    this->statusBar()->setSizeGripEnabled(false);

    gate_in = new Gate_In_Manager(this);
    train_create = new Train_maker(this);
    canvas_animation = new Animation(this);

    map_labels = new QLabel*[MAX_X * MAX_Y];
    for(int i = 0; i < MAX_X * MAX_Y; i++)
    {
        this->map_labels[i] = new QLabel(this);
        int x = i % MAX_X;
        int y = i / MAX_X;
        this->map_labels[i]->setGeometry(BLOCK_X*x+ 10, 300 + BLOCK_Y*y, BLOCK_X, BLOCK_Y);
        this->map_labels[i]->setAutoFillBackground(false);
    }

    train_labels = new std::pair<QLabel*, Train*>*[PLATFORM_SUM+PLATFORM_SUM];
    for(int i = 0; i < PLATFORM_SUM+PLATFORM_SUM; i++)
    {
        this->train_labels[i] = new std::pair<QLabel*, Train*>;
        this->train_labels[i]->first = new QLabel(this);
        this->train_labels[i]->second = nullptr;
        this->train_labels[i]->first->setGeometry(BLOCK_X*(MAX_X-1)+ 10, 300, BLOCK_X, BLOCK_Y);
        this->train_labels[i]->first->setStyleSheet("font: 10pt; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border: 2px solid black");
        train_labels[i]->first->setAutoFillBackground(true);
        this->train_labels[i]->first->hide();
    }

    connect(train_create, SIGNAL(notify_train_incoming(Train*)), gate_in, SLOT(notified_train_incoming(Train*)));

    connect(canvas_animation, SIGNAL(notify_move_train(Train*,Infrastructure*)), this, SLOT(notified_move_train(Train*,Infrastructure*)));
    connect(canvas_animation, SIGNAL(notify_train_arrived(Train*,Infrastructure*,Infrastructure*)), gate_in, SLOT(notified_train_arrived(Train*,Infrastructure*,Infrastructure*)));
    connect(canvas_animation, SIGNAL(notify_color(int,int,int)), this, SLOT(notified_color(int,int,int)));

    connect(gate_in, SIGNAL(notify_update_current_time(int)), this, SLOT(notified_update_current_time(int)));
    connect(gate_in, SIGNAL(notify_incoming_train_full(bool)), train_create, SLOT(notified_incoming_train_full(bool)));
    connect(gate_in, SIGNAL(notify_update_incoming_train(QString)), this, SLOT(notified_update_incoming_train(QString)));
    connect(gate_in, SIGNAL(notify_path_color(int,int)), this, SLOT(notified_path_color(int,int)));
    connect(gate_in, SIGNAL(notify_color(int,int,int)), this, SLOT(notified_color(int,int,int)));
    connect(gate_in, SIGNAL(notify_train_label_attach(Train*)), this, SLOT(notified_train_label_attach(Train*)));
    connect(gate_in, SIGNAL(notify_put_train_on_canvas(Train*)), this, SLOT(notified_put_train_on_canvas(Train*)));
    connect(gate_in, SIGNAL(notify_train_depart(std::deque<Infrastructure*>*)), canvas_animation, SLOT(notified_train_depart(std::deque<Infrastructure*>*)));
    connect(gate_in, SIGNAL(notify_change_color(Train*)), this, SLOT(notified_change_color(Train*)));
    connect(gate_in, SIGNAL(notify_train_label_detach(Train*)), this, SLOT(notified_train_label_detach(Train*)));

    this->gate_in->map_coloring();
    this->mark_intersections();
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
            this->train_labels[i]->first->move(now->getX()*BLOCK_X+ 10, 300 + now->getY()*BLOCK_Y);
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
            train_labels[i]->first->move(BLOCK_X*(MAX_X-1)+ 10, 300);
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
        this->map_labels[y2 + x]->setStyleSheet("background-color: rgb(205, 255, 205); border: 1px solid black; font: 10pt; font-weight: bold;");
    else if(type == 1)
        this->map_labels[y2 + x]->setStyleSheet("background-color: rgb(205, 205, 255); border: 1px solid black");
    else
        this->map_labels[y2 + x]->setStyleSheet("background-color: rgb(105, 155, 205); border: 1px solid black");
    this->map_labels[y2 + x]->setAutoFillBackground(true);
}

void MainWindow::notified_change_color(Train *train_input)
{
    for(unsigned int i = 0; i < PLATFORM_SUM+PLATFORM_SUM; i++)
    {
        if(this->train_labels[i]->second == train_input)
        {
            this->train_labels[i]->first->setStyleSheet("font: 10pt; color: rgb(0, 0, 0); background-color: rgb(255, 255, 155); border: 2px solid black");
            return;
        }
    }
}

void MainWindow::notified_update_incoming_train(QString input)
{
    ui->incoming_train_text->setText(input);
}

void MainWindow::notified_path_color(int x, int y)
{
    int y2 = (39) * y;
    this->map_labels[y2 + x]->setStyleSheet("background-color: rgb(255, 105, 105); border: 1px solid black");
}

void MainWindow::notified_update_current_time(int second)
{
    int minute = second / 60;
    int hour = minute / 60;
    std::string real_time = "Current time: " + std::to_string(hour/10) + std::to_string(hour%10) + ':' + std::to_string((minute/10)%6) + std::to_string(minute%10) + ':' + std::to_string((second/10)%6) + std::to_string(second%10);
    ui->current_time->setText(QString::fromStdString(real_time));
}

void MainWindow::start_simulation()
{
    gate_in->start();
    canvas_animation->start();
    train_create->start();
}

void MainWindow::mark_intersections()
{
    // Intersection between Line I and II
    map_labels[48]->setText("/");
    map_labels[48]->setAlignment(Qt::AlignCenter);
    map_labels[50]->setText("\\");
    map_labels[50]->setAlignment(Qt::AlignCenter);
    map_labels[71]->setText("/");
    map_labels[71]->setAlignment(Qt::AlignCenter);
    map_labels[73]->setText("\\");
    map_labels[73]->setAlignment(Qt::AlignCenter);
    map_labels[75]->setText("/");
    map_labels[75]->setAlignment(Qt::AlignCenter);

    // Intersection between Line II and III
    map_labels[121]->setText("/");
    map_labels[121]->setAlignment(Qt::AlignCenter);
    map_labels[123]->setText("\\");
    map_labels[123]->setAlignment(Qt::AlignCenter);
    map_labels[130]->setText("\\");
    map_labels[130]->setAlignment(Qt::AlignCenter);
    map_labels[134]->setText("\\");
    map_labels[134]->setAlignment(Qt::AlignCenter);
    map_labels[148]->setText("/");
    map_labels[148]->setAlignment(Qt::AlignCenter);
    map_labels[151]->setText("/");
    map_labels[151]->setAlignment(Qt::AlignCenter);

    // Intersection on Line III
    map_labels[170]->setText("\\");
    map_labels[170]->setAlignment(Qt::AlignCenter);
    map_labels[174]->setText("\\");
    map_labels[174]->setAlignment(Qt::AlignCenter);
    map_labels[186]->setText("/");
    map_labels[186]->setAlignment(Qt::AlignCenter);
    map_labels[189]->setText("/");
    map_labels[189]->setAlignment(Qt::AlignCenter);

    // Intersection between Line III and IV
    map_labels[201]->setText("\\");
    map_labels[201]->setAlignment(Qt::AlignCenter);
    map_labels[203]->setText("\\");
    map_labels[203]->setAlignment(Qt::AlignCenter);
    map_labels[210]->setText("\\");
    map_labels[210]->setAlignment(Qt::AlignCenter);
    map_labels[214]->setText("/");
    map_labels[214]->setAlignment(Qt::AlignCenter);
    map_labels[224]->setText("/");
    map_labels[224]->setAlignment(Qt::AlignCenter);
    map_labels[227]->setText("/");
    map_labels[227]->setAlignment(Qt::AlignCenter);

    // Intersection on Line IV
    map_labels[265]->setText("/");
    map_labels[265]->setAlignment(Qt::AlignCenter);

    // Intersection between Line IV and V
    map_labels[281]->setText("\\");
    map_labels[281]->setAlignment(Qt::AlignCenter);
    map_labels[283]->setText("\\");
    map_labels[283]->setAlignment(Qt::AlignCenter);
    map_labels[290]->setText("/");
    map_labels[290]->setAlignment(Qt::AlignCenter);
    map_labels[300]->setText("/");
    map_labels[300]->setAlignment(Qt::AlignCenter);
    map_labels[303]->setText("/");
    map_labels[303]->setAlignment(Qt::AlignCenter);

    // Intersection on Line V
    map_labels[321]->setText("\\");
    map_labels[321]->setAlignment(Qt::AlignCenter);
    map_labels[341]->setText("/");
    map_labels[341]->setAlignment(Qt::AlignCenter);

    // Intersection between Line V and VI
    map_labels[361]->setText("\\");
    map_labels[361]->setAlignment(Qt::AlignCenter);
    map_labels[363]->setText("\\");
    map_labels[363]->setAlignment(Qt::AlignCenter);
    map_labels[366]->setText("/");
    map_labels[366]->setAlignment(Qt::AlignCenter);
    map_labels[376]->setText("/");
    map_labels[376]->setAlignment(Qt::AlignCenter);
    map_labels[379]->setText("/");
    map_labels[379]->setAlignment(Qt::AlignCenter);

    // Intersection between Line VI and VII
    map_labels[441]->setText("\\");
    map_labels[441]->setAlignment(Qt::AlignCenter);
    map_labels[443]->setText("\\");
    map_labels[443]->setAlignment(Qt::AlignCenter);
    map_labels[445]->setText("/");
    map_labels[445]->setAlignment(Qt::AlignCenter);
    map_labels[455]->setText("/");
    map_labels[455]->setAlignment(Qt::AlignCenter);

    // Intersection on Line VII
    map_labels[493]->setText("/");
    map_labels[493]->setAlignment(Qt::AlignCenter);

    // Intersection between Line VII and VIII
    map_labels[521]->setText("\\");
    map_labels[521]->setAlignment(Qt::AlignCenter);
    map_labels[523]->setText("\\");
    map_labels[523]->setAlignment(Qt::AlignCenter);
    map_labels[531]->setText("/");
    map_labels[531]->setAlignment(Qt::AlignCenter);

    // Intersection on Line VIII
    map_labels[569]->setText("/");
    map_labels[569]->setAlignment(Qt::AlignCenter);
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


void MainWindow::on_train_speed_button_clicked()
{
    canvas_animation->set_block_per_second(ui->train_speed_spinbox->value());
    ui->train_speed_desc->setText(QString::fromStdString("Current train speed: " + std::to_string(ui->train_speed_spinbox->value()) + " block(s) per second"));
}


void MainWindow::on_train_interval_button_clicked()
{
    train_create->setTrain_interval(ui->train_interval_spinbox->value());
}


void MainWindow::on_pause_button_clicked()
{
    if(start == false)
    {
        start = true;
        ui->pause_button->setText("Pause");
        this->start_simulation();
        return;
    }
    if(gate_in->get_pause())
    {
        gate_in->set_pause(false);
        canvas_animation->set_pause(false);
        train_create->set_pause(false);
        ui->pause_button->setText("Pause");
    }
    else
    {
        gate_in->set_pause(true);
        canvas_animation->set_pause(true);
        train_create->set_pause(true);
        ui->pause_button->setText("Continue");
    }
}

