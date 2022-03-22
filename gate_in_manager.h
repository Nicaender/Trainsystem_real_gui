#ifndef GATE_IN_MANAGER_H
#define GATE_IN_MANAGER_H

#include <QThread>
#include <QObject>
#include <infrastructure.h>
#include <queue>
#include <QMutex>
#include <QDebug>

#define MAX_Y 15
#define MAX_X 39
#define PLATFORM_SUM 5

class Gate_In_Manager : public QThread
{
    Q_OBJECT
public:
    explicit Gate_In_Manager(QObject *parent = nullptr);
    void run();

    void setMultiplier(int newMultiplier);

    void setGate_out_cooldown(int newGate_out_cooldown);

    enum {RAIL, PLATFORM, MINE};

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

    Infrastructure* map[MAX_Y][MAX_X];
    Infrastructure* in = map[0][MAX_X-1];
    Infrastructure* out = map[2][MAX_X-1];
    std::vector<Infrastructure*> Mine_group[3];

    std::deque<Train*> incoming_train;
    std::deque<int> outcoming_train_pos;

    void right_initialization();
    void mine_initialization();
};

#endif // GATE_IN_MANAGER_H
