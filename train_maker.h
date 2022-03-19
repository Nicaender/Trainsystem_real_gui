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
    int trail_interval = -1;

signals:
    void notify_gate_in(Train*);

private:
    int multiplier = 10;
};

#endif // TRAIN_MAKER_H
