#ifndef GATE_IN_MANAGER_H
#define GATE_IN_MANAGER_H

#include <QThread>
#include <QObject>
#include <infrastructure.h>
#include <queue>
#include <stack>
#include <QMutex>
#include <QDebug>
#include <utility>

#define MAX_Y 15
#define MAX_X 39
#define PLATFORM_SUM 8

class Gate_In_Manager : public QThread
{
    Q_OBJECT
public:
    explicit Gate_In_Manager(QObject *parent = nullptr);
    void run();

//    void setMultiplier(int newMultiplier);

//    void setGate_out_cooldown(int newGate_out_cooldown);

signals:
    void notify_train_label_attach(Train*);
    void notify_put_train_on_canvas(Train*);
    void notify_train_depart(std::deque <Infrastructure*>*);
    void notify_train_label_detach(Train*);
//    void notify_animation(int, bool, Train*); // kalau true, suruh animasi masuk, false = animasi keluar
//    void update_cooldown_canvas(int);
//    void time_update(int);
//    void change_color_to_red(int);
//    void update_in_waiting_list(QString);

public slots:
    void notified_train_arrived(Infrastructure*);
    void notified_train_incoming(Train*);
//    void notified_to_remove_train(int);
//    void on_new_train_notified(Train*);
//    void set_train_on_platform(int, Train*);

private:
    void put_train_at_entrance();
    void train_depart(Infrastructure *start);
//    void notify_train_exiting_platform(int pos, Train*);
    std::deque<Infrastructure*> *navigate(Infrastructure* start_pos, Infrastructure* end_pos, bool direction);

    Infrastructure *check_free_platform();
    bool gate_in_ready = true, gate_out_ready = true, pathway = true;
    int multiplier = 5;
    int timer = 0;

    Infrastructure* map[MAX_Y][MAX_X];
    Infrastructure* in = map[0][MAX_X-1];
    Infrastructure* out = map[2][MAX_X-1];
    Infrastructure* platform_list[PLATFORM_SUM];
    std::vector<Infrastructure*> mine_group[3];
    enum {RAIL, PLATFORM, MINE};
    enum {ENTERING, EXITING};

    std::deque<Train*> incoming_train;
    std::deque<Infrastructure*> outcoming_train_pathway;
    std::deque<Infrastructure*> outcoming_train_gate;

    // Help attributes
    std::deque<int> fill_left = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,-1,9,11,-1,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,-1,4,6,13,17,-1,1,2,3,4,5,6,7,14,18,19,20,21,-1,6,8,15,19,-1,
                                 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,-1,8,10,17,-1,9,10,11,12,13,14,15,16,17,18,19,20,21,-1,10,12,15,-1,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,-1,
                                 12,14,16,-1,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,-1,14,16,-1,15,16,17,18,19,20,21};
    std::deque<int> fill_right = {23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,-1,33,34,36,-1,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,-1,31,34,-1,23,24,25,26,27,28,29,30,33,-1,29,32,-1,
                                  23,24,25,26,27,28,31,-1,27,30,-1,23,24,25,26,29,-1,25,28,-1,23,24,25,26,27,-1,26,-1,23,24,25,-1,24,-1,23};
    std::pair<Infrastructure *, int> *check_free_mine();

    // Initialization
    void left_initialization();
    void left_hand_initialization();
    void right_initialization();
    void right_hand_initialization();
    void mine_initialization();
    void mine_hand_initialization();
    void platform_initialization();
    void platform_hand_initialization();
};

#endif // GATE_IN_MANAGER_H
