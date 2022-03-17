#ifndef DATABASE_H
#define DATABASE_H

#include <train.h>
#include <queue>
#include <QDebug>
#include <QMutex>

#define PLATFORM_SUM 4
#define GATE_IN_DURATION 5

static int train_interval = 5;
static Train* platforms[PLATFORM_SUM];
static std::queue<Train*> incoming_train;
static std::queue<Train*> outcoming_train;
static QMutex m;

class Database
{
public:
    Database(int interval);

};

#endif // DATABASE_H
