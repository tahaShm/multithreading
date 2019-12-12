#include "monitor.hpp"
#include "classes.hpp"

using namespace std;

vector <Monitor> monitors;

vector <Edge> allEdges;
vector <Path> allpaths;
vector <Car> allCars;
int globalPathId = 0;
int globalCarId = 0;


Edge findEdge(string s, string d){
	Edge wantedEdge;
	int edgesSize = allEdges.size();
	for (int i = 0; i < edgesSize; i++){
		if (allEdges[i].source == s && allEdges[i].destination == d){
			wantedEdge = allEdges[i];
			break;
		}
	}
	return wantedEdge;
}
int findEdgeIndex(string s, string d){
	int index = -1;
	int edgesSize = allEdges.size();
	for (int i = 0; i < edgesSize; i++){
		if (allEdges[i].source == s && allEdges[i].destination == d){
			index = i;
			break;
		}
	}
	return index;
}
void getInputs() {
	fstream fin; 
    fin.open("./input.txt", ios::in);
    vector<string> row; 
    bool sharpSignSeen = false;
    int lineNum = 0;
    string line; 
    while (fin >> line) {
    	if (sharpSignSeen == false){
	    	if (line != "#"){
	    		stringstream ss(line);
				string token;
				int index = 0;
				Edge newEdge;
				while (getline(ss,token, '-'))
				{
					if (index == 0)
						newEdge.source = token;
					else if (index == 1)
						newEdge.destination = token;
					else if (index == 2) 
						newEdge.h = stoi(token);
					index++;
				}
				allEdges.push_back(newEdge);	
	    	}
    		else 
    			sharpSignSeen = true;
	    }
	    else {
	    	if (lineNum == 0){
	    		stringstream ss(line);
				string token;
				int index = 0;
				Path newPath;
				vector<string> allNodes;
				vector<Edge> pathEdges;
				while (getline(ss,token, '-'))
				{
					Edge currentEdge;
					if (index >= 1) {
						string token1 = allNodes[allNodes.size()-1];
						string token2 = token;
						Edge currentEdge = findEdge(token1, token2);
						pathEdges.push_back(currentEdge);
					}
					allNodes.push_back(token);
					index++;
				}
				newPath.edges = pathEdges;
				allpaths.push_back(newPath);
	    	}
	    	else if (lineNum == 1) {
	    		int numberOfCars = stoi(line);
	    		allpaths[allpaths.size()-1].numOfCars = numberOfCars;
	    		allpaths[allpaths.size()-1].pathId = globalPathId;
	    		globalPathId++;
				for (int i = 0; i < numberOfCars; i++){
					Car newCar = Car(allpaths[allpaths.size()-1], globalCarId);
					allCars.push_back(newCar);
					globalCarId++;
				}
	    	}

	    	lineNum = 1 - lineNum;
	    }
	}
    fin.close();
}

void printStuff(){
	int EdgesSize = allEdges.size();
	int PathsSize = allpaths.size();
	int carsSize = allCars.size();
	for (int i = 0;i < EdgesSize;i++) {
		cout << "edge" << i << "   :   source : " << allEdges[i].source << "   : destination : " << allEdges[i].destination << endl;
	}
	cout << endl;
	for (int i = 0;i < PathsSize; i++){
		cout << endl << "path" << i << endl;
		int pathEdgesSize = allpaths[i].edges.size();
		for (int j = 0;j < pathEdgesSize; j++){
			cout << "	edge" << j << "   :   source : " << allpaths[i].edges[j].source << "   : destination : " << allpaths[i].edges[j].destination << endl;
		}
		cout <<"	path_cars : " << allpaths[i].numOfCars << endl;
	}
	cout << "car size : " << carsSize << endl;
	for (int i = 0;i < carsSize; i++){
		allCars[i].printInfo();
	}
}
void threadFunction(int index, int p){
	string s = allCars[index].getSource();
	string d = allCars[index].getDestination();
	// if (allCars[id].)
	while(true){
		s = allCars[index].getSource();
		d = allCars[index].getDestination();
		int id = findEdgeIndex(s, d);
		cout << s << " *** " << d << endl;
		if (id != -1){
			monitors[id].crossCars(p);
		}
		else{
			cout << "end of car!" << endl;
			break;
		}
		int go = allCars[index].goAhead();
		// if (go == -1) {
		// 	cout << "end of car!" << endl;
		// 	break;
		// }

		// cout << "path length : " << allCars[index].getPathlength() << "car id : " << index << "  , position : " << allCars[index].getPosition() << endl;
	}
}

void makeMonitorsAndThreadsAndDoProcess(){
	int carsSize = allCars.size();
	int edgesSize = allEdges.size();
	for (int i = 0; i < edgesSize; i++) {
		Monitor newMonitor(allEdges[i].h); //index of "allEdges" and "monitors" are the same.
		monitors.push_back(newMonitor);
	}
	// thread t (&threadFunction, 1);
	// t.join();
	thread allThreads[100];
	for (int i = 0; i < carsSize; i++) {
		allThreads[i] = thread (&threadFunction, i, allCars[i].getP());
	}
	for (int i = 0; i < carsSize; i++)
		allThreads[i].join();

}
int main() {
	getInputs();
	// printStuff(allEdges, allpaths, allCars);
	makeMonitorsAndThreadsAndDoProcess();
}