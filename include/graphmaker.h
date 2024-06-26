#ifndef GRAPHMAKER_H
#define GRAPHMAKER_H
#include "Sheetreader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <filesystem>

#include <graphDataStruct.h>


using namespace std;

class Graphmaker
{
public:
    // Constructor
    Graphmaker() {}

    void processDataForDay(string &directoryPath, int day, int Limit, graphDataStruct &graphData);

    void processDataForDay(string &directoryPath, int day, int Limit);
    // const vector<Linkutils>& getLinkUtilsData() const{return linkUtilsData;}
    // const vector<Traffic>& getTrafficData() const {return trafficData;}
    // const vector<Paths>& getPathsData() const {return pathsData;}
    // const vector<Router>& getRoutersData() const {return ma;}
    // const vector<Link>& getLinksData() const {return linksData;}

// private:
//     vector<Linkutils> linkUtilsData;
//     vector<Traffic> trafficData;
//     vector<Paths> pathsData;
//     vector<Router> routersData;
//     vector<Link> linksData;

};


#endif // GRAPHMAKER_H