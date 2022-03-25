#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <train_maker.h>
#include <animation.h>

#define BLOCK_X 40
#define BLOCK_Y 30

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
    void notified_update_incoming_train(QString);

private slots:

    void on_multiplier_button_clicked();

    void on_platform_stay_button_clicked();

    void on_mine_duration_button_clicked();

    void on_train_speed_button_clicked();

private:
    Gate_In_Manager* gate_in;
    Train_maker* train_create;
    Animation* canvas_animation;
    std::pair<QLabel*, Train*> **train_labels;
    QLabel** map_labels;

    void start_simulation();
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
