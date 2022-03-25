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
    void notify_train_arrived(Train*,Infrastructure*, Infrastructure*);
    void notify_move_train(Train*,Infrastructure*);

public slots:
    void notified_train_depart(std::deque <Infrastructure*>*);

private:
    std::vector<std::pair<std::pair<std::deque<Infrastructure *>, std::deque<Infrastructure *>>, Train*>> path_list; // path, full path, train
    int multiplier = 5;
};

#endif // ANIMATION_H
