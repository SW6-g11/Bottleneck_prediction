#include "SimulatorController.h"
#include "graphDataStruct.h"
#include "DinicAlgorithm.h"
#include <map>

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

std::unordered_map<std::string, Linkutils> SimulatorController::findPeaks()
{
    std::unordered_map<std::string, Linkutils> set = {};
    std::cout << "Size " + std::to_string(graphData.linkUtilsData.size()) << std::endl;
    for (int i = 0; i < graphData.linkUtilsData.size(); i++)
    {
        std::string fingerprint = graphData.linkUtilsData[i].linkStart + graphData.linkUtilsData[i].linkEnd;
        if (set.find(fingerprint) != set.end())
        {
            std::cout << "Did not find: " + std::to_string(i) << std::endl;
            set.insert({fingerprint, graphData.linkUtilsData[i]});
        }
        else
        {
            std::cout << "Found in set, comparing: " + std::to_string(i) << std::endl;
            if (set[fingerprint].avgUtilization < graphData.linkUtilsData[i].avgUtilization)
            {
                set.insert_or_assign(fingerprint, graphData.linkUtilsData[i]);
            }
        }
    }
    std::cout << set.size() << std::endl;

    //
    // vector<Linkutils> PeakValueArray;
    // PeakValueArray.reserve(set.size());
    // for (const auto &pair : set)
    // {
    //     PeakValueArray.push_back(pair.second); // Extract the LinkUtils objects and add them to the vector
    // }
    // return PeakValueArray;
    return set;
}

void SimulatorController::findPeakUtilValues(int amountofPUVs)
{
    std::unordered_map<std::string, Linkutils> peakSet = findPeaks();

    std::unordered_map<std::string, Link> PUVMap;
    for (int i = 0; i < graphData.linksData.size(); i++)
    {
        const std::string fingerprint = makeFingerPrint(graphData.linksData[i]);
        PUVMap.insert({fingerprint, graphData.linksData[i]});
    }
    for (auto &pair : PUVMap)
    {
        std::cout << pair.first << std::endl;
        if (peakSet.find(pair.first) == peakSet.end())
        {
            std::cout << "DataSet error, link and linkUtils not matching" << std::endl;
            continue;
        }
        else
        {
            std::cout << "WHOOOOO" << std::endl;
        }
        // avgUtilization is actually peakutilization implicitly because it is in peakSet
        double a = peakSet[pair.first].avgUtilization / pair.second.capacity;
        std::cout << a << std::endl;
    }

    // for (auto &pair : peakSet)
    // {

    //     vector<Linkutils> replaceLocations = replaceByFingerPrint(&SimulatorController::makeFingerPrint, pair.second, graphData.linkUtilsData);
    // }
}

// function which returns the links router names as 1 string
std::string SimulatorController::makeFingerPrint(Linkutils LinkUtils)
{
    return LinkUtils.linkStart + LinkUtils.linkEnd;
}
std::string SimulatorController::makeFingerPrint(Link link)
{
    return link.linkStart + link.linkEnd;
}