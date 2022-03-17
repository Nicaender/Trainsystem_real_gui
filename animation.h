#ifndef ANIMATION_H
#define ANIMATION_H

#include <QThread>
#include <QObject>
#include <database.h>

class Animation : public QThread
{
    Q_OBJECT
public:
    explicit Animation(QObject *parent = nullptr);
    void run();

signals:
    void move_entering_on_canvas(int);
    void move_exiting_on_canvas(int);
    void destroy_train(int);

public slots:
    void start_animating(int, bool);

private:
    int duration_in = 0, duration_out = 0, pos_in = -1, pos_out = -1;
    bool entering = false;
    bool exiting = false;
};

#endif // ANIMATION_H
