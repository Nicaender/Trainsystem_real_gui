#ifndef TRAIN_H
#define TRAIN_H


class Train
{
public:
    Train(int id, int stop);

    void stop_reduction();

    int getId() const;

    void add_duration(int duration);

    int getStop_duration() const;

private:
    int id;
    int stop_duration;
};

#endif // TRAIN_H
