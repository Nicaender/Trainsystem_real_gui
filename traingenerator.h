#ifndef TRAINGENERATOR_H
#define TRAINGENERATOR_H

#include <QThread>
#include <QObject>
#include "Train.h"

class TrainGenerator : public QThread
{
    Q_OBJECT
public:
    TrainGenerator();
    void run();

signals:
    void TrainGenerated(Train*);
};

#endif // TRAINGENERATOR_H
