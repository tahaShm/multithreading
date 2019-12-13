#include "classes.hpp"
Car::Car(Path path, int id, int pathId){
    srand (time(NULL));
    int p = rand() % 10 + 1;
    this -> p = p;
    this -> carPath = path;
    this -> position = 0;
    this -> curEmission = 0.0;
    this -> carId = id;
    this -> pathId = pathId;
}
void Car::printInfo(){
    cout << "   p : " << p << endl;
    cout << "   carPath[0] : " << carPath.edges[0].source << "  " << carPath.edges[0].destination << endl;
    cout << "   position : " << position << endl;
    cout << "   curEmission : " << curEmission << endl;
    // cout << "   enterTime : " << enterTimes[0].count() << endl;
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
void Car::addEnterTime(milliseconds enterTime){
    enterTimes.push_back(enterTime);
}
void Car::addFinishTime(milliseconds finishTime){
    finishTimes.push_back(finishTime);
}
void Car::setNewEmission(double newEmission, double newTotalEmission){
    emissions.push_back(newEmission);
    totalEmissions.push_back(newTotalEmission + newEmission);
    curEmission += newEmission;
}
double Car::getCurrentEmission(){
    return curEmission;
}
void Car::printEmissions(){
    for (int i = 0; i < emissions.size(); i++){
        cout << "   " <<  i + 1 << " : " << emissions[i] << endl;
    }
}
void Car::printTimes(){
    // cout << "time sizes : " <<  enterTimes.size() << "   " <<  finishTimes.size() << endl;
    for (int i = 0; i < enterTimes.size(); i++){
        cout << "   " <<  i + 1 << " : start_time : " << enterTimes[i].count() << " : finish_time : " << finishTimes[i].count() << endl;
    }
}
int Car::getPathId(){
    return pathId;
}
vector <double> Car::getEmissions(){
    return emissions;
}
vector <double> Car::getTotalEmissions(){
    return totalEmissions;
}
vector <milliseconds> Car::getEnterTimes(){
    return enterTimes;
}
vector <milliseconds> Car::getFinishTimes(){
    return finishTimes;
}