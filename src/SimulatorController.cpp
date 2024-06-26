#include "SimulatorController.h"
#include "graphDataStruct.h"
#include "DinicAlgorithm.h"
#include <algorithm>
#include <map>
#include <regex>
#include <vector>
#include "Networkmanipulator.h"
#include "graphviz.h"
#include "Path.h"

graphDataStruct SimulatorController::graphData;
DinicAlgorithm SimulatorController::dinicsInstance;
bool SimulatorController::UIEnabled = true;

int SimulatorController::runDinics(const std::string source, const std::string sink, bool usePreLoad, bool isCalculatingMincut)
{
    dinicsInstance.populateDinics(graphData.Augmentedlinks, graphData.MappedRouterVector, true);

    int result = dinicsInstance.compute_flow(source, sink, usePreLoad, isCalculatingMincut);
    std::cout << "Result 2: " << result << std::endl;

    return result;
}

void SimulatorController::resetDinics()
{
    dinicsInstance.populateDinics(graphData.Augmentedlinks, graphData.MappedRouterVector, true);
}

graphDataStruct &SimulatorController::getGraphDataPointer()
{
    return graphData;
}

vector<std::pair<std::string, int>> SimulatorController::DinicsOnBottlenecksNoAugmentedNetork(int amountPUV, int amountPaths, bool usePreLoad, bool ShowtrafficinGraph)
{
    std::cout << "DinicsOnBottlenecksNoAugmentedNetork true: " << true << std::endl;
    std::cout << "DinicsOnBottlenecksNoAugmentedNetork is asking for Preload?: " << usePreLoad << std::endl;

    std::vector<std::pair<std::string, Linkutils>> peakset;
    Networkmanipulator::findPeakUtilValues(amountPUV, peakset, getGraphDataPointer());

    Networkmanipulator::reduceVector(peakset, amountPUV);
    vector<Paths> problempaths = Networkmanipulator::findLinksInPaths(peakset, amountPUV, getGraphDataPointer());
    Networkmanipulator::reduceVector(problempaths, amountPaths);
    std::cout << "ProblemPaths length: " << problempaths.size() << std::endl;
    int dinicscounter = 0;
    /*
    std::string problempathsString = "";
    for (const auto &problemPath : problempaths)
    {
        problempathsString += problemPath.fingerprint + "\n";
    }
    */

    vector<std::pair<std::string, int>> dinicsResults;
    dinicsResults.reserve(problempaths.size());
    for (const Paths &path : problempaths)
    {
        std::cout << "running dinics for the " << dinicscounter << " time" << std::endl;
        dinicscounter++;
        std::pair<std::string, int> result = std::pair(Networkmanipulator::makeFingerPrint(path), runDinics(path.origin, path.destination, usePreLoad, false));
        dinicsResults.push_back(result);
        if (SimulatorController::UIEnabled)
        {
            std::cout << "UI ENABLED" << std::endl;
            string filename = ("empty_" + std::to_string(!usePreLoad) + "_Flow_Path_" + path.origin + "---" + path.destination);
            Graphviz::GenerateDotandPNGFile(filename, usePreLoad, ShowtrafficinGraph, false, result.first);
        }
        std::cout << "Over" << std::endl;
    }
    for (const auto &dinicsResult : dinicsResults)
    {
        std::cout << "Result: " << dinicsResult.first << ": " << dinicsResult.second << std::endl;
    }
    return dinicsResults;
}

vector<pair<string, string>> SimulatorController::minCut(std::string source, std::string sink, bool usePreload)
{
    int maxFlow = runDinics(source, sink, usePreload, true);
    vector<MappedRouter> nodes = dinicsInstance.getNodes();
    vector<int> level = vector<int>(nodes.size(), -1);
    vector<pair<string, string>> minCut;
    std::string path = source + "," + sink;
    dinicsInstance.findMinCut(source, level, minCut, path);
    cout << "Min Cut: " << endl;
    for (const auto &cut : minCut)
    {
        cout << cut.first << " - " << cut.second << endl;
    }
    return minCut;
}