#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for(int i = 0; i < PLATFORM_SUM; i++){
        train_labels[i] = new QLabel(this);
        train_labels[i]->setGeometry(1790, 472, 111, 41);
    }

    ui->in_waiting_list->setStyleSheet("border: 1px solid black;");

    gate_in = new Gate_In_Manager(this);
    train_create = new Train_maker(this);
    canvas_animation = new Animation(this);

    connect(gate_in, SIGNAL(update_cooldown_canvas(int)), this, SLOT(update_out_cooldown(int))); // update waktu
    connect(gate_in, SIGNAL(time_update(int)), this, SLOT(time_update(int))); // update jam
    connect(gate_in, SIGNAL(update_in_waiting_list(QString)), this, SLOT(update_in_waiting_list(QString))); // connect waiting list dari luar
    connect(train_create, SIGNAL(notify_gate_in(Train*)), gate_in, SLOT(on_new_train_notified(Train*))); // Train to station
    connect(gate_in, SIGNAL(train_in_entrance(int,Train*)), this, SLOT(train_entering(int,Train*))); // dari gate bikin kereta
    connect(this, SIGNAL(notify_animation(int,bool,Train*)), canvas_animation, SLOT(start_animating(int,bool,Train*))); // dari canvas suruh gerakin animasi
    connect(canvas_animation, SIGNAL(move_entering_on_canvas(int)), this, SLOT(move_train(int))); // dari animasi gerakin di canvas
    connect(canvas_animation, SIGNAL(train_arrived_on_platform(int,Train*)), gate_in, SLOT(set_train_on_platform(int,Train*))); // notif bahwa kereta sampai
    connect(gate_in, SIGNAL(change_color_to_red(int)), this, SLOT(change_to_red_train(int))); // ubah kereta jadi merah kalo mau keluar
    connect(gate_in, SIGNAL(notify_animation(int,bool,Train*)), canvas_animation, SLOT(start_animating(int,bool,Train*))); // notif untuk keluarin kereta
    connect(canvas_animation, SIGNAL(move_exiting_on_canvas(int)), this, SLOT(move_train(int))); // dari animasi gerakin di canvas
    connect(canvas_animation, SIGNAL(destroy_train(int)), this, SLOT(reset_train_on_canvas(int))); // delete kereta di canvas
    connect(this, SIGNAL(notify_gate_to_cooldown(int)), gate_in, SLOT(notified_to_remove_train(int))); // dari canvas delete kereta di gate
}

MainWindow::~MainWindow()
{
    gate_in->terminate();
    train_create->terminate();
    canvas_animation->terminate();
    delete ui;
}

void MainWindow::train_entering(int i, Train* input)
{
    train_labels[i]->setText("Train " + QString::number(input->getId()));
    train_labels[i]->setStyleSheet("background-color:rgb(205,255,205);font: 18pt;");
    train_labels[i]->setAutoFillBackground(true);
    emit notify_animation(i, true, input);
}

void MainWindow::move_train(int i)
{
    int y = 472 - (i * 50);
    if(train_labels[i]->x() > 1650)
        train_labels[i]->move(train_labels[i]->x()-140, train_labels[i]->y()); // kalau mau pakai smoother animation, di bagi dengan speed yang diinginkan
    else if(train_labels[i]->x() > 710)
    {
        if(train_labels[i]->y() > y)
            train_labels[i]->move(train_labels[i]->x(), train_labels[i]->y()-50); // kalau mau pakai smoother animation, di bagi dengan speed yang diinginkan
        train_labels[i]->move(train_labels[i]->x()-90, train_labels[i]->y()); // kalau mau pakai smoother animation, di bagi dengan speed yang diinginkan
    }
    else
    {
        if(train_labels[i]->y() < 472 && train_labels[i]->x() < (710 - 90 * (PLATFORM_SUM - i)))
            train_labels[i]->move(train_labels[i]->x(), train_labels[i]->y()+50); // kalau mau pakai smoother animation, di bagi dengan speed yang diinginkan
        train_labels[i]->move(train_labels[i]->x()-90, train_labels[i]->y()); // kalau mau pakai smoother animation, di bagi dengan speed yang diinginkan
    }
}

void MainWindow::reset_train_on_canvas(int i)
{
    train_labels[i]->move(1790, 472);
    train_labels[i]->setText("");
    train_labels[i]->setStyleSheet("font: 18pt;");
    train_labels[i]->setAutoFillBackground(false);
    emit notify_gate_to_cooldown(i);
}

void MainWindow::update_out_cooldown(int i)
{
    ui->out_cd_counter->display(i);
}

void MainWindow::time_update(int time)
{
    int second = time % 60;
    int minute = time / 60;
    int hour = minute / 60;
    ui->clock->setText(QString::number(hour / 10) + QString::number(hour % 10) + QString::fromStdString(":") + QString::number((minute / 10) % 6) + QString::number(minute % 10) + QString::fromStdString(":") + QString::number(second / 10) + QString::number(second % 10));
}

void MainWindow::change_to_red_train(int i)
{
    train_labels[i]->setStyleSheet("background-color:rgb(255,205,205);font: 18pt;");
}

void MainWindow::update_in_waiting_list(QString i)
{
    ui->in_waiting_list->setText(i);
}

void MainWindow::start_simulation()
{
    gate_in->start();
    canvas_animation->start();
    train_create->start();
}

void MainWindow::on_start_button_clicked()
{
    ui->start_background->hide();
    ui->start_button->hide();
    train_create->trail_interval = ui->train_interval_spinbox->value();
    this->start_simulation();
}

void MainWindow::on_execute_button_clicked()
{
    train_create->trail_interval = ui->train_interval_spinbox->value();
    gate_in->setMultiplier(ui->multiplier_spinbox->value());
    canvas_animation->setMultiplier(ui->multiplier_spinbox->value());
    train_create->setMultiplier(ui->multiplier_spinbox->value());
}

