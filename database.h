#ifndef DATABASE_H
#define DATABASE_H

#include <train.h>
#include <queue>
#include <QDebug>
#include <QMutex>

#define PLATFORM_SUM 5
#define GATE_IN_DURATION 9
#define GATE_OUT_DURATION 9
#define GATE_OUT_OUT 20

static int train_interval = 5;
static Train* platforms[PLATFORM_SUM];
static std::queue<Train*> incoming_train;
static std::deque<int> outcoming_train_pos;
static QMutex m;

class Database
{
public:
    Database(int interval);

};

#endif // DATABASE_H
