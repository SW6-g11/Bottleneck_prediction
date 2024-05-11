#include "graphmaker.h"
#include "Sheetreader.h"
#include "Linkutils.h"
#include "Traffic.h"
#include "Path.h"
#include "Router.h"
#include "Link.h"
#include "graphDataStruct.h"

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
    // Read flows data
    cout << "Processing flowfile" << endl;
    string flowsFileName = directoryPath + "/flow-traffic-day" + to_string(day) + ".csv";
    Readmaster.readData(flowsFileName, graphdata.trafficData, false);
    // Read paths data
    cout << "Processing pathfile" << endl;
    string pathsFileName = directoryPath + "/flow-paths-day" + to_string(day) + ".csv";
    Readmaster.readData(pathsFileName, graphdata.pathsData, false);
    // Read routers data
    cout << "Processing routerdata" << endl;
    string routersFileName = directoryPath + "/routers.csv";
    Readmaster.readData(routersFileName, graphdata.MappedRouterVector, false);
    // Read links data
    cout << "Processing links" << endl;
    string linksFileName = directoryPath + "/links.csv";
    Readmaster.readData(linksFileName, graphdata.Augmentedlinks, false);

    cout << "Done" << endl;
    ;
};
