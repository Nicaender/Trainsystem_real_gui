#ifndef GATE_IN_MANAGER_H
#define GATE_IN_MANAGER_H

#include <QThread>
#include <QObject>
#include <train.h>
#include <queue>
#include <QMutex>
#include <QDebug>

#define PLATFORM_SUM 5

class Gate_In_Manager : public QThread
{
    Q_OBJECT
public:
    explicit Gate_In_Manager(QObject *parent = nullptr);
    void run();

    void setMultiplier(int newMultiplier);

    void setGate_out_cooldown(int newGate_out_cooldown);

signals:
    void train_in_entrance(int,Train*);
    void notify_animation(int, bool, Train*); // kalau true, suruh animasi masuk, false = animasi keluar
    void update_cooldown_canvas(int);
    void time_update(int);
    void change_color_to_red(int);
    void update_in_waiting_list(QString);

public slots:
    void notified_to_remove_train(int);
    void on_new_train_notified(Train*);
    void set_train_on_platform(int, Train*);

private:
    void notify_train_into_platform(int pos);
    void notify_train_exiting_platform(int pos, Train*);

    int gate_out_cooldown = -1;
    int train_out_cooldown = -1;
    int check_free_platform();
    bool pathway_entering = true, gate_in_ready = true, gate_out_ready = true;
    int multiplier = 1;
    int timer = 0;

    Train* platforms[PLATFORM_SUM];
    std::deque<Train*> incoming_train;
    std::deque<int> outcoming_train_pos;
};

#endif // GATE_IN_MANAGER_H
