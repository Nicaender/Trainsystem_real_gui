#ifndef INFRASTRUCTURE_H
#define INFRASTRUCTURE_H

#include <train.h>
#include <vector>

class Infrastructure
{
public:
    Infrastructure(int newType, int newY, int newX);

    int getType() const;

    int getX() const;

    int getY() const;

    bool getOccupied() const;
    void setOccupied(bool newOccupied);

    int getStay() const;

    void addLeft(Infrastructure *newLeft);
    const std::vector<Infrastructure *> &getLeft_list() const;

    void addRight(Infrastructure *newRight);
    const std::vector<Infrastructure *> &getRight_list() const;

    Train *getTrain() const;
    void setTrain(Train *newTrain);

    std::vector<int> *getMines() const;
    void setMines(const int &newMines);

private:
    enum {RAIL, PLATFORM, MINE};
    int type = -1, x = -1, y = -1;
    bool occupied = false;
    int stay = 0;
    std::vector<Infrastructure*> left_list;
    std::vector<Infrastructure*> right_list;
    Train* train = nullptr;
    std::vector <int>* mines;
};

#endif // INFRASTRUCTURE_H
