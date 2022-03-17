#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //testing
    for(int i = 0; i < PLATFORM_SUM; i++){
            train_labels[i] = new QLabel(this);
            train_labels[i]->setGeometry(1790, 272, 111, 41);
    //        train_labels[i]->setFont("font: 18pt");
            train_labels[i]->setStyleSheet("font: 18pt");
        }

    Database database(2);
    gate_in = new Gate_In_Manager(this);
    train_create = new Train_maker(this);
    canvas_animation = new Animation(this);

    connect(gate_in, SIGNAL(train_in_entrance(int,Train*)), this, SLOT(train_entering(int,Train*))); // connect train masuk ke queue
    connect(train_create, SIGNAL(notify_gate_in(Train*)), gate_in, SLOT(on_new_train_notified(Train*))); // connect pasang train
    connect(gate_in, SIGNAL(notify_animation(int,bool)), canvas_animation, SLOT(start_animating(int,bool)));
    connect(canvas_animation, SIGNAL(move_entering_on_canvas(int)), this, SLOT(move_train(int))); // connect animasi
    connect(canvas_animation, SIGNAL(move_exiting_on_canvas(int)), this, SLOT(move_train(int))); // connect animasi
    connect(canvas_animation, SIGNAL(destroy_train(int)), gate_in, SLOT(notified_to_remove_train(int))); // kelar animasi delete train
    connect(gate_in, SIGNAL(notify_canvas_to_destroy_train(int)), this, SLOT(reset_train_on_canvas(int))); // reset train
    gate_in->start();
    train_create->start();
    canvas_animation->start();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::train_entering(int i, Train* input)
{
    train_labels[i]->setText("Train " + QString::number(input->getId()));
}

void MainWindow::move_train(int i)
{
    int y = 272 - (i * 50);
    if(train_labels[i]->x() == 1790)
        train_labels[i]->setGeometry(1650, train_labels[i]->y(), train_labels[i]->width(), train_labels[i]->height());
    else
    {
        if(train_labels[i]->y() > y)
            train_labels[i]->setGeometry(train_labels[i]->x(), train_labels[i]->y()-50, train_labels[i]->width(), train_labels[i]->height());
        train_labels[i]->setGeometry(train_labels[i]->x()-90, train_labels[i]->y(), train_labels[i]->width(), train_labels[i]->height());
    }
}

void MainWindow::reset_train_on_canvas(int i)
{
    if(i == 0)
    {
//        qDebug() << "gerakin kereta di kanvas" << '\n';
        train_labels[i]->setGeometry(1790, 272, 111, 41);
        train_labels[i]->setText("");
    }
}

