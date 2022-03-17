#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <gate_in_manager.h>
#include <train_maker.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Gate_In_Manager* gate_in;
    Train_maker* train_create;


public slots:
    void train_entering(int, Train*);

private:
    enum direction {left, right, up, down};
    void move_train();
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
