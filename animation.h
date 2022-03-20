#ifndef ANIMATION_H
#define ANIMATION_H

#include <QThread>
#include <QObject>
#include <gate_in_manager.h>
#include <QMutex>

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
    void move_entering_on_canvas(int);
    void move_exiting_on_canvas(int);
    void destroy_train(int);
    void train_arrived_on_platform(int, Train*);

public slots:
    void start_animating(int, bool, Train*);

private:
    int duration_in = 0, duration_out = 0, pos_in = -1, pos_out = -1;
    bool entering = false;
    bool exiting = false;
    Train* train_in = nullptr;
    Train* train_out = nullptr;
    bool first_animating = false;
    bool currently_animating = false;
    int multiplier = 1;
};

#endif // ANIMATION_H
