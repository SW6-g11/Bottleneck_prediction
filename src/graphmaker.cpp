#include "graphmaker.h"
#include <mainwindow.h>
#include <iostream>
#include <vector>
#include "Link.h"
#include "Linkutils.h"
#include "Path.h"
#include "Router.h"
#include "Sheetreader.h"
#include "Traffic.h"
#include "graphDataStruct.h"
#include <future>

using namespace std;

void Graphmaker::processDataForDay(string &directoryPath,
                                   int day,
                                   int Limit,
                                   graphDataStruct &graphdata)
{
    SheetReader Readmaster(Limit);
    MainWindow &mainWindow = MainWindow::getInstance();

    graphdata.Augmentedlinks.clear();
    graphdata.linkUtilsData.clear();
    graphdata.MappedRouterVector.clear();
    graphdata.pathsData.clear();
    graphdata.trafficData.clear();

    string linkUtilsFileName =
        directoryPath + "/link-util-day" + to_string(day) + ".csv";
    std::future<void> linkUtilFuture = std::async(std::launch::async, &Readmaster.readData, linkUtilsFileName, graphdata.linkUtilsData, false);
    // Readmaster.readData(linkUtilsFileName, graphdata.linkUtilsData, false);
    mainWindow.simulateProcessingOne();

    string flowsFileName =
        directoryPath + "/flow-traffic-day" + to_string(day) + ".csv";
    // Readmaster.readData(flowsFileName, graphdata.trafficData, false);
    std::future<void> flowTrafficFuture = std::async(std::launch::async, &Readmaster.readData, flowsFileName, graphdata.trafficData, false);
    mainWindow.simulateProcessingOne();

    string pathsFileName =
        directoryPath + "/flow-paths-day" + to_string(day) + ".csv";
    // Readmaster.readData(pathsFileName, graphdata.pathsData, false);
    std::future<void> flowPathsFuture = std::async(std::launch::async, &Readmaster.readData, pathsFileName, graphdata.pathsData, false);
    mainWindow.simulateProcessingOne();

    string routersFileName = directoryPath + "/routers.csv";
    Readmaster.readData(routersFileName, graphdata.MappedRouterVector, false);
    std::future<void> routersFuture = std::async(std::launch::async, &Readmaster.readData, routersFileName, graphdata.MappedRouterVector, false);
    mainWindow.simulateProcessingOne();

    string linksFileName = directoryPath + "/links.csv";
    Readmaster.readData(linksFileName, graphdata.Augmentedlinks, false);
    std::future<void> linsFuture = std::async(std::launch::async, &Readmaster.readData, linksFileName, graphdata.Augmentedlinks, false);
    mainWindow.simulateProcessingOne();

    std::string dots = "" while (linkUtilFuture.wait_for(std::chrono::milliseconds(100)) != std::future_status::ready)
    {
        mainWindow.clearTerminal();
        mainWindow.addToTerminal("Loading" + dots);
        if (dots.size() < 3)
        {
            dots += ".";
        }
        else
        {
            dots = "";
        }
        // Simulate doing some other work
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
};

bool Graphmaker::isdone(std::future<void> a, std::future<void> b, std::future<void> c, std::future<void> d, std::future<void> e)
{
    return a.wait_for(std::chrono::milliseconds(20)) != std::future_status::ready &&
           b.wait_for(std::chrono::milliseconds(20)) != std::future_status::ready &&
           c.wait_for(std::chrono::milliseconds(20)) != std::future_status::ready &&
           d.wait_for(std::chrono::milliseconds(20)) != std::future_status::ready &&
           e.wait_for(std::chrono::milliseconds(20)) != std::future_status::ready;
}