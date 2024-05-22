#include "SimulatorController.h"
#include "graphDataStruct.h"
#include "DinicAlgorithm.h"
#include <algorithm>
#include <map>
#include <regex>
#include <vector>
#include "Path.h"
#include <Networkmanipulator.h>

graphDataStruct SimulatorController::graphData;
DinicAlgorithm SimulatorController::dinicsInstance;

int SimulatorController::runDinics(const std::string source, const std::string sink, bool usePreLoad, bool isCalculatingMincut)
{
    dinicsInstance.populateDinics(graphData.Augmentedlinks, graphData.MappedRouterVector, true);

    int result = dinicsInstance.compute_flow(source, sink, usePreLoad, isCalculatingMincut);
    std::cout << "Result 2: " << result << std::endl;
    return result;
}

graphDataStruct &SimulatorController::getGraphDataPointer()
{
    return graphData;
}

vector<std::pair<std::string, int>> SimulatorController::DinicsOnBottlenecksNoAugmentedNetork(int amountPUV, int amountPaths, bool usePreLoad)
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

    vector<std::pair<std::string, int>> dinicsResults;
    dinicsResults.reserve(problempaths.size());
    for (const Paths &path : problempaths)
    {
        std::cout << "running dinics for the " << dinicscounter << " time" << std::endl;
        dinicscounter++;
        dinicsResults.push_back(std::pair(Networkmanipulator::makeFingerPrint(path), runDinics(path.origin, path.destination, usePreLoad, false)));
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
    dinicsInstance.findMinCut(source, level, minCut);

    cout << "Min Cut: " << endl;
    for (const auto &cut : minCut)
    {
        cout << cut.first << " - " << cut.second << endl;
    }
    return minCut;
}