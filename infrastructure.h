#ifndef INFRASTRUCTURE_H
#define INFRASTRUCTURE_H

#include <train.h>
#include <vector>

class Infrastructure
{
public:
    Infrastructure(int new_type);
    int getType() const;

    bool getIs_occupied() const;
    void setIs_occupied(bool newIs_occupied);

    int getStay_duration() const;

    void setLeft_list(Infrastructure *&newLeft);
    const std::vector<Infrastructure *> &getLeft_list() const;

    void setRight_list(Infrastructure *&newRight);
    const std::vector<Infrastructure *> &getRight_list() const;

    Train *getCurrent_train() const;
    void setCurrent_train(Train *newCurrent_train);

private:
    enum {RAIL, PLATFORM, MINE};
    int type = -1;
    bool is_occupied = false;
    int stay_duration = -1;
    std::vector<Infrastructure*> left_list;
    std::vector<Infrastructure*> right_list;
    Train* current_train = nullptr;
};

#endif // INFRASTRUCTURE_H
