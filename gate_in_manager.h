#ifndef GATE_IN_MANAGER_H
#define GATE_IN_MANAGER_H

#include <QThread>
#include <QObject>
#include <database.h>

class Gate_In_Manager : public QThread
{
    Q_OBJECT
public:
    explicit Gate_In_Manager(QObject *parent = nullptr);
    void run();

    void add_train();

signals:
    void train_coming(int,Train*);

public slots:
    void on_new_train_notified(Train*);
};

#endif // GATE_IN_MANAGER_H
