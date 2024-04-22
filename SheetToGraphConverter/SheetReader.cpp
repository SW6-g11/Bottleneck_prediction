
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <filesystem>
#include <iostream>
#include <typeinfo>
#include "SheetReader.h"

using namespace std;

template <typename T>
// generic read function, calls the correct specific read function based on vectors type
void SheetReader::readData(const string &fileName, vector<T> &data, bool debug) {
    // cout << "Inside function 1 ";
    if (debug)
        cout << "Inside function 1 ";
    ifstream file(fileName);
    if (debug)
        cout << "2 ";
    if (!file)
    {
        cout << "Error ";
        cerr << "Error: Unable to open file " << fileName << endl;
        return;
    }
    if (debug)
        cout << "3 ";
    const int bufferSize = 1024; // Adjust buffer size as needed
    if (debug)
        cout << "4 ";
    char buffer[bufferSize];
    if (debug)
        cout << "5 ";
    int count = 0;
    if (debug)
        cout << "6 ";
    int i = 0;
    while (file.getline(buffer, bufferSize) && i > 0 && i < limit)
    {
        i++;
        if (debug)
        {
            cout << to_string(count) + fileName + ": ";
        }
        istringstream iss(buffer);
        T item;
        // switch (typeid(T))

        // {
        // case typeid(Linkutils):
        //     readLinkUtils(iss, item);
        //     break;
        // case typeid(Traffic):
        //     readTraffic(iss, item);
        //     break;
        // case typeid(Paths):
        //     readPaths(iss, item);
        //     break;
        // case typeid(Router):
        //     readRouters(iss, item);
        //     break;
        // case typeid(Link):
        //     readLinks(iss, item);
        //     break;
        // }
        if (typeid(T) == typeid(Linkutils))
        {
            readLinkUtils(iss, item);
        }
        else if (typeid(T) == typeid(Traffic))
        {
            readTraffic(iss, item);
        }
        else if (typeid(T) == typeid(Paths))
        {
            readPaths(iss, item);
        }
        else if (typeid(T) == typeid(Router))
        {
            readRouters(iss, item);
        }
        else if (typeid(T) == typeid(Link))
        {
            readLinks(iss, item);
        }
        data.push_back(item);
        count++;
    }
}

void SheetReader::readLinkUtils(istringstream &iss, Linkutils &linkUtilsItem) {
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


void SheetReader::readTraffic(istringstream &iss, Traffic &trafficItem) {
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

void SheetReader::readPaths(istringstream &iss, Paths &pathsItem)
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


void SheetReader::readRouters(istringstream &iss, Router &routerItem)
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

void SheetReader::readLinks(istringstream &iss, Link &linkItem)
{
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
