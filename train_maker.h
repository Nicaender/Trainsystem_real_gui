#ifndef TRAIN_MAKER_H
#define TRAIN_MAKER_H

#include <QThread>
#include <QObject>
#include <gate_in_manager.h>
#include <windows.h>
#include <QMutex>

class Train_maker : public QThread
{
    Q_OBJECT
public:
    explicit Train_maker(QObject *parent = nullptr);
    void run();


    void setMultiplier(int newMultiplier);

    void setStay_duration(int newStay_duration);

    void setTrain_interval(int newTrain_interval);

signals:
    void notify_gate_in(Train*);

private:
    int multiplier = 1;
    int stay_duration = 15;
    int train_interval = -1;
};

#endif // TRAIN_MAKER_H
