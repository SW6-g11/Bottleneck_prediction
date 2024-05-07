#include "SimulatorController.h"
#include "graphDataStruct.h"
#include "DinicAlgorithm.h"

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
/*
DinicAlgorithm &SimulatorController::getDinicsInstance(const std::vector<Link> &linksData)
{
    // Construct dinicsInstance if not already constructed
    if (!dinicsInstance.isValid())
    {
        dinicsInstance = DinicAlgorithm(linksData);
    }
    return dinicsInstance;
}
*/