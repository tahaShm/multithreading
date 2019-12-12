#ifndef MONITOR_HPP
#define MONITOR_HPP

#include "include.hpp"
#include "classes.hpp"

using namespace std;
using namespace std::chrono;


class Monitor {
private : 
    sem_t mutex;
    int h;
public :
    Monitor(int h);
    void crossCars(int p);
    double calcPolution(int p);
};

#endif