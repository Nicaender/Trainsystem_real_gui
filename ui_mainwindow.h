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
        incoming_train_text->setGeometry(QRect(0, 0, 1200, 30));
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
        MainWindow->setCentralWidget(centralwidget);
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
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
