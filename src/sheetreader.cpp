#include "sheetreader.h"
#include "path.h"
#include "link.h"
#include "router.h"
#include "inputverifyer.h"
#include "linkutils.h"
#include "traffic.h"

using namespace std;

template <>
void SheetReader::readType(istringstream &iss, Linkutils &linkUtilsItem)
{
    cout << "type linkutils"<< endl;
    string timestamp, linkStart, linkEnd;
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
template <>
void SheetReader::readType<Paths>(istringstream &iss, Paths &pathsItem)
{

    // Read the timestamp, origin, and destination directly from the file stream
    if (getline(iss, pathsItem.timestamp, ',') &&
        getline(iss, pathsItem.origin, ',') &&
        getline(iss, pathsItem.destination, ','))
    {
        // Read the rest of the columns (nodes in the path)
        string pathNode;
        // pathsItem.path = new vector<string>(); // Manual memory allocation

        while (getline(iss, pathNode, ','))
        {
            // Skip '[' and ']' characters
            if (pathNode.front() == '[')
                pathNode.erase(0, 1);
            if (pathNode.back() == ']')
                pathNode.pop_back();

            // Split the nodes separated by tabs
            istringstream pathStream(pathNode);
            string pathItem;
            int itemCount = 0;
            vector<string> itemPaths;
            while (getline(pathStream, pathItem, '\t'))
            {
                itemPaths.push_back(move(pathItem));
                itemCount++;
                // pathsItem.path.push_back(move(pathItem));
            }

            pathsItem.path.resize(itemCount);
            for (int i = 0; i < itemCount; i++)
            {
                pathsItem.path.push_back(itemPaths[i]);
            }
            itemPaths.clear();
        }
    }
    else
    {
        cerr << "Warning: Skipping line with insufficient data: " << iss.str() << endl;
    }
}
template <>
void SheetReader::readType<Router>(istringstream &iss, Router &routerItem)
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
        routerItem = Router(id, latitude, longitude, type);
    }
    else
    {
        cerr << "Warning: Skipping line with insufficient data: " << iss.str() << endl;
    }
}
template <>
void SheetReader::readType<Link>(istringstream &iss, Link &linkItem)
{
    cout << "type link"<< endl;
    string linkStart, linkEnd;
    double capacity;
    if (getline(iss, linkStart, ',') &&
        getline(iss, linkEnd, ',') &&
        iss >> capacity)
    {
        linkItem = Link(linkStart, linkEnd, capacity);
    }
    else
    {
        cerr << "Warning: Skipping line with insufficient data: " << iss.str() << endl;
    }
}

