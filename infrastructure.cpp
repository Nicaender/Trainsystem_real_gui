#include "infrastructure.h"

Infrastructure::Infrastructure(int newType, int newY, int newX)
{  
    this->type = newType;
    this->y = newY;
    this->x = newX;
    if(this->type == PLATFORM)
        this->stay = 10;
    else if(this->type == MINE)
        this->stay = 5;

    this->mines = new std::vector <int>;
}

int Infrastructure::getType() const
{
    return type;
}

int Infrastructure::getX() const
{
    return x;
}

int Infrastructure::getY() const
{
    return y;
}

bool Infrastructure::getOccupied() const
{
    return occupied;
}

void Infrastructure::setOccupied(bool newOccupied)
{
    occupied = newOccupied;
}

int Infrastructure::getStay() const
{
    return stay;
}

void Infrastructure::addLeft(Infrastructure *newLeft)
{
    this->left_list.push_back(newLeft);
}

const std::vector<Infrastructure *> &Infrastructure::getLeft_list() const
{
    return left_list;
}

void Infrastructure::addRight(Infrastructure *newRight)
{
    this->right_list.push_back(newRight);
}

const std::vector<Infrastructure *> &Infrastructure::getRight_list() const
{
    return right_list;
}

Train *Infrastructure::getTrain() const
{
    return this->train;
}

void Infrastructure::setTrain(Train *newTrain)
{
    train = newTrain;
}

std::vector<int> *Infrastructure::getMines() const
{
    return mines;
}

void Infrastructure::setMines(const int &newMines)
{
    this->mines->push_back(newMines);
}
