#include "monitor.hpp"

Monitor::Monitor(int h){
    this -> h = h;
    sem_init(&(this->mutex), 0, 1);
}
void Monitor::crossCars(int p){
    sem_wait(&mutex);
    // cout << "I'm here in thread" << endl;
    calcPolution(p);
    sem_post(&mutex);
}
double Monitor::calcPolution(int p) {
    double ans;
    for (int k = 0;k < RANGE; k++){
        ans += (double)(k) / (double)(BIGNUM * p * h);
    }
}
