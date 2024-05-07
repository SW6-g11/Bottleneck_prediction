#include "graphmaker.h"
#include "sheetreader.h"
#include "linkutils.h"
#include "traffic.h"
#include "path.h"
#include "router.h"
#include "link.h"
#include "graphDataStruct.h"
#include <iostream>
#include <vector>


using namespace std;

void Graphmaker::processDataForDay(string &directoryPath, int day, int Limit, graphDataStruct &graphdata)
{
    SheetReader Readmaster(Limit);

    // vector<Linkutils> linkUtilsData;
    // vector<Traffic> trafficData;
    // vector<Paths> pathsData;
    // vector<Router> routersData;
    // vector<Link> linksData;


    // vector<int> intData;
    // Readmaster.readType("hello", intData, false);

    // Read link utilities data
    cout << "Processing linkutils" << endl;
    string linkUtilsFileName = directoryPath + "/link-util-day" + to_string(day) + ".csv";

    Readmaster.readData(linkUtilsFileName, graphdata.linkUtilsData, false);


    mainWindow.simulateProcessingOne();
    // Read flows data
    cout << "Processing flowfile" << endl;
    string flowsFileName = directoryPath + "/flow-traffic-day" + to_string(day) + ".csv";

    Readmaster.readData(flowsFileName, graphdata.trafficData, false);


    mainWindow.simulateProcessingOne();
    // Read paths data
    cout << "Processing pathfile" << endl;
    string pathsFileName = directoryPath + "/flow-paths-day" + to_string(day) + ".csv";

    Readmaster.readData(pathsFileName, graphdata.pathsData, false);


    mainWindow.simulateProcessingOne();

    // Read routers data
    cout << "Processing routerdata" << endl;
    string routersFileName = directoryPath + "/routers.csv";

    Readmaster.readData(routersFileName, graphdata.routersData, true);


    mainWindow.simulateProcessingOne();


    // Read links data
    cout << "Processing links" << endl;
    string linksFileName = directoryPath + "/links.csv";

    Readmaster.readData(linksFileName, graphdata.linksData, true);




    mainWindow.simulateProcessingOne();

};

