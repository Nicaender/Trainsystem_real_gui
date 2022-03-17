#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <gate_in_manager.h>
#include <train_maker.h>
#include <animation.h>

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
    Animation* canvas_animation;


public slots:
    void train_entering(int, Train*);
    void move_train(int);
    void reset_train_on_canvas(int);

private:
    QLabel** train_labels = new QLabel*[PLATFORM_SUM];
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
