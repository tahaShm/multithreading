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
int Car::getP(){
    return p;
}
string Car::getSource(){
    if (position >= carPath.edges.size())
        return "-";
    else
        return carPath.edges[position].source;
}
string Car::getDestination(){
    if (position >= carPath.edges.size())
        return "-";
    else
        return carPath.edges[position].destination;
}
int Car::goAhead(){
    position++;
    milliseconds newTime = duration_cast < milliseconds > (
        system_clock::now().time_since_epoch()
    );
    enterTimes.push_back(newTime);
    finishTimes.push_back(newTime);
    if (position >= carPath.edges.size())
        return -1;
    return 1;
}
int Car::getPosition(){
    return position;
}
int Car::getPathlength(){
    return carPath.edges.size();
}