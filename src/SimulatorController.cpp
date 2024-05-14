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
    dinicsInstance.populateDinics(graphData.Augmentedlinks, graphData.MappedRouterVector, false);

    int result = dinicsInstance.compute_flow(source, sink);
    std::cout << "Result: " << result << std::endl;
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
    std::cout << "ProblemPaths length: " << problempaths.size() << std::endl;
    int dinicscounter = 0;
    /*
    for (const auto &path : problempaths)
    {
        std::cout << "running dinics for the " << dinicscounter << " time" << std::endl;
        dinicscounter++;
        runDinics(path.origin, path.destination);
    }
    */
    runDinics("R1", "R9");

    // for(i<problempaths.size: i++)
    //     runDinics(problempaths[i].2, problempaths[i].3)
}
