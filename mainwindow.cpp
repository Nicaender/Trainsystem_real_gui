#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //testing
    Database database(2);
    gate_in = new Gate_In_Manager(this);
    train_create = new Train_maker(this);

    connect(gate_in, SIGNAL(train_coming(int,Train*)), this, SLOT(train_entering(int,Train*)));
    connect(train_create, SIGNAL(notify_new_train(Train*)), gate_in, SLOT(on_new_train_notified(Train*)));
//    gate_in->start();
    train_create->start();

    qDebug() << train_interval << '\n';

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::train_entering(int i, Train* input)
{
    if(i == 0)
        ui->Train1->setText("Train " + QString::number(input->getId()));
}

