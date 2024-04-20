
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <filesystem>
#include "SheetReader.h"
#include "GraphMaker.h"
#include "Linkutils.h"
#include "Traffic.h"
#include "Path.h"
#include "Router.h"
#include "Link.h"

using namespace std;
template <typename T>
class Graphmaker
{
    public: Graphmaker(const std::string &directoryPath);

    public: void processDataForDay(const std::string &directoryPath, int day)
    {
        vector<Linkutils> linkUtilsData;
        vector<Traffic> trafficData;
        vector<Paths> pathsData;
        vector<Router> routersData;
        vector<Link> linksData;
        cout << "Processing linkutils" << endl;
        // Read link utilities data
        string linkUtilsFileName = directoryPath + "/link-util-day" + to_string(day) + ".csv";
        readData(linkUtilsFileName, linkUtilsData, readLinkUtils, false);
        cout << "Processing flowfile" << endl;
        // Read flows data
        string flowsFileName = directoryPath + "/flow-traffic-day" + to_string(day) + ".csv";
        readData(flowsFileName, trafficData, readTraffic, false);
        cout << "Processing pathfile" << endl;
        // Read paths data
        string pathsFileName = directoryPath + "/flow-paths-day" + to_string(day) + ".csv";
        readData(pathsFileName, pathsData, readPaths, false);
        cout << "Processing routerdata" << endl;
        // Read routers data
        string routersFileName = directoryPath + "/routers.csv";
        readData(routersFileName, routersData, readRouters, false);
        cout << "Processing links" << endl;
        // Read links data
        string linksFileName = directoryPath + "/links.csv";
        readData(linksFileName, linksData, readLinks, false);

        cout << "Done" << endl;

        int userInput;
        cin >> userInput;
    }

};

