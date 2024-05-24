#include "graphviz.h"
#include "graphmaker.h"
#include "Link.h"
#include "Linkutils.h"
#include "Path.h"
#include "Router.h"
#include "Sheetreader.h"
#include "Traffic.h"
#include <iostream>
#include <fstream>
#include <mainwindow.h>
#include "SimulatorController.h"
#include <QProcess>
#include <QMessageBox>
#include <QString>
#include <QStringList>


using namespace std;

void Graphviz::GenerateGraphViz(const string& filename, bool usePreLoad) {
    graphDataStruct& graphdata = SimulatorController::getGraphDataPointer();
    MainWindow& mainWindow = MainWindow::getInstance(); 
    
    
    string filePath = "../images/" + filename;
    ofstream dotFile(filePath);

    if (!dotFile.is_open())
    {
        cerr << "Error: Failed to open file " << filename << endl;
        return;
    }

    
    dotFile << "digraph G { \n" << endl;
    dotFile << "\t" << "graph [layout=neato];" << endl;
    writeRouters(dotFile, graphdata.MappedRouterVector);
    mainWindow.simulateProcessingTwo();
    // writeTraffic(dotFile, trafficData);
    mainWindow.simulateProcessingTwo();
    // writePaths(dotFile, pathsData);
    if(usePreLoad){
        writeTraffic(dotFile, graphdata.Augmentedlinks, usePreLoad);
    }else{
        writeLinks(dotFile, graphdata.Augmentedlinks);
        }
    
    mainWindow.simulateProcessingTwo();
    mainWindow.simulateProcessingTwo();
    // writeLinkUtils(dotFile, linkUtilsData);    
    dotFile << "}\n" << endl;

    dotFile.close();
    mainWindow.simulateProcessingTwo();

    if (dotFile.fail())
    {
        cerr << "Error: Failed to write to file " << filename << endl;
        return;
    }

    Graphviz::GenerateImageFromDotFile(filePath);

    // mainWindow.openGraphvizImage(filePath);
}

void Graphviz::writeRouters(ofstream& dotFile, vector<MappedRouter>& routervector) {
    std:cout<<routervector.size()<<endl;
    for (const auto& router : routervector) {
        dotFile << "\t" << router.id << "[pos=\""<< router.longitude <<","<< router.latitude <<"!\"];\n";
    }
}



void Graphviz::writeTraffic(std::ofstream& dotFile, const std::vector<AugmentedLink>& linksData, bool usePreLoad) {
    for (const auto& AugmentedLink : linksData) {
        dotFile << "\t" << AugmentedLink.linkStart << " -> " << AugmentedLink.linkEnd << " [label=" << AugmentedLink.getRemainingCapacity(AugmentedLink.start_, usePreLoad, false) << ", color=yellow];\n";
    }
}

void Graphviz::writeLinks(std::ofstream& dotFile, const std::vector<AugmentedLink>& linksData) {
    for (const auto& AugmentedLink : linksData) {
        dotFile << "\t" << AugmentedLink.linkStart << " -> " << AugmentedLink.linkEnd << " [label=" << AugmentedLink.capacity << ", color=green];\n";
    }
}


void Graphviz::GenerateImageFromDotFile(string dotFilename){
    MainWindow& mainWindow = MainWindow::getInstance(); 
      // Use QProcess to run the dot command
        QProcess process;
        QStringList arguments;
        string pngFilename = Graphviz::convertDotToPngFilename(dotFilename);
        arguments << "-Tpng" << QString::fromStdString(dotFilename) << "-o" << QString::fromStdString(pngFilename);
        
        process.start("dot", arguments);
        process.waitForFinished(-1);  // Wait for the process to finish
        std:cout<<"looking for file: " << dotFilename<<endl;
        if (process.exitCode() == 0) {
            QMessageBox::information(nullptr, "Success", "Graphviz output successfully generated as PNG.");
        } else {
            QMessageBox::warning(nullptr, "Error", "Failed to generate PNG from DOT file.");
        }
        mainWindow.imageSaver(pngFilename);
}

// // This is not implemented yet!!!
// void Graphviz::InvertDotFile(const std::string& dotFilename){
//     std:string peakfile ="NetworkDuringTheoreticPeak";
//     std:int tempflow = 0;
    
// }

 std::string Graphviz::convertDotToPngFilename(const std::string& dotFilename) {
    std::string pngFilename = dotFilename;
    // Check if the filename ends with ".dot" and replace it with ".png"
    if (pngFilename.size() >= 4 && pngFilename.compare(pngFilename.size() - 4, 4, ".dot") == 0) {
        pngFilename.replace(pngFilename.size() - 4, 4, ".png");
    } else {
        // If it doesn't end with ".dot", just append ".png"
        pngFilename += ".png";

    }
    return pngFilename;
}

