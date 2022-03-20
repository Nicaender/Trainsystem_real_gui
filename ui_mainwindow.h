/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QSpinBox *train_interval_spinbox;
    QLabel *Background;
    QLCDNumber *out_cd_counter;
    QLabel *start_background;
    QLabel *train_interval_text;
    QSpinBox *multiplier_spinbox;
    QPushButton *execute_button;
    QLabel *multiplier_text;
    QLabel *timer;
    QLabel *clock;
    QPushButton *start_button;
    QLabel *in_waiting_list;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1961, 531);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        train_interval_spinbox = new QSpinBox(centralwidget);
        train_interval_spinbox->setObjectName(QString::fromUtf8("train_interval_spinbox"));
        train_interval_spinbox->setGeometry(QRect(115, 50, 71, 31));
        QFont font;
        font.setPointSize(18);
        train_interval_spinbox->setFont(font);
        train_interval_spinbox->setMinimum(1);
        train_interval_spinbox->setValue(30);
        Background = new QLabel(centralwidget);
        Background->setObjectName(QString::fromUtf8("Background"));
        Background->setGeometry(QRect(0, 200, 1961, 331));
        Background->setPixmap(QPixmap(QString::fromUtf8(":/Images/Images/TrainSim.jpg")));
        Background->setScaledContents(true);
        out_cd_counter = new QLCDNumber(centralwidget);
        out_cd_counter->setObjectName(QString::fromUtf8("out_cd_counter"));
        out_cd_counter->setGeometry(QRect(30, 450, 31, 31));
        out_cd_counter->setFrameShadow(QFrame::Raised);
        out_cd_counter->setDigitCount(2);
        out_cd_counter->setSegmentStyle(QLCDNumber::Flat);
        start_background = new QLabel(centralwidget);
        start_background->setObjectName(QString::fromUtf8("start_background"));
        start_background->setGeometry(QRect(0, 0, 1961, 531));
        start_background->setAutoFillBackground(true);
        train_interval_text = new QLabel(centralwidget);
        train_interval_text->setObjectName(QString::fromUtf8("train_interval_text"));
        train_interval_text->setGeometry(QRect(0, 50, 101, 21));
        QFont font1;
        font1.setPointSize(12);
        train_interval_text->setFont(font1);
        multiplier_spinbox = new QSpinBox(centralwidget);
        multiplier_spinbox->setObjectName(QString::fromUtf8("multiplier_spinbox"));
        multiplier_spinbox->setGeometry(QRect(115, 10, 71, 31));
        multiplier_spinbox->setFont(font);
        multiplier_spinbox->setMinimum(1);
        multiplier_spinbox->setMaximum(100);
        multiplier_spinbox->setValue(1);
        execute_button = new QPushButton(centralwidget);
        execute_button->setObjectName(QString::fromUtf8("execute_button"));
        execute_button->setGeometry(QRect(5, 90, 61, 21));
        execute_button->setFont(font1);
        multiplier_text = new QLabel(centralwidget);
        multiplier_text->setObjectName(QString::fromUtf8("multiplier_text"));
        multiplier_text->setGeometry(QRect(0, 10, 111, 21));
        multiplier_text->setFont(font1);
        timer = new QLabel(centralwidget);
        timer->setObjectName(QString::fromUtf8("timer"));
        timer->setGeometry(QRect(1750, 0, 81, 41));
        QFont font2;
        font2.setPointSize(20);
        timer->setFont(font2);
        clock = new QLabel(centralwidget);
        clock->setObjectName(QString::fromUtf8("clock"));
        clock->setGeometry(QRect(1830, 0, 121, 41));
        clock->setFont(font2);
        start_button = new QPushButton(centralwidget);
        start_button->setObjectName(QString::fromUtf8("start_button"));
        start_button->setGeometry(QRect(900, 240, 231, 31));
        start_button->setFont(font2);
        in_waiting_list = new QLabel(centralwidget);
        in_waiting_list->setObjectName(QString::fromUtf8("in_waiting_list"));
        in_waiting_list->setGeometry(QRect(520, 10, 971, 31));
        in_waiting_list->setFont(font1);
        MainWindow->setCentralWidget(centralwidget);
        Background->raise();
        out_cd_counter->raise();
        multiplier_spinbox->raise();
        execute_button->raise();
        multiplier_text->raise();
        timer->raise();
        clock->raise();
        train_interval_spinbox->raise();
        train_interval_text->raise();
        in_waiting_list->raise();
        start_background->raise();
        start_button->raise();
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        Background->setText(QString());
        start_background->setText(QString());
        train_interval_text->setText(QCoreApplication::translate("MainWindow", "Train interval: ", nullptr));
        execute_button->setText(QCoreApplication::translate("MainWindow", "Execute", nullptr));
        multiplier_text->setText(QCoreApplication::translate("MainWindow", "Fast forwarding: ", nullptr));
        timer->setText(QCoreApplication::translate("MainWindow", "Timer: ", nullptr));
        clock->setText(QString());
        start_button->setText(QCoreApplication::translate("MainWindow", "Start the simulator", nullptr));
        in_waiting_list->setText(QCoreApplication::translate("MainWindow", "Next Train: ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
