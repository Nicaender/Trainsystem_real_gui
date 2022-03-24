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

    void setMultiplier(int newMultiplier);

signals:
    void notify_train_arrived(Infrastructure*);
    void notify_move_train(Infrastructure*);

public slots:
    void notified_train_depart(std::deque <Infrastructure*>*);

private:
    std::vector<std::deque<Infrastructure*>> path_list;
    std::vector<std::deque<Infrastructure*>> copy_path_list;
    int multiplier = 5;
};

#endif // ANIMATION_H
