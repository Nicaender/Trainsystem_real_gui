#ifndef ANIMATION_H
#define ANIMATION_H

#include <QThread>
#include <QObject>
#include <gate_in_manager.h>
#include <QMutex>
#include <deque>

#define GATE_IN_DURATION 9 // kalau mau pakai smoother animation, di kali dengan speed yang diinginkan
#define GATE_OUT_DURATION 10 // kalau mau pakai smoother animation, di kali dengan speed yang diinginkan

class Animation : public QThread
{
    Q_OBJECT
public:
    explicit Animation(QObject *parent = nullptr);
    void run();

    void set_multiplier(int new_multiplier);

    void set_block_per_second(int new_block_per_second);

signals:
    void notify_train_arrived(Train*,Infrastructure*, Infrastructure*);
    void notify_move_train(Train*,Infrastructure*);
    void notify_color(int,int,int);

public slots:
    void notified_train_depart(std::deque <Infrastructure*>*);

private:
    std::vector<std::pair<std::pair<std::deque<Infrastructure *>, std::deque<Infrastructure *>>, Train*>> path_list; // path, full path, train
    int multiplier = 1;
    int block_per_second = 1;
};

#endif // ANIMATION_H
