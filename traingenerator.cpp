#include "traingenerator.h"

TrainGenerator::TrainGenerator()
{

}

/**
 * Trains will be generated (coming) every 20 mins
 * Train sleep duration in a platform is 75 mins
*/
void TrainGenerator::run()
{
    int sleep_duration = 75;
    int train_cycle = 20;
    while (true) {
        Train* newtrain = new Train(sleep_duration);
        emit TrainGenerated(newtrain);
        sleep(train_cycle);
    }
}
