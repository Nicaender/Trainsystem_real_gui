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

signals:
    void train_in_entrance(int,Train*);
    void train_into_platform();
    void train_exiting_platform();
    void notify_animation(int, bool); // kalau true, suruh animasi masuk, false = animasi keluar
    void notify_canvas_to_destroy_train(int);

public slots:

    void notified_to_remove_train(int pos);
    void on_new_train_notified(Train*);
    void path_clear(bool);

private:
    void notify_train_into_platform(int pos);
    void notify_train_exiting_platform(int pos);

    int train_in_cooldown = 0;
    int train_out_cooldown = 0;
    int check_free_platform();
    bool pathway_entering = true;
};

#endif // GATE_IN_MANAGER_H
