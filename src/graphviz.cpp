#include "graphviz.h"
#include "graphmaker.h"
#include "link.h"
#include "linkutils.h"
#include "path.h"
#include "router.h"
#include "sheetreader.h"
#include "traffic.h"
#include <iostream>
#include <fstream>
#include <mainwindow.h>

using namespace std;

void Graphviz::GenerateGraphViz(const string& filename) {
    Graphmaker graph;
    const vector<Router>& routersData = graph.getRoutersData();
    const vector<Traffic>& trafficData = graph.getTrafficData();
    const vector<Paths>& pathsData = graph.getPathsData();
    const vector<Linkutils>& linkUtilsData = graph.getLinkUtilsData();
    const vector<Link>& linksData = graph.getLinksData();
    MainWindow& mainWindow = MainWindow::getInstance();
    
    string filePath = "../images/" + filename + ".dot";
    ofstream dotFile(filePath);

    if (!dotFile.is_open()) {
        cerr << "Error: Failed to open file " << filename << endl;
        return;
    }
    
    dotFile << "digraph G { \n" << endl;
    
    // Write routers as nodes
    for (const auto& Router : routersData) {
        dotFile << "\t\"" << Router.id << "\" [label=\"" << Router.id << "\", shape=circle];" << endl;
    }
    
    mainWindow.simulateProcessingTwo();
    // Write traffic data as edges with labels
    for (const auto& Traffic : trafficData) {
        dotFile << "\t\"" << Traffic.origin << "\" -> \"" << Traffic.destination << "\" [label=\"" << Traffic.avgTraffic << "\", color=red];" << endl;
    }

    mainWindow.simulateProcessingTwo();
    // Write paths data as edges
    for (const auto& Path : pathsData) {
        for (size_t i = 0; i < Path.path.size() - 1; ++i) {
            dotFile << "\t\"" << Path.path[i] << "\" -> \"" << Path.path[i + 1] << "\" [style=dashed];" << endl;
        }
    }

    mainWindow.simulateProcessingTwo();
    // Write link utils data as edges with labels
    for (const auto& LinkUtils : linkUtilsData) {
        dotFile << "\t\"" << LinkUtils.linkStart << "\" -> \"" << LinkUtils.linkEnd << "\" [label=\"" << LinkUtils.avgUtilization << "\", color=blue];" << endl;
    }

    mainWindow.simulateProcessingTwo();
    // Write links data as edges with labels
    for (const auto& Link : linksData) {
        dotFile << "\t\"" << Link.linkStart << "\" -> \"" << Link.linkEnd << "\" [label=\"" << Link.capacity << "\", color=green];" << endl;
    } 
    
    dotFile << "}\n" << endl;
    dotFile.close();
    mainWindow.simulateProcessingTwo();
    
    if (dotFile.fail()) {
        cerr << "Error: Failed to write to file " << filename << endl;
        return;
    }
}
