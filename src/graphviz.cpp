#include "graphviz.h"
#include "graphmaker.h"
#include "link.h"
#include "Linkutils.h"
#include "Path.h"
#include "Router.h"
#include "Sheetreader.h"
#include "Traffic.h"
#include <iostream>
#include <fstream>
#include <mainwindow.h>

using namespace std;

void Graphviz::GenerateGraphViz(const string &filename)
{
    Graphmaker graph;
    MainWindow &mainWindow = MainWindow::getInstance();
    const vector<Router> &routersData = graph.getRoutersData();
    const vector<Traffic> &trafficData = graph.getTrafficData();
    const vector<Paths> &pathsData = graph.getPathsData();
    const vector<Linkutils> &linkUtilsData = graph.getLinkUtilsData();
    const vector<Link> &linksData = graph.getLinksData();

    string filePath = "../images/" + filename;
    ofstream dotFile(filePath);

    if (!dotFile.is_open())
    {
        cerr << "Error: Failed to open file " << filename << endl;
        return;
    }

    dotFile << "digraph G { \n"
            << endl;

    writeRouters(dotFile, routersData);
    mainWindow.simulateProcessingThree(5);
    writeTraffic(dotFile, trafficData);
    mainWindow.simulateProcessingThree(35);
    writePaths(dotFile, pathsData);
    mainWindow.simulateProcessingThree(10);
    writeLinkUtils(dotFile, linkUtilsData);
    mainWindow.simulateProcessingThree(35);
    writeLinks(dotFile, linksData);

    dotFile << "}\n"
            << endl;
    dotFile.close();
    mainWindow.simulateProcessingThree(15);

    if (dotFile.fail())
    {
        cerr << "Error: Failed to write to file " << filename << endl;
        return;
    }
    // mainWindow.openGraphvizImage(filePath);
}

void Graphviz::writeRouters(ofstream &dotFile, const vector<Router> &routersData)
{
    for (const auto &router : routersData)
    {
        dotFile << "\t\"" << router.id << "\" [label=\"" << router.id << "\", shape=circle];" << endl;
    }
}

void Graphviz::writeTraffic(ofstream &dotFile, const vector<Traffic> &trafficData)
{
    for (const auto &traffic : trafficData)
    {
        dotFile << "\t\"" << traffic.origin << "\" -> \"" << traffic.destination << "\" [label=\"" << traffic.avgTraffic << "\", color=red];" << endl;
    }
}

void Graphviz::writePaths(ofstream &dotFile, const vector<Paths> &pathsData)
{
    for (const auto &path : pathsData)
    {
        for (size_t i = 0; i < path.path.size() - 1; ++i)
        {
            dotFile << "\t\"" << path.path[i] << "\" -> \"" << path.path[i + 1] << "\" [style=dashed];" << endl;
        }
    }
}

void Graphviz::writeLinkUtils(ofstream &dotFile, const vector<Linkutils> &linkUtilsData)
{
    for (const auto &linkUtils : linkUtilsData)
    {
        dotFile << "\t\"" << linkUtils.linkStart << "\" -> \"" << linkUtils.linkEnd << "\" [label=\"" << linkUtils.avgUtilization << "\", color=blue];" << endl;
    }
}

void Graphviz::writeLinks(ofstream &dotFile, const vector<Link> &linksData)
{
    for (const auto &link : linksData)
    {
        dotFile << "\t\"" << link.linkStart << "\" -> \"" << link.linkEnd << "\" [label=\"" << link.capacity << "\", color=green];" << endl;
    }
}