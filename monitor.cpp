#include "monitor.hpp"

Monitor::Monitor(int h){
    this -> h = h;
    sem_init(&(this->mutex), 0, 1);
}
double Monitor::crossCars(int p){
    sem_wait(&mutex);
    double emission = calcPolution(p);
    sem_post(&mutex);
    return emission;
}
double Monitor::calcPolution(int p) {
    double ans;
    for (int k = 0;k < RANGE; k++){
        ans += (double)(k) / (double)(BIGNUM * p * h);
    }
}
