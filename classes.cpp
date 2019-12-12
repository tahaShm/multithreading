#include "classes.hpp"
Car::Car(Path path, int id){
    srand (time(NULL));
    int p = rand() % 10 + 1;
    this -> p = p;
    this -> carPath = path;
    this -> position = 0;
    this -> curPollution = 0.0;
    milliseconds enterTime = duration_cast < milliseconds > (
        system_clock::now().time_since_epoch()
    );
    enterTimes.push_back(enterTime);
}
void Car::printInfo(){
    cout << "   p : " << p << endl;
    cout << "   carPath[0] : " << carPath.edges[0].source << "  " << carPath.edges[0].destination << endl;
    cout << "   position : " << position << endl;
    cout << "   curPollution : " << curPollution << endl;
    cout << "   enterTime : " << enterTimes[0].count() << endl;
}