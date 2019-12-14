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
					Car newCar = Car(allpaths[allpaths.size()-1], globalCarId, allpaths.size()-1);
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
double calculateTotalEmission(){
	int carsSize = allCars.size();
	double total = 0.0;
	for (int i = 0; i< carsSize; i++)
		total += allCars[i].getCurrentEmission();
	return total;

}
string contentOfCarMoves(int index, int pathId) {
	string content = "";
	string seperator = ", ";
	int iterSize = allCars[index].getPathlength();
	vector <double> emissions = allCars[index].getEmissions();
	vector <double> totalEmissions = allCars[index].getTotalEmissions();
	vector <milliseconds> enterTimes = allCars[index].getEnterTimes();
	vector <milliseconds> finishTimes = allCars[index].getFinishTimes();
	double totalEmission = calculateTotalEmission();
	for (int i = 0; i < iterSize; i++){
		content += allpaths[pathId].edges[i].source + seperator + to_string(enterTimes[i].count()) + seperator + allpaths[pathId].edges[i].destination + seperator + to_string(finishTimes[i].count()) + seperator + to_string((int)emissions[i]) + seperator + to_string((int)totalEmissions[i]) + "\n";
	}
	return content;
}
void makeCorrespondingFile(int index){
	int pathId = allCars[index].getPathId();
	string route = to_string(pathId) + "-" + to_string(index);
	string content = contentOfCarMoves(index, pathId);
	int fd = open(route.c_str(), O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	close(fd);
	fd = open(route.c_str(), O_WRONLY);
    int writed = write(fd,content.c_str(),content.size());
    close(fd);
}
void threadFunction(int index, int p){
	while(true){
		string s = allCars[index].getSource();
		string d = allCars[index].getDestination();
		int id = findEdgeIndex(s, d);
		if (id != -1){
			milliseconds enterTime = duration_cast < milliseconds > (
				system_clock::now().time_since_epoch()
			);
			allCars[index].addEnterTime(enterTime);

			double newEmission = monitors[id].crossCars(p);

			double totalEmission = calculateTotalEmission();
			allCars[index].setNewEmission(newEmission, totalEmission);

			milliseconds finishTime = duration_cast < milliseconds > (
				system_clock::now().time_since_epoch()
			);
			allCars[index].addFinishTime(finishTime);
		}
		else
			break;
		// cout << " " << endl;
		// cout << "car index : " << index << "  source : " << s << "  destination : " << d << "  finish_time : " << nowTime2.count() << endl;
		// cout << " " << endl;
		allCars[index].goAhead();
	}
	makeCorrespondingFile(index);
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
void printResults(){
	int carsSize = allCars.size();
	for(int i = 0; i < carsSize; i++) {
		cout << "car id : " << i << endl;
		cout << "  position : " << allCars[i].getPosition() << endl;
		cout << "  current emission : " << allCars[i].getCurrentEmission() << endl;
		cout << "  emissions : " << endl;
		allCars[i].printEmissions();
		cout << "  times : " << endl;
		allCars[i].printTimes();
		cout << endl << endl << endl;
	}
}
int main() {
	getInputs();
	// printStuff(allEdges, allpaths, allCars);
	makeMonitorsAndThreadsAndDoProcess();
	// printResults();
}