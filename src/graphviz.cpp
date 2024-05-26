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
#include <algorithm>
#include <QProcess>
#include <QMessageBox>
#include <QString>
#include <QStringList>
#include <optional>

using namespace std;

void Graphviz::GenerateDotandPNGFile(const string &filename, bool usePreLoad, bool useTraffic, bool mincut, std::optional<std::string> result)
{
    if(result.has_value()) {
        cout << result.value() << endl;
    } else {
        cout << "no result passed" << endl;
    }
    MainWindow &mainWindow = MainWindow::getInstance();
    string filePath = "../images/" + filename;
    ofstream dotFile(filePath);

    graphDataStruct &graphdata = SimulatorController::getGraphDataPointer();

    if (!dotFile.is_open())
    {
        cerr << "Error: Failed to open file " << filename << endl;
        return;
    }
    dotFile << "digraph G { \n"<< endl;
    dotFile << "\t" << "graph [layout=neato];" << endl;
    writeRouters(dotFile, graphdata.MappedRouterVector);
    bool peaksetgraph = (filename == "NetworkDuringTheoreticPeak"); /// bruges kun til color

    if (!useTraffic)
    {
        std::cout<<"graph is not using traffic!"<< endl;
        writeLinks(dotFile, graphdata.Augmentedlinks, result);
    }
    else if (mincut)
    {
        std::cout<<"graph is mincut true"<< endl;
        writeMincut(dotFile, graphdata.Augmentedlinks);
    }
    else
    {
        std::cout<<"graph is default: traffic, preload: "<<usePreLoad<< endl;
        writeTraffic(dotFile, graphdata.Augmentedlinks, usePreLoad, peaksetgraph, result);
    }
    dotFile << "}\n"
            << endl;
    dotFile.close();
    mainWindow.simulateProcessingTwo();

    if (dotFile.fail())
    {
        cerr << "Error: Failed to write to file " << filename << endl;
        return;
    }
    Graphviz::GenerateImageFromDotFile(filePath);
}

void Graphviz::writeRouters(ofstream &dotFile, vector<MappedRouter> &routervector)
{
    std::cout << routervector.size() << endl;
    for (const auto &router : routervector)
    {
        dotFile << "\t" << router.id << "[pos=\"" << router.longitude << "," << router.latitude << "!\"];\n";
    }
}

void Graphviz::writeTraffic(std::ofstream &dotFile, const std::vector<AugmentedLink> &linksData, bool usePreLoad, bool PeaksetOnly, std::optional<std::string> result )
{
    for (const auto &augmentedLink : linksData)
    {
        if (PeaksetOnly)
        {
            dotFile << "\t" << augmentedLink.linkStart << " -> " << augmentedLink.linkEnd << " [label=" << augmentedLink.getRemainingCapacity(augmentedLink.start_, usePreLoad, false) << ", color=brown" << "];\n";
        }
        else
        {
            dotFile << "\t" << augmentedLink.linkStart << " -> " << augmentedLink.linkEnd << " [label=" << augmentedLink.flow << ", color=" << getRightColor(augmentedLink, result, "darkblue", "red") << "];\n";
        }
    }
}

std::string Graphviz::getRightColor(const AugmentedLink &link, std::optional<std::string> result, const std::string &normalColor, const std::string &specialColor) {
    if(result.has_value() && result.value().find(link.linkStart + "," + link.linkEnd) != std::string::npos) {
        return specialColor;
    }
    return normalColor;
}

void Graphviz::writeLinks(std::ofstream &dotFile, const std::vector<AugmentedLink> &linksData, std::optional<std::string> result)
{
    for (const auto &augmentedLink : linksData)
    {
        dotFile << "\t" << augmentedLink.linkStart << " -> " << augmentedLink.linkEnd << " [label=" << doubleToString(augmentedLink.capacity) << ", color=" << getRightColor(augmentedLink, result, "green", "red") << "];\n";
    }
}
void Graphviz::writeMincut(std::ofstream &dotFile, const std::vector<AugmentedLink> &linksData)
{
    for (const auto &augmentedLink : linksData)
    {
        dotFile << "\t" << augmentedLink.linkStart << " -> " << augmentedLink.linkEnd << " [label=" << doubleToString(augmentedLink.getRemainingCapacity(augmentedLink.start_, false, true)) << ", color=" << "purple" << "];\n";
    }
}

std::string Graphviz::doubleToString(double db)
{
    std::string temp = std::to_string(db);
    std::replace(temp.begin(), temp.end(), ',', '.');

    // Remove trailing zeros
    size_t dotPos = temp.find('.');
    if (dotPos != std::string::npos)
    {
        // Remove trailing zeros
        temp.erase(temp.find_last_not_of('0') + 1);
        // Remove trailing dot if it's the last character
        if (temp.back() == '.')
        {
            temp.pop_back();
        }
    }
    return temp;
}

void Graphviz::GenerateImageFromDotFile(string dotFilename)
{
    MainWindow &mainWindow = MainWindow::getInstance();
    // Use QProcess to run the dot command
    QProcess process;
    QStringList arguments;
    string pngFilename = Graphviz::convertDotToPngFilename(dotFilename);
    arguments << "-Tpng" << QString::fromStdString(dotFilename) << "-o" << QString::fromStdString(pngFilename);

    process.start("dot", arguments);
    process.waitForFinished(-1); // Wait for the process to finish
std:
    cout << "looking for file: " << dotFilename << endl;
    if (process.exitCode() == 0)
    {
        QMessageBox::information(nullptr, "Success", "Graphviz output successfully generated as PNG.");
    }
    else
    {
        QMessageBox::warning(nullptr, "Error", "Failed to generate PNG from DOT file.");
    }
    mainWindow.imageSaver(pngFilename);
}

// // This is not implemented yet!!!
// void Graphviz::InvertDotFile(const std::string& dotFilename){
//     std:string peakfile ="NetworkDuringTheoreticPeak";
//     std:int tempflow = 0;

// }

std::string Graphviz::convertDotToPngFilename(const std::string &dotFilename)
{
    std::string pngFilename = dotFilename;
    // Check if the filename ends with ".dot" and replace it with ".png"
    if (pngFilename.size() >= 4 && pngFilename.compare(pngFilename.size() - 4, 4, ".dot") == 0)
    {
        pngFilename.replace(pngFilename.size() - 4, 4, ".png");
    }
    else
    {
        // If it doesn't end with ".dot", just append ".png"
        pngFilename += ".png";
    }
    return pngFilename;
}
