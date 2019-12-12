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
    double curPollution;
    vector <milliseconds> enterTimes;
    vector <milliseconds> finishTimes;
    int carId;
public :
    Car(Path path, int id);
    void printInfo();
    int getP();
    string getSource();
    string getDestination();
    int goAhead();
    void addPollution(double newPollution);
    int getPosition();
    int getPathlength();
};

#endif