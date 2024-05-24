#include "Sheetreader.h"
#include "Path.h"
#include "link.h"
#include "Router.h"
#include "inputverifyer.h"
#include "Linkutils.h"
#include "Traffic.h"
#include <regex>
#include <MappedRouter.h>
#include <AugmentedLink.h>

using namespace std;

template <>
void SheetReader::readType(istringstream &iss, Linkutils &linkUtilsItem)
{
    // cout << "type linkutils" << endl;
    string timestamp, linkStart, linkEnd, avgUtilizationString;
    double avgUtilization;
    if (getline(iss, timestamp, ',') &&
        getline(iss, linkStart, ',') &&
        getline(iss, linkEnd, ',') &&
        iss >> avgUtilization)
    {
        linkUtilsItem = Linkutils(timestamp, linkStart, linkEnd, avgUtilization);
    }
    else
    {
        cerr << "Warning: Skipping line with insufficient data: " << iss.str() << endl;
    }
}

template <>
void SheetReader::readType<Traffic>(istringstream &iss, Traffic &trafficItem)
{
    // cout << "typetraffic" << endl;
    string timestamp, origin, destination;
    double avgTraffic;
    if (getline(iss, timestamp, ',') &&
        getline(iss, origin, ',') &&
        getline(iss, destination, ',') &&
        iss >> avgTraffic)
    {
        trafficItem = Traffic(timestamp, origin, destination, avgTraffic);
    }
    else
    {
        cerr << "Warning: Skipping line with insufficient data: " << iss.str() << endl;
    }
}
// template <>
// void SheetReader::readType<Paths>(istringstream &iss, Paths &pathsItem)
// {
//     cout << "type paths" << endl;
//     // Read the timestamp, origin, and destination directly from the file stream
//     if (getline(iss, pathsItem.timestamp, ',') &&
//         getline(iss, pathsItem.origin, ',') &&
//         getline(iss, pathsItem.destination, ','))
//     {
//         // Read the rest of the columns (nodes in the path)
//         string pathNode;

//         while (getline(iss, pathNode, ','))
//         {
//             // Skip '[' and ']' characters
//             if (pathNode.front() == '[')
//                 pathNode.erase(0, 1);
//             if (pathNode.back() == ']')
//                 pathNode.pop_back();

//             // Split the nodes separated by tabs
//             istringstream pathStream(pathNode);
//             string pathItem;
//             int itemCount = 0;
//             while (getline(pathStream, pathItem, '\t'))
//             {
//                 if (pathItem == "")
//                     continue;
//                 pathsItem.path.push_back(move(pathItem));
//                 itemCount++;
//                 cout << "item counter: " + to_string(itemCount) << endl;
//                 cout << "item: " + pathItem << endl;
//                 // pathsItem.path.push_back(move(pathItem));
//             }
//         }
//     }
//     else
//     {
//         cerr << "Warning: Skipping line with insufficient data: " << iss.str() << endl;
//     }
// }
template <>
void SheetReader::readType<Paths>(istringstream &iss, Paths &pathsItem)
{
    const regex matcher = regex("^([^,]+),([^,]+),([^,]+)(?:,((?:(?:(?:[^,]+),)*)(?:[^,]+)))?");
    string buffer;
    std::smatch matches;

    // std::cout << "BeforeLoop" << std::endl;

    // Loop over each token separated by the tab character ('\t') in the input string stream (iss)
    while (getline(iss, buffer, '\t'))
    {
        // std::cout << "New path: " << std::endl;
        regex_search(buffer, matches, matcher);
        // Extract and assign the timestamp, origin, and destination from the matched groups
        pathsItem.timestamp = matches[1];
        pathsItem.origin = matches[2];
        pathsItem.destination = matches[3];
        // std::cout << "0: " << matches[0] << " 1: " << matches[1] << " 2: " << matches[2] << " 3: " << matches[3] << " 4: " << matches[4] << std::endl;
        if (matches[4] == "")
            continue;
        std::stringstream ss(matches[4]);
        string pathBuffer;
        while (getline(ss, pathBuffer, ','))
        {
            pathsItem.path.push_back(move(pathBuffer));
        }
        pathsItem.applyChanges();
        // std::cout << pathsItem.to_string() << std::endl;
    }
}

template <>
void SheetReader::readType<MappedRouter>(istringstream &iss, MappedRouter &routerItem)
{
    string id, type;
    double latitude, longitude;
    if (getline(iss, id, ',') &&
        iss >> latitude &&
        iss.ignore() && // Skip the comma
        iss >> longitude &&
        iss.ignore() && // Skip the comma
        getline(iss, type))
    {
        routerItem = MappedRouter(id, latitude, longitude, type);
    }
    else
    {
        cerr << "Warning: Skipping line with insufficient data: " << iss.str() << endl;
    }
}
template <>
void SheetReader::readType<AugmentedLink>(istringstream &iss, AugmentedLink &linkItem)
{
    // cout << "type link" << endl;
    string linkStart, linkEnd;
    double capacity;
    if (getline(iss, linkStart, ',') &&
        getline(iss, linkEnd, ',') &&
        iss >> capacity)
    {
        linkItem = AugmentedLink(linkStart, linkEnd, capacity);
    }
    else
    {
        cerr << "Warning: Skipping line with insufficient data: " << iss.str() << endl;
    }
}
