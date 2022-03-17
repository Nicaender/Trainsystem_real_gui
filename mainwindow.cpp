#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    train_thread = new TrainGenerator(this);
    connect(train_thread, SIGNAL(TrainGenerated(Train*)), this, SLOT(onTrainGenerated(Train*)));
    QLabel* q = new QLabel(this);
    q->setGeometry(1410, 480, 261, 191);
    q->setProperty("text", "text label");
    q->setStyleSheet("font: 18pt");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTrainGenerated(Train *)
{
    // handler if a train has been generated
}

/**
 *
 * How to create a qlabel object for trains
 *
    QLabel* q = new QLabel(this);
    q->setGeometry(1410, 480, 261, 191);
    q->setProperty("text", "text label");
    q->setStyleSheet("font: 18pt");
 *
 *
 *
 *   <widget class="QLabel" name="label">
    <property name="geometry">
     <rect>
      <x>10</x>
      <y>20</y>
      <width>171</width>
      <height>41</height>
     </rect>
    </property>
    <property name="font">
     <font>
      <pointsize>15</pointsize>
     </font>
    </property>
    <property name="text">
     <string>TextLabel</string>
    </property>
   </widget>
*/
