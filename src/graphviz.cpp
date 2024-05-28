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
#include <filesystem>

using namespace std;

void Graphviz::GenerateDotandPNGFile(const string &filename, bool usePreLoad, bool useTraffic, bool mincut, std::optional<std::string> result, std::optional<vector<std::string>> mincutResult)
{
    const std::string folder = "../images/";
    if (!std::filesystem::exists(folder))
    {
        std::filesystem::create_directory(folder);
    }
    if (result.has_value())
    {
        cout << result.value() << endl;
    }
    else
    {
        cout << "no result passed" << endl;
    }
    MainWindow &mainWindow = MainWindow::getInstance();
    string filePath = folder + filename;
    ofstream dotFile(filePath);

    graphDataStruct &graphdata = SimulatorController::getGraphDataPointer();

    if (!dotFile.is_open())
    {
        cerr << "Error: Failed to open file " << filename << endl;
        return;
    }
    dotFile << "digraph G { \n"
            << endl;
    dotFile << "\t" << "graph [layout=neato];" << endl;
    writeRouters(dotFile, graphdata.MappedRouterVector, result);
    bool peaksetgraph = (filename == "NetworkDuringTheoreticPeak"); /// bruges kun til color

    if (!useTraffic)
    {
        std::cout << "graph is not using traffic!" << endl;
        writeLinks(dotFile, graphdata.Augmentedlinks, result);
    }
    else if (mincut)
    {
        std::cout << "graph is mincut true" << endl;
        writeMincut(dotFile, graphdata.Augmentedlinks, result, mincutResult);
    }
    else
    {
        std::cout << "graph is default: traffic, preload: " << usePreLoad << endl;
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

void Graphviz::writeRouters(ofstream &dotFile, vector<MappedRouter> &routervector, std::optional<string> minCutTarget)
{
    std::unordered_map<string, string> colors = {
        {"normalColor", "black"},
        {"specialColor", "Red"}};

    for (const auto &router : routervector)
    {
        dotFile << "\t" << router.id << "[color=\"" << getRouterColor(router, colors, minCutTarget) << "\",pos=\"" << router.longitude << "," << router.latitude << "!\"];\n";
    }
}
std::string Graphviz::getRouterColor(const MappedRouter &router, std::unordered_map<string, string> colors, std::optional<string> minCutTarget)
{
    if (!minCutTarget.has_value())
        return colors["normalColor"];
    if (minCutTarget.value().find(router.id) != std::string::npos)
    {
        return colors["specialColor"];
    }
    return colors["normalColor"];
}

void Graphviz::writeTraffic(std::ofstream &dotFile, const std::vector<AugmentedLink> &linksData, bool usePreLoad, bool PeaksetOnly, std::optional<std::string> result)
{
    std::unordered_map<string, string> colors = {
        {"normalColor", "Darkblue"},
        {"pathColor", "Red"},
    };
    for (const auto &augmentedLink : linksData)
    {
        if (PeaksetOnly)
        {
            dotFile << "\t" << augmentedLink.linkStart << " -> " << augmentedLink.linkEnd << " [label=" << augmentedLink.getRemainingCapacity(augmentedLink.start_, usePreLoad, false) << ", color=brown" << "];\n";
        }
        else
        {
            dotFile << "\t" << augmentedLink.linkStart << " -> " << augmentedLink.linkEnd << " [label="
                    << augmentedLink.flow << ", color=" << getRightColor(augmentedLink, colors, result) << "];\n";
        }
    }
}

std::string Graphviz::getRightColor(const AugmentedLink &link, unordered_map<std::string, std::string> colors, std::optional<std::string> result, std::optional<vector<string>> minCut)
{
    bool resultFound = false;
    bool minCutFound = false;
    if (!result.has_value() && !result.has_value())
    {
        return colors["normalColor"];
    }
    if (result.has_value() && result.value().find(link.linkStart + "," + link.linkEnd) != std::string::npos)
    {
        resultFound = true;
    }
    if (minCut.has_value() && std::find(minCut.value().begin(), minCut.value().end(), link.linkStart + "," + link.linkEnd) != minCut.value().end())
    {
        minCutFound = true;
    }

    if (minCutFound && resultFound)
    {
        return colors["bothColor"];
    }
    else if (resultFound)
    {
        return colors["pathColor"];
    }
    else if (minCutFound)
    {
        return colors["minCutColor"];
    }
    return colors["normalColor"];
}

void Graphviz::writeLinks(std::ofstream &dotFile, const std::vector<AugmentedLink> &linksData, std::optional<std::string> result)
{
    std::unordered_map<string, string> colors = {
        {"normalColor", "Green"},
        {"pathColor", "Red"}};
    for (const auto &augmentedLink : linksData)
    {
        dotFile << "\t" << augmentedLink.linkStart << " -> " << augmentedLink.linkEnd
                << " [label=" << doubleToString(augmentedLink.capacity) << ", color="
                << getRightColor(augmentedLink, colors, result) << "];\n";
    }
}
void Graphviz::writeMincut(std::ofstream &dotFile, const std::vector<AugmentedLink> &linksData, std::optional<std::string> result, std::optional<vector<std::string>> mincutResult)
{
    std::unordered_map<string, string> colors = {
        {"normalColor", "Black"},
        {"pathColor", "Black"},
        {"minCutColor", "Blue"},
        {"bothColor", "Blue"} // Should be the combination of minCut and path
    };

    for (const auto &augmentedLink : linksData)
    {
        dotFile << "\t" << augmentedLink.linkStart << " -> " << augmentedLink.linkEnd
                << " [label=" << doubleToString(augmentedLink.getRemainingCapacity(augmentedLink.start_, false, true))
                << ", color=" << getRightColor(augmentedLink, colors, result, mincutResult) << "];\n";
    }
    dotFile << "\tnode [shape=plaintext];\n"
            << "\tColorIndicator [label=\"Color for the minCut: " << colors["minCutColor"] << "\", pos=\"0,0.2!\"];\n"
            << "\texplainer [label=\"This is minCut of: " << result.value() << "\", pos=\"0,0!\"];\n"
            << "\tnode [shape=ellipse];\n";
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
