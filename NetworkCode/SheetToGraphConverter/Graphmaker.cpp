
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <filesystem>
#include "SheetReader.h"
#include "Graphmaker.h"
using namespace std;

void Graphmaker::processDataForDay(string &directoryPath, int day, int Limit)
    {
        SheetReader Readmaster(Limit);
        vector<Linkutils> linkUtilsData;
        vector<Traffic> trafficData;
        vector<Paths> pathsData;
        vector<Router> routersData;
        vector<Link> linksData;
        cout << "Processing linkutils" << endl;
        // Read link utilities data
        string linkUtilsFileName = directoryPath + "/link-util-day" + to_string(day) + ".csv";
        Readmaster.readData(linkUtilsFileName, linkUtilsData, false);
        cout << "Processing flowfile" << endl;
        // Read flows data
        string flowsFileName = directoryPath + "/flow-traffic-day" + to_string(day) + ".csv";
        Readmaster.readData(flowsFileName, trafficData, false);
        cout << "Processing pathfile" << endl;
        // Read paths data
        string pathsFileName = directoryPath + "/flow-paths-day" + to_string(day) + ".csv";
        Readmaster.readData(pathsFileName, pathsData, false);
        cout << "Processing routerdata" << endl;
        // Read routers data
        string routersFileName = directoryPath + "/routers.csv";
        Readmaster.readData(routersFileName, routersData, false);
        cout << "Processing links" << endl;
        // Read links data
        string linksFileName = directoryPath + "/links.csv";
        Readmaster.readData(linksFileName, linksData, false);

        cout << "Done" << endl;

        int userInput;
        cin >> userInput;
    };
    // void printTimestamp()
    // {
    //     // Get current time
    //     time_t currentTime = time(nullptr);

    //     // Convert current time to local time
    //     tm *localTime = localtime(&currentTime);

    //     // Format and print the local time
    //     char timeBuffer[80]; // Buffer to store formatted time
    //     strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", localTime);
    //     cout << "Current local time: " << timeBuffer << endl;
    // }

    // void printRouters(const vector<Router> &routersData, int numRoutersToPrint)
    // {
    //     cout << "Printing " << numRoutersToPrint << " routers:" << endl;
    //     int count = 0;
    //     for (const Router &router : routersData)
    //     {
    //         cout << "Router ID: " << router.id << ", Latitude: " << router.latitude << ", Longitude: " << router.longitude << ", Type: " << router.type << endl;
    //         count++;
    //         if (count >= numRoutersToPrint)
    //         {
    //             break; // Exit loop after printing desired number of routers
    //         }
    //     }
    // }

