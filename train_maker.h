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

    void setTrain_interval(int newTrain_interval);

signals:
    void notify_train_incoming(Train*);

public slots:
    void notified_incoming_train_full(bool);

private:
    int multiplier = 5;
    int train_interval = 5;
    bool halt = false;
};

#endif // TRAIN_MAKER_H
