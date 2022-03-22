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

private:
    int id;
    int stop_duration;
    bool out_waiting_list = false;
};

#endif // TRAIN_H
