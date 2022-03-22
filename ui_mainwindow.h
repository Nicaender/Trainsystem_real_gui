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
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *Background;
    QLCDNumber *out_cd_counter;
    QLabel *start_background;
    QLabel *train_interval_text;
    QLabel *multiplier_text;
    QLabel *timer;
    QLabel *clock;
    QPushButton *start_button;
    QLabel *in_waiting_list;
    QSlider *multiplier_slider;
    QSlider *train_interval_slider;
    QLabel *multiplier_min_max;
    QLabel *train_interval_min_max;
    QLCDNumber *multiplier_current;
    QLCDNumber *train_interval_current;
    QSlider *stay_duration_slider;
    QLabel *stay_duration_text;
    QLabel *stay_duration_min_max;
    QLCDNumber *stay_duration_current;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1961, 531);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
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
        train_interval_text->setGeometry(QRect(190, 10, 101, 21));
        QFont font;
        font.setPointSize(12);
        train_interval_text->setFont(font);
        multiplier_text = new QLabel(centralwidget);
        multiplier_text->setObjectName(QString::fromUtf8("multiplier_text"));
        multiplier_text->setGeometry(QRect(20, 10, 111, 21));
        multiplier_text->setFont(font);
        timer = new QLabel(centralwidget);
        timer->setObjectName(QString::fromUtf8("timer"));
        timer->setGeometry(QRect(1750, 0, 81, 41));
        QFont font1;
        font1.setPointSize(20);
        timer->setFont(font1);
        clock = new QLabel(centralwidget);
        clock->setObjectName(QString::fromUtf8("clock"));
        clock->setGeometry(QRect(1830, 0, 121, 41));
        clock->setFont(font1);
        start_button = new QPushButton(centralwidget);
        start_button->setObjectName(QString::fromUtf8("start_button"));
        start_button->setGeometry(QRect(900, 240, 231, 31));
        start_button->setFont(font1);
        in_waiting_list = new QLabel(centralwidget);
        in_waiting_list->setObjectName(QString::fromUtf8("in_waiting_list"));
        in_waiting_list->setGeometry(QRect(520, 10, 971, 31));
        in_waiting_list->setFont(font);
        multiplier_slider = new QSlider(centralwidget);
        multiplier_slider->setObjectName(QString::fromUtf8("multiplier_slider"));
        multiplier_slider->setGeometry(QRect(10, 35, 121, 16));
        multiplier_slider->setMinimum(1);
        multiplier_slider->setMaximum(100);
        multiplier_slider->setPageStep(5);
        multiplier_slider->setOrientation(Qt::Horizontal);
        train_interval_slider = new QSlider(centralwidget);
        train_interval_slider->setObjectName(QString::fromUtf8("train_interval_slider"));
        train_interval_slider->setGeometry(QRect(180, 35, 111, 16));
        train_interval_slider->setMinimum(5);
        train_interval_slider->setMaximum(75);
        train_interval_slider->setPageStep(5);
        train_interval_slider->setValue(20);
        train_interval_slider->setOrientation(Qt::Horizontal);
        multiplier_min_max = new QLabel(centralwidget);
        multiplier_min_max->setObjectName(QString::fromUtf8("multiplier_min_max"));
        multiplier_min_max->setGeometry(QRect(10, 50, 151, 21));
        QFont font2;
        font2.setPointSize(15);
        multiplier_min_max->setFont(font2);
        train_interval_min_max = new QLabel(centralwidget);
        train_interval_min_max->setObjectName(QString::fromUtf8("train_interval_min_max"));
        train_interval_min_max->setGeometry(QRect(180, 50, 141, 21));
        train_interval_min_max->setFont(font2);
        multiplier_current = new QLCDNumber(centralwidget);
        multiplier_current->setObjectName(QString::fromUtf8("multiplier_current"));
        multiplier_current->setGeometry(QRect(50, 50, 41, 31));
        multiplier_current->setFrameShadow(QFrame::Raised);
        multiplier_current->setDigitCount(3);
        multiplier_current->setSegmentStyle(QLCDNumber::Flat);
        train_interval_current = new QLCDNumber(centralwidget);
        train_interval_current->setObjectName(QString::fromUtf8("train_interval_current"));
        train_interval_current->setGeometry(QRect(220, 50, 31, 31));
        train_interval_current->setFrameShadow(QFrame::Raised);
        train_interval_current->setDigitCount(2);
        train_interval_current->setSegmentStyle(QLCDNumber::Flat);
        stay_duration_slider = new QSlider(centralwidget);
        stay_duration_slider->setObjectName(QString::fromUtf8("stay_duration_slider"));
        stay_duration_slider->setGeometry(QRect(330, 35, 111, 16));
        stay_duration_slider->setMinimum(0);
        stay_duration_slider->setMaximum(30);
        stay_duration_slider->setPageStep(5);
        stay_duration_slider->setValue(15);
        stay_duration_slider->setOrientation(Qt::Horizontal);
        stay_duration_text = new QLabel(centralwidget);
        stay_duration_text->setObjectName(QString::fromUtf8("stay_duration_text"));
        stay_duration_text->setGeometry(QRect(340, 10, 101, 21));
        stay_duration_text->setFont(font);
        stay_duration_min_max = new QLabel(centralwidget);
        stay_duration_min_max->setObjectName(QString::fromUtf8("stay_duration_min_max"));
        stay_duration_min_max->setGeometry(QRect(330, 50, 141, 21));
        stay_duration_min_max->setFont(font2);
        stay_duration_current = new QLCDNumber(centralwidget);
        stay_duration_current->setObjectName(QString::fromUtf8("stay_duration_current"));
        stay_duration_current->setGeometry(QRect(370, 50, 31, 31));
        stay_duration_current->setFrameShadow(QFrame::Raised);
        stay_duration_current->setDigitCount(2);
        stay_duration_current->setSegmentStyle(QLCDNumber::Flat);
        MainWindow->setCentralWidget(centralwidget);
        Background->raise();
        out_cd_counter->raise();
        multiplier_text->raise();
        timer->raise();
        clock->raise();
        train_interval_text->raise();
        in_waiting_list->raise();
        multiplier_slider->raise();
        train_interval_slider->raise();
        multiplier_min_max->raise();
        train_interval_min_max->raise();
        multiplier_current->raise();
        train_interval_current->raise();
        stay_duration_slider->raise();
        stay_duration_text->raise();
        stay_duration_min_max->raise();
        stay_duration_current->raise();
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
        train_interval_text->setText(QCoreApplication::translate("MainWindow", "Train interval", nullptr));
        multiplier_text->setText(QCoreApplication::translate("MainWindow", "Fast forwarding", nullptr));
        timer->setText(QCoreApplication::translate("MainWindow", "Timer: ", nullptr));
        clock->setText(QString());
        start_button->setText(QCoreApplication::translate("MainWindow", "Start the simulator", nullptr));
        in_waiting_list->setText(QCoreApplication::translate("MainWindow", "Next Train: ", nullptr));
        multiplier_min_max->setText(QCoreApplication::translate("MainWindow", "1               100", nullptr));
        train_interval_min_max->setText(QCoreApplication::translate("MainWindow", "5               75", nullptr));
        stay_duration_text->setText(QCoreApplication::translate("MainWindow", "Stay duration", nullptr));
        stay_duration_min_max->setText(QCoreApplication::translate("MainWindow", "0               30", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
