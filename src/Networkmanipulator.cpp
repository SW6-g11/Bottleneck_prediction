#include "Networkmanipulator.h"
#include "graphDataStruct.h"
#include <SimulatorController.h>
#include <algorithm>
#include <map>
#include <regex>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <regex>
#include <unordered_map>

// void Networkmanipulator::AugmentNetworkbyTimeStamp(string timestamp, vector<Linkutils> &Linkutildata, vector<Linkutils> &AugmentedLinks)
// {

// }
std::unordered_map<std::string, Linkutils> Networkmanipulator::findPeaks(graphDataStruct &graphData)
{
    std::unordered_map<std::string, Linkutils> peakSet = {};
    std::cout << "Size " + std::to_string(graphData.linkUtilsData.size()) << std::endl;
    // loop through all linkutildata
    for (int i = 0; i < graphData.linkUtilsData.size(); i++)
    {
        std::string fingerprint = makeFingerPrint(graphData.linkUtilsData[i]);
        if (fingerprint == "")
        {
            std::cout << "Found an issue, fingerprint empty" << std::endl;
            continue;
        }
        // if the link is not already present in the peakset
        if (peakSet.find(fingerprint) == peakSet.end())
        {
            std::cout << "Did not find: \"" + fingerprint + "\"" << std::endl;
            peakSet.insert({fingerprint, graphData.linkUtilsData[i]});
        }
        else // if the link is already present in the peakset
        {
            std::cout << "Found in peakSet, comparing: " + fingerprint + "\"" << std::endl;
            if (peakSet[fingerprint].avgUtilization < graphData.linkUtilsData[i].avgUtilization)
            {
                peakSet.insert_or_assign(fingerprint, graphData.linkUtilsData[i]);
            }
        }
    }
    std::cout << peakSet.size() << std::endl;

    //
    // vector<Linkutils> PeakValueArray;
    // PeakValueArray.reserve(peakSet.size());
    // for (const auto &pair : peakSet)
    // {
    //     PeakValueArray.push_back(pair.second); // Extract the LinkUtils objects and add them to the vector
    // }
    // return PeakValueArray;
    return peakSet;
}
// function which returns the links router names as 1 string
std::string Networkmanipulator::makeFingerPrint(Linkutils LinkUtils)
{
    return LinkUtils.linkStart + "," + LinkUtils.linkEnd;
}
std::string Networkmanipulator::makeFingerPrint(Link link)
{
    return link.linkStart + "," + link.linkEnd;
}

vector<Paths> Networkmanipulator::findLinksInPaths(std::vector<std::pair<std::string, Linkutils>> peakset, int amountofBottleneckLinks, graphDataStruct &graphData)
{

    std::unordered_map<std::string, Paths> ProblematicPathMap;
    // Populate ProblematicPathVector so we can remove dublicates.
    // for (int j = 0; j < graphData.pathsData.size(); j++)
    // {
    //     if (ProblematicPathVector.find(graphData.pathsData[j].fingerprint) == ProblematicPathVector.end())
    //         ProblematicPathVector.insert({graphData.pathsData[j].fingerprint, graphData.pathsData[j]});
    // }

    // for each bottleneck link in the peakset, search the paths data to find all paths which uses this link.
    for (int i = 0; i < peakset.size(); i++)
    {
        std::cout << +"\" searching for: \"" + peakset[i].first + "\"" << endl;
        std::regex test = std::regex(".*" + peakset[i].first + ".*"); // peakset[i].first = the link fingerprint
        for (int j = 0; j < graphData.pathsData.size(); j++)
        {
            if (ProblematicPathMap.find(graphData.pathsData[j].fingerprint) != ProblematicPathMap.end())
                continue;
            // std::cout << "Searching in: \"" + PathCorrector(graphData.pathsData[j]) + "\" searching for: \"" + peakset[i].first + "\"" << endl;
            //  if we find the bottlenecklink (from peakset) in the path, add that path to the problematicpath vector
            if (std::regex_search(PathCorrector(graphData.pathsData[j]), test))
                ProblematicPathMap.insert({graphData.pathsData[j].fingerprint, graphData.pathsData[j]});
        }
    }

    // For each bottleneck link in the peakset, search the problematic vectors, and increase path length.
    double PUVmodifier = 2 / amountofBottleneckLinks;
    for (int i = 0; i < peakset.size(); i++)
    {
        std::regex test = std::regex(".*" + peakset[i].first + ".*"); // peakset[i].first = the link fingerprint
        for (auto &pathPair : ProblematicPathMap)
        {
            if (std::regex_search(PathCorrector(pathPair.second), test))
            {
                // If the bottleneck link is found in the path, increase its length by the modifier
                pathPair.second.pathLength += (pathPair.second.pathLength * PUVmodifier);
                std::cout << " increased pathsize of path: " + pathPair.second.to_string() << endl;
            }
        }
    }

    std::vector<Paths> ProblematicPathVector;
    for (const auto &pair : ProblematicPathMap)
    {
        ProblematicPathVector.push_back(pair.second);
    }
    ProblematicPathMap.clear();
    // sort the problematicpathvector by path length, longest first
    std::sort(ProblematicPathVector.begin(), ProblematicPathVector.end(), &Networkmanipulator::comparePathLength);
    // ProblematicPathVector.erase(std::unique(ProblematicPathVector.begin(), ProblematicPathVector.end()), ProblematicPathVector.end());
    std::cout << "***All problematic paths (No duplicates), ordered by pathlength: ***" << endl;
    for (const Paths &Problematicpath : ProblematicPathVector)
    {
        std::cout << Problematicpath.to_string() + " pathsize: " << Problematicpath.pathLength << endl;
    }

    return ProblematicPathVector;
}

bool Networkmanipulator::comparePeakUtilValues(const std::pair<std::string, Linkutils> &a, const std::pair<std::string, Linkutils> &b)
{
    return a.second.PeakUtilValue > b.second.PeakUtilValue;
}
bool Networkmanipulator::comparePathLength(const Paths &a, const Paths &b)
{
    std::cout << to_string(a.pathLength) + "|" + to_string(b.pathLength) << std::endl;
    return a.pathLength > b.pathLength;
}
/*
bool Networkmanipulator::comparePathFingerprint(const Paths &a, const Paths &b)
{
    std::cout << "comparing " + a.fingerprint + "|" + b.fingerprint << std::endl;
    return a.fingerprint > b.fingerprint;
}
*/

bool Networkmanipulator::alphanumericCompareDecorator(const Paths a, const Paths b)
{
    for (int i = 0; i < a.fingerprint.size(); i++)
    {
        if (a.fingerprint[i] != b.fingerprint[i])
        {
            return a.fingerprint[i] > b.fingerprint[i];
        }
    }
    return false;
    // return alphanumericCompare(a.fingerprint, b.fingerprint);
}

bool Networkmanipulator::alphanumericCompare(const std::string &a, const std::string &b)
{
    size_t i = 0, j = 0;
    while (i < a.length() && j < b.length())
    {
        if (std::isdigit(a[i]) && std::isdigit(b[j]))
        {
            // If both characters are digits, compare the numeric values
            long numA = 0, numB = 0;
            while (i < a.length() && std::isdigit(a[i]))
            {
                numA = numA * 10 + (a[i++] - '0');
            }
            while (j < b.length() && std::isdigit(b[j]))
            {
                numB = numB * 10 + (b[j++] - '0');
            }
            if (numA != numB)
            {
                return numA < numB;
            }
        }
        else
        {
            // Compare characters normally
            if (a[i] != b[j])
            {
                return a[i] < b[j];
            }
            ++i;
            ++j;
        }
    }
    // If one string is a prefix of the other, shorter string comes first
    return i == a.length();
}

// path data comes in the format: timestamp(""), origin(""), destination(""), path(), where path are all if any intermidiate steps. which is stupid AF
// PathCorrector lets us compare links to paths, so we can see if a given link is part of a path, by formatting the pathvector.path to be origin(""), *intermidiate steps, destination("")
string Networkmanipulator::PathCorrector(Paths chaoticpath)
{
    string correctedpath = chaoticpath.origin + ",";
    // if (chaoticpath.path.size() > 0)
    // {
    //     std::cout << "path.size is > 0 here:" << std::endl;
    //     std::cout << chaoticpath.origin + chaoticpath.path[0] + chaoticpath.path[1] + chaoticpath.destination << std::endl;
    // }
    for (const auto &str : chaoticpath.path)
    {
        correctedpath += str + ",";
    }
    correctedpath += chaoticpath.destination;
    return correctedpath;
}

void Networkmanipulator::findPeakUtilValues(int amountofBottleneckLinks, vector<std::pair<std::string, Linkutils>> &BottleLinks, graphDataStruct &graphData)
{
    std::unordered_map<std::string, Linkutils> peakSet = findPeaks(graphData);

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
        peakSet[pair.first].PeakUtilValue = peakSet[pair.first].avgUtilization / pair.second.capacity;

        // Sort peakSet by highest PeakUtilValue
    }
    // reset the BottleLinks
    BottleLinks.clear();
    BottleLinks.assign(peakSet.begin(), peakSet.end());
    std::sort(BottleLinks.begin(), BottleLinks.end(), &Networkmanipulator::comparePeakUtilValues);

    // Output sorted results
    std::cout << "***Sorted BottleLinks:****" << std::endl;
    for (int i = 0; i < amountofBottleneckLinks && i < BottleLinks.size(); ++i)
    {
        const auto &pair = BottleLinks[i];
        std::cout << pair.first << " - PeakUtilValue: " << pair.second.PeakUtilValue << std::endl;
        // DinicAlgorithm::DinicAlgorithm(())
    }
    // Output the rest of the results to the console
    std::cout << "***Remaining results:****" << std::endl;
    for (int i = amountofBottleneckLinks; i < BottleLinks.size(); ++i)
    {
        const auto &pair = BottleLinks[i];
        std::cout << pair.first << " - PeakUtilValue: " << pair.second.PeakUtilValue << std::endl;
    }
    // for (auto &pair : peakSet)
    // {

    //     vector<Linkutils> replaceLocations = replaceByFingerPrint(&SimulatorController::makeFingerPrint, pair.second, graphData.linkUtilsData);
    // }
}