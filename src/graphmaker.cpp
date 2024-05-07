#include "graphmaker.h"
#include "sheetreader.h"
#include "linkutils.h"
#include "traffic.h"
#include "path.h"
#include "router.h"
#include "link.h"
#include <iostream>
#include <vector>

using namespace std;

void Graphmaker::processDataForDay(string &directoryPath, int day, int Limit)
{
    SheetReader Readmaster(Limit);

    // vector<int> intData;
    // Readmaster.readData("hello", intData, false);

    cout << "Processing linkutils" << endl;
    // Read link utilities data
    string linkUtilsFileName = directoryPath + "/link-util-day" + to_string(day) + ".csv";
    Readmaster.readData(linkUtilsFileName, linkUtilsData, false);
    mainWindow.simulateProcessingOne();
    cout << "Processing flowfile" << endl;
    // Read flows data
    string flowsFileName = directoryPath + "/flow-traffic-day" + to_string(day) + ".csv";
    Readmaster.readData(flowsFileName, trafficData, false);
    mainWindow.simulateProcessingOne();
    cout << "Processing pathfile" << endl;
    // Read paths data
    string pathsFileName = directoryPath + "/flow-paths-day" + to_string(day) + ".csv";
    Readmaster.readData(pathsFileName, pathsData, false);
    mainWindow.simulateProcessingOne();
    cout << "Processing routerdata" << endl;
    // Read routers data
    string routersFileName = directoryPath + "/routers.csv";
    Readmaster.readData(routersFileName, routersData, false);
    mainWindow.simulateProcessingOne();
    cout << "Processing links" << endl;
    // Read links data
    string linksFileName = directoryPath + "/links.csv";
    Readmaster.readData(linksFileName, linksData, false);
    mainWindow.simulateProcessingOne();

    cout << "Done" << endl;
    
    int userInput;
    cin >> userInput;
};

