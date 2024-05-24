#include "graphmaker.h"
#include "Sheetreader.h"
#include "Linkutils.h"
#include "Traffic.h"
#include "Path.h"
#include "Router.h"
#include "Link.h"
#include "graphDataStruct.h"
#include <iostream>
#include <vector>
#include <mainwindow.h>

using namespace std;

void Graphmaker::processDataForDay(string &directoryPath, int day, int Limit, graphDataStruct &graphdata)
{
    SheetReader Readmaster(Limit);
    MainWindow &mainWindow = MainWindow::getInstance();

    string linkUtilsFileName = directoryPath + "/link-util-day" + to_string(day) + ".csv";
    Readmaster.readData(linkUtilsFileName, graphdata.linkUtilsData, false);
    mainWindow.simulateProcessingOne();

    string flowsFileName = directoryPath + "/flow-traffic-day" + to_string(day) + ".csv";
    Readmaster.readData(flowsFileName, graphdata.trafficData, false);
    mainWindow.simulateProcessingOne();

    string pathsFileName = directoryPath + "/flow-paths-day" + to_string(day) + ".csv";
    Readmaster.readData(pathsFileName, graphdata.pathsData, false);
    mainWindow.simulateProcessingOne();

    string routersFileName = directoryPath + "/routers.csv";
    Readmaster.readData(routersFileName, graphdata.MappedRouterVector, false);
    mainWindow.simulateProcessingOne();

    string linksFileName = directoryPath + "/links.csv";
    Readmaster.readData(linksFileName, graphdata.Augmentedlinks, false);
    mainWindow.simulateProcessingOne();
};
