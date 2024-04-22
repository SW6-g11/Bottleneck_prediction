#include "sheetreader.h"
#include "graphmaker.h"
#include "linkutils.h"
#include "traffic.h"
#include "path.h"
#include "router.h"
#include "link.h"

using namespace std;

class Graphmaker
{
    // string directoryPath;

    public:  // Default constructor
        Graphmaker() {
           
            }
        
    public: void processDataForDay(const std::string &directoryPath, int day, int Limit)
    {
        SheetReader Readmaster
        vector<Linkutils> linkUtilsData;
        vector<Traffic> trafficData;
        vector<Paths> pathsData;
        vector<Router> routersData;
        vector<Link> linksData;
        cout << "Processing linkutils" << endl;
        // Read link utilities data
        string linkUtilsFileName = directoryPath + "/link-util-day" + to_string(day) + ".csv";
        SheetReader.readData(linkUtilsFileName, linkUtilsData, readLinkUtils, false);
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

};

