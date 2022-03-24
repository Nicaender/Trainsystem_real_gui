#ifndef TRAIN_H
#define TRAIN_H


class Train
{
public:
    Train(int id);

    void stop_reduction();

    int getId() const;

    void add_duration(int duration);

    int getStop_duration() const;

    bool getOut_waiting_list() const;
    void setOut_waiting_list(bool newOut_waiting_list);

    bool getDirection() const;
    void setDirection(bool newDirection);

    int getBefore_x() const;
    void setBefore_x(int newBefore_x);

    int getBefore_y() const;
    void setBefore_y(int newBefore_y);

private:
    enum {ENTERING, EXITING};
    int id;
    int stop_duration = 0;
    bool out_waiting_list = false;
    bool direction = ENTERING;
    int before_x = -1;
    int before_y = -1;
};

#endif // TRAIN_H
