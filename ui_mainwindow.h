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
    QLabel *incoming_train_text;
    QSpinBox *multiplier_spinbox;
    QPushButton *multiplier_button;
    QLabel *multiplier_text;
    QSpinBox *platform_stay_spinbox;
    QLabel *platform_stay_text;
    QPushButton *platform_stay_button;
    QLabel *mine_duration_text;
    QPushButton *mine_duration_button;
    QSpinBox *mine_duration_spinbox;
    QLabel *train_speed_text;
    QSpinBox *train_speed_spinbox;
    QPushButton *train_speed_button;
    QSpinBox *train_interval_spinbox;
    QLabel *train_interval_text;
    QPushButton *train_interval_button;
    QLabel *current_time;
    QLabel *legend_rail;
    QLabel *legend_rail_2;
    QLabel *legend_rail_3;
    QLabel *legend_text;
    QLabel *legend_text_2;
    QLabel *legend_text_3;
    QLabel *train_speed_desc;
    QPushButton *pause_button;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1560, 760);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        incoming_train_text = new QLabel(centralwidget);
        incoming_train_text->setObjectName(QString::fromUtf8("incoming_train_text"));
        incoming_train_text->setGeometry(QRect(5, 5, 1200, 30));
        QFont font;
        font.setPointSize(15);
        incoming_train_text->setFont(font);
        incoming_train_text->setFrameShape(QFrame::Box);
        multiplier_spinbox = new QSpinBox(centralwidget);
        multiplier_spinbox->setObjectName(QString::fromUtf8("multiplier_spinbox"));
        multiplier_spinbox->setGeometry(QRect(1450, 25, 61, 51));
        QFont font1;
        font1.setPointSize(14);
        multiplier_spinbox->setFont(font1);
        multiplier_spinbox->setAlignment(Qt::AlignCenter);
        multiplier_spinbox->setMinimum(1);
        multiplier_spinbox->setMaximum(100);
        multiplier_spinbox->setValue(1);
        multiplier_button = new QPushButton(centralwidget);
        multiplier_button->setObjectName(QString::fromUtf8("multiplier_button"));
        multiplier_button->setGeometry(QRect(1440, 80, 80, 24));
        multiplier_text = new QLabel(centralwidget);
        multiplier_text->setObjectName(QString::fromUtf8("multiplier_text"));
        multiplier_text->setGeometry(QRect(1400, 0, 151, 21));
        multiplier_text->setFont(font1);
        multiplier_text->setAlignment(Qt::AlignCenter);
        platform_stay_spinbox = new QSpinBox(centralwidget);
        platform_stay_spinbox->setObjectName(QString::fromUtf8("platform_stay_spinbox"));
        platform_stay_spinbox->setGeometry(QRect(1285, 25, 71, 51));
        platform_stay_spinbox->setFont(font1);
        platform_stay_spinbox->setAlignment(Qt::AlignCenter);
        platform_stay_spinbox->setMinimum(1);
        platform_stay_spinbox->setMaximum(1000);
        platform_stay_spinbox->setValue(10);
        platform_stay_text = new QLabel(centralwidget);
        platform_stay_text->setObjectName(QString::fromUtf8("platform_stay_text"));
        platform_stay_text->setGeometry(QRect(1240, 0, 161, 21));
        platform_stay_text->setFont(font1);
        platform_stay_text->setAlignment(Qt::AlignCenter);
        platform_stay_button = new QPushButton(centralwidget);
        platform_stay_button->setObjectName(QString::fromUtf8("platform_stay_button"));
        platform_stay_button->setGeometry(QRect(1280, 80, 80, 24));
        mine_duration_text = new QLabel(centralwidget);
        mine_duration_text->setObjectName(QString::fromUtf8("mine_duration_text"));
        mine_duration_text->setGeometry(QRect(1240, 105, 161, 21));
        mine_duration_text->setFont(font1);
        mine_duration_text->setAlignment(Qt::AlignCenter);
        mine_duration_button = new QPushButton(centralwidget);
        mine_duration_button->setObjectName(QString::fromUtf8("mine_duration_button"));
        mine_duration_button->setGeometry(QRect(1280, 185, 80, 24));
        mine_duration_spinbox = new QSpinBox(centralwidget);
        mine_duration_spinbox->setObjectName(QString::fromUtf8("mine_duration_spinbox"));
        mine_duration_spinbox->setGeometry(QRect(1285, 130, 71, 51));
        mine_duration_spinbox->setFont(font1);
        mine_duration_spinbox->setAlignment(Qt::AlignCenter);
        mine_duration_spinbox->setMinimum(1);
        mine_duration_spinbox->setMaximum(1000);
        mine_duration_spinbox->setValue(60);
        train_speed_text = new QLabel(centralwidget);
        train_speed_text->setObjectName(QString::fromUtf8("train_speed_text"));
        train_speed_text->setGeometry(QRect(1400, 105, 151, 21));
        train_speed_text->setFont(font1);
        train_speed_text->setAlignment(Qt::AlignCenter);
        train_speed_spinbox = new QSpinBox(centralwidget);
        train_speed_spinbox->setObjectName(QString::fromUtf8("train_speed_spinbox"));
        train_speed_spinbox->setGeometry(QRect(1450, 130, 61, 51));
        train_speed_spinbox->setFont(font1);
        train_speed_spinbox->setAlignment(Qt::AlignCenter);
        train_speed_spinbox->setMinimum(1);
        train_speed_spinbox->setMaximum(10);
        train_speed_spinbox->setValue(1);
        train_speed_button = new QPushButton(centralwidget);
        train_speed_button->setObjectName(QString::fromUtf8("train_speed_button"));
        train_speed_button->setGeometry(QRect(1440, 185, 80, 24));
        train_interval_spinbox = new QSpinBox(centralwidget);
        train_interval_spinbox->setObjectName(QString::fromUtf8("train_interval_spinbox"));
        train_interval_spinbox->setGeometry(QRect(1140, 130, 61, 51));
        train_interval_spinbox->setFont(font1);
        train_interval_spinbox->setAlignment(Qt::AlignCenter);
        train_interval_spinbox->setMinimum(10);
        train_interval_spinbox->setMaximum(120);
        train_interval_spinbox->setValue(20);
        train_interval_text = new QLabel(centralwidget);
        train_interval_text->setObjectName(QString::fromUtf8("train_interval_text"));
        train_interval_text->setGeometry(QRect(1090, 105, 151, 21));
        train_interval_text->setFont(font1);
        train_interval_text->setAlignment(Qt::AlignCenter);
        train_interval_button = new QPushButton(centralwidget);
        train_interval_button->setObjectName(QString::fromUtf8("train_interval_button"));
        train_interval_button->setGeometry(QRect(1130, 185, 80, 24));
        current_time = new QLabel(centralwidget);
        current_time->setObjectName(QString::fromUtf8("current_time"));
        current_time->setGeometry(QRect(5, 40, 261, 21));
        current_time->setFont(font1);
        legend_rail = new QLabel(centralwidget);
        legend_rail->setObjectName(QString::fromUtf8("legend_rail"));
        legend_rail->setGeometry(QRect(1390, 630, 40, 30));
        legend_rail->setStyleSheet(QString::fromUtf8("background-color: rgb(205, 255, 205); border: 1px solid black;"));
        legend_rail_2 = new QLabel(centralwidget);
        legend_rail_2->setObjectName(QString::fromUtf8("legend_rail_2"));
        legend_rail_2->setGeometry(QRect(1390, 665, 40, 30));
        legend_rail_2->setStyleSheet(QString::fromUtf8("background-color: rgb(205, 205, 255); border: 1px solid black;"));
        legend_rail_3 = new QLabel(centralwidget);
        legend_rail_3->setObjectName(QString::fromUtf8("legend_rail_3"));
        legend_rail_3->setGeometry(QRect(1390, 700, 40, 30));
        legend_rail_3->setStyleSheet(QString::fromUtf8("background-color: rgb(105, 155, 205); border: 1px solid black;"));
        legend_text = new QLabel(centralwidget);
        legend_text->setObjectName(QString::fromUtf8("legend_text"));
        legend_text->setGeometry(QRect(1440, 630, 61, 31));
        legend_text->setFont(font1);
        legend_text_2 = new QLabel(centralwidget);
        legend_text_2->setObjectName(QString::fromUtf8("legend_text_2"));
        legend_text_2->setGeometry(QRect(1440, 665, 111, 31));
        legend_text_2->setFont(font1);
        legend_text_3 = new QLabel(centralwidget);
        legend_text_3->setObjectName(QString::fromUtf8("legend_text_3"));
        legend_text_3->setGeometry(QRect(1440, 700, 71, 31));
        legend_text_3->setFont(font1);
        train_speed_desc = new QLabel(centralwidget);
        train_speed_desc->setObjectName(QString::fromUtf8("train_speed_desc"));
        train_speed_desc->setGeometry(QRect(5, 70, 381, 21));
        train_speed_desc->setFont(font1);
        pause_button = new QPushButton(centralwidget);
        pause_button->setObjectName(QString::fromUtf8("pause_button"));
        pause_button->setGeometry(QRect(5, 100, 151, 41));
        QFont font2;
        font2.setPointSize(16);
        pause_button->setFont(font2);
        MainWindow->setCentralWidget(centralwidget);
        incoming_train_text->raise();
        multiplier_spinbox->raise();
        multiplier_button->raise();
        multiplier_text->raise();
        platform_stay_spinbox->raise();
        platform_stay_text->raise();
        platform_stay_button->raise();
        mine_duration_text->raise();
        mine_duration_button->raise();
        mine_duration_spinbox->raise();
        train_speed_text->raise();
        train_speed_spinbox->raise();
        train_speed_button->raise();
        train_interval_spinbox->raise();
        train_interval_text->raise();
        train_interval_button->raise();
        current_time->raise();
        train_speed_desc->raise();
        pause_button->raise();
        legend_rail->raise();
        legend_text->raise();
        legend_text_3->raise();
        legend_text_2->raise();
        legend_rail_3->raise();
        legend_rail_2->raise();
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        incoming_train_text->setText(QString());
        multiplier_button->setText(QCoreApplication::translate("MainWindow", "Confirm", nullptr));
        multiplier_text->setText(QCoreApplication::translate("MainWindow", "Speed multiplier", nullptr));
        platform_stay_text->setText(QCoreApplication::translate("MainWindow", "Platform duration", nullptr));
        platform_stay_button->setText(QCoreApplication::translate("MainWindow", "Confirm", nullptr));
        mine_duration_text->setText(QCoreApplication::translate("MainWindow", "Mine duration", nullptr));
        mine_duration_button->setText(QCoreApplication::translate("MainWindow", "Confirm", nullptr));
        train_speed_text->setText(QCoreApplication::translate("MainWindow", "Train speed", nullptr));
        train_speed_button->setText(QCoreApplication::translate("MainWindow", "Confirm", nullptr));
        train_interval_text->setText(QCoreApplication::translate("MainWindow", "Train interval", nullptr));
        train_interval_button->setText(QCoreApplication::translate("MainWindow", "Confirm", nullptr));
        current_time->setText(QCoreApplication::translate("MainWindow", "Current Time: ", nullptr));
        legend_rail->setText(QString());
        legend_rail_2->setText(QString());
        legend_rail_3->setText(QString());
        legend_text->setText(QCoreApplication::translate("MainWindow", "= Rail", nullptr));
        legend_text_2->setText(QCoreApplication::translate("MainWindow", "= Platform", nullptr));
        legend_text_3->setText(QCoreApplication::translate("MainWindow", "= Mine", nullptr));
        train_speed_desc->setText(QCoreApplication::translate("MainWindow", "Current train speed: 1 block(s) per second", nullptr));
        pause_button->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
