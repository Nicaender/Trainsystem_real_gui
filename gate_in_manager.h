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
    ~Gate_In_Manager();
    void run();

    void map_coloring();

    void set_multiplier(int new_multiplier);

    void change_platform_duration(bool platform, int duration);

    void set_pause(bool new_pause);

    bool get_pause() const;

signals:
    void notify_train_label_attach(Train*);
    void notify_put_train_on_canvas(Train*);
    void notify_train_depart(std::deque <Infrastructure*>*);
    void notify_train_label_detach(Train*);
    void notify_color(int,int,int);
    void notify_change_color(Train*);
    void notify_incoming_train_full(bool);
    void notify_update_incoming_train(QString);
    void notify_path_color(int, int);
    void notify_update_current_time(int);

public slots:
    void notified_train_arrived(Train*,Infrastructure*, Infrastructure*);
    void notified_train_incoming(Train*);

private:
    void put_train_at_entrance();
    bool train_depart(Infrastructure *start);
    std::deque<Infrastructure*> *navigate(Infrastructure* start_pos, Infrastructure* end_pos, bool direction);

    Infrastructure *check_free_platform();
    bool gate_in_ready = true, gate_out_ready = true, incoming_train_full = false, pause = false;
    int multiplier = 1;
    int timer = 0;

    Infrastructure* map[MAX_Y][MAX_X];
    Infrastructure* in = map[0][MAX_X-1];
    Infrastructure* out = map[2][MAX_X-1];
    Infrastructure* platform_list[PLATFORM_SUM];
    std::vector<Infrastructure*> mine_group[3];
    enum {RAIL, PLATFORM, MINE};
    enum {ENTERING, EXITING};

    std::deque<Train*> incoming_train;
    std::vector<Infrastructure*> outcoming_train_pathway;
    std::deque<Infrastructure*> outcoming_train_gate;

    // Help attributes
    std::deque<int> fill_left = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,-1,9,11,-1,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,-1,4,6,13,17,-1,1,2,3,4,5,6,7,14,18,19,20,21,-1,6,8,15,19,-1,
                                 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,-1,8,10,17,-1,9,10,11,12,13,14,15,16,17,18,19,20,21,-1,10,12,15,-1,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,-1,
                                 12,14,16,-1,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,-1,14,16,-1,15,16,17,18,19,20,21};
    std::deque<int> fill_right = {23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,-1,32,34,36,-1,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,-1,31,34,-1,23,24,25,26,27,28,29,30,33,-1,29,32,-1,
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
