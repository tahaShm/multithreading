#ifndef CLASSES_HPP
#define CLASSES_HPP

#include "include.hpp"
using namespace std;
using namespace std::chrono;

struct Edge
{
    string source;
    string destination;
    int h;
};

struct Path
{
    vector <Edge> edges;
    int numOfCars;
    int pathId;
};

class Car {
private : 
    int p;
    Path carPath;
    int position;
    double curEmission;
    vector <double> emissions;
    vector <milliseconds> enterTimes;
    vector <milliseconds> finishTimes;
    int pathId;
    int carId;
public :
    Car(Path path, int id, int pathId);
    void printInfo();
    int getP();
    string getSource();
    string getDestination();
    int goAhead();
    void addPollution(double newPollution);
    int getPosition();
    int getPathlength();
    void addEnterTime(milliseconds enterTime);
    void addFinishTime(milliseconds finishTime);
    void setNewEmission(double newEmission);
    double getCurrentEmission();
    void printEmissions();
    void printTimes();
    int getPathId();
};

#endif