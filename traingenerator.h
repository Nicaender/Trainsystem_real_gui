#ifndef TRAINGENERATOR_H
#define TRAINGENERATOR_H

#include <QThread>
#include "Train.h"

class TrainGenerator : public QThread
{
    Q_OBJECT
public:
    explicit TrainGenerator(QObject* parent = 0);
    void run();

signals:
    void TrainGenerated(Train*);
};

#endif // TRAINGENERATOR_H
