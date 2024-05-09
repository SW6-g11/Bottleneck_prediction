#include "SimulatorController.h"
#include "graphDataStruct.h"
#include "DinicAlgorithm.h"
#include <algorithm>
#include <map>
#include <regex>
#include <vector>
#include "paths.h"
#include <Networkmanipulator.h>

graphDataStruct SimulatorController::graphData;
DinicAlgorithm SimulatorController::dinicsInstance;

void SimulatorController::runDinics(const std::string source, const std::string sink)
{
    dinicsInstance.addLinks(graphData.linksData);
    dinicsInstance.findMaxFlow(source, sink);
}

graphDataStruct &SimulatorController::getGraphDataPointer()
{
    return graphData;
}

void SimulatorController::DinicsOnBottlenecksNoAugmentedNetork(int amountPUV, int amountPaths)
{
    std::vector<std::pair<std::string, Linkutils>> peakset;
    Networkmanipulator::findPeakUtilValues(amountPUV, peakset, getGraphDataPointer());
    Networkmanipulator::reduceVector(peakset, amountPUV);
    vector<Paths> problempaths = Networkmanipulator::findLinksInPaths(peakset, amountPUV, getGraphDataPointer());
    Networkmanipulator::reduceVector(problempaths, amountPaths);
    for (const auto &path : problempaths)
    {
        runDinics(path.origin, path.destination);
    }

    // for(i<problempaths.size: i++)
    //     runDinics(problempaths[i].2, problempaths[i].3)
}
