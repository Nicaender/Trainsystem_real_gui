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
    Gate_In_Manager* gate_in;
    Train_maker* train_create;
    Animation* canvas_animation;

signals:
    void notify_gate_to_cooldown(int);
    void notify_animation(int, bool, Train*);

public slots:
    void train_entering(int, Train*);
    void move_train(int);
    void reset_train_on_canvas(int);
    void update_out_cooldown(int);
    void time_update(int);
    void change_to_red_train(int);
    void update_in_waiting_list(QString);

private slots:

    void on_start_button_clicked();

    void on_multiplier_slider_sliderMoved(int position);

    void on_train_interval_slider_sliderMoved(int position);

    void on_stay_duration_slider_sliderMoved(int position);

private:
    void start_simulation();
    QLabel** train_labels = new QLabel*[PLATFORM_SUM];
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
