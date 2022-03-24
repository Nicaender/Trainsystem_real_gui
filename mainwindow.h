#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
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

signals:

public slots:
    void notified_train_label_attach(Train*);
    void notified_put_train_on_canvas(Train*);
    void notified_move_train(Train*,Infrastructure*);
    void notified_train_label_detach(Train*);
    void notified_color(int, int, int);
    void notified_change_color(Train*);

private slots:

private:
    Gate_In_Manager* gate_in;
    Train_maker* train_create;
    Animation* canvas_animation;
    std::pair<QLabel*, Train*> **train_labels;
    QLabel** map_labels;

    void start_simulation();
    void background_initialization();
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
