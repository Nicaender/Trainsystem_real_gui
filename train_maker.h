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

    void setTrain_interval(int newTrain_interval);

    void set_multiplier(int new_multiplier);

signals:
    void notify_train_incoming(Train*);

public slots:
    void notified_incoming_train_full(bool);

private:
    int multiplier = 1;
    int train_interval = 5;
    bool halt = false;
};

#endif // TRAIN_MAKER_H
