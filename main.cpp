#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <filesystem>

// Line limit(for ram usage) 0 = unlimited(in theory)
const int limit = 1000;

using namespace std;

class LinkUtils
{
public:
    string timestamp;
    string linkStart;
    string linkEnd;
    double avgUtilization;

    // Default constructor
    LinkUtils() : timestamp(""), linkStart(""), linkEnd(""), avgUtilization(0.0) {}

    // Constructor with parameters
    LinkUtils(const string &timestamp, const string &linkStart, const string &linkEnd, double avgUtilization)
        : timestamp(timestamp), linkStart(linkStart), linkEnd(linkEnd), avgUtilization(avgUtilization) {}
};

class Traffic
{
public:
    string timestamp;
    string origin;
    string destination;
    double avgTraffic;

    // Default constructor
    Traffic() : timestamp(""), origin(""), destination(""), avgTraffic(0.0) {}

    // Constructor with parameters
    Traffic(const string &timestamp, const string &origin, const string &destination, double avgTraffic)
        : timestamp(timestamp), origin(origin), destination(destination), avgTraffic(avgTraffic) {}
};

class Paths
{
public:
    string timestamp;
    string origin;
    string destination;
    vector<string> path; // Changed to a pointer

    // Default constructor
    Paths() : timestamp(""), origin(""), destination(""), path() {}

    // Constructor with parameters
    Paths(const string &timestamp, const string &origin, const string &destination, vector<string> path)
        : timestamp(timestamp), origin(origin), destination(destination), path(path) {}

    // Destructor
    ~Paths()
    {
        // delete path;
    }
};

class Router
{
public:
    string id;
    double latitude;
    double longitude;
    string type;

    // Default constructor
    Router() : id(""), latitude(0.0), longitude(0.0), type("") {}

    // Constructor with parameters
    Router(const string &id, double latitude, double longitude, const string &type)
        : id(id), latitude(latitude), longitude(longitude), type(type) {}
};

class Link
{
public:
    string linkStart;
    string linkEnd;
    double capacity;

    // Default constructor
    Link() : linkStart(""), linkEnd(""), capacity(0.0) {}

    // Constructor with parameters
    Link(const string &linkStart, const string &linkEnd, double capacity)
        : linkStart(linkStart), linkEnd(linkEnd), capacity(capacity) {}
};

template <typename T>
void readData(const string &fileName, vector<T> &data, void (*readFunction)(istringstream &, T &), bool debug)
{
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
        readFunction(iss, item);
        data.push_back(item);
        count++;
    }
}

void readLinkUtils(istringstream &iss, LinkUtils &linkUtilsItem)
{
    string timestamp, linkStart, linkEnd;
    double avgUtilization;
    if (getline(iss, timestamp, ',') &&
        getline(iss, linkStart, ',') &&
        getline(iss, linkEnd, ',') &&
        iss >> avgUtilization)
    {
        linkUtilsItem = LinkUtils(timestamp, linkStart, linkEnd, avgUtilization);
    }
    else
    {
        cerr << "Warning: Skipping line with insufficient data: " << iss.str() << endl;
    }
}

void readTraffic(istringstream &iss, Traffic &trafficItem)
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

void readPaths(istringstream &iss, Paths &pathsItem)
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

void readRouters(istringstream &iss, Router &routerItem)
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

void readLinks(istringstream &iss, Link &linkItem)
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

void processDataForDay(const string &directoryPath, int day)
{
    vector<LinkUtils> linkUtilsData;
    vector<Traffic> trafficData;
    vector<Paths> pathsData;
    vector<Router> routersData;
    vector<Link> linksData;
    cout << "Processing" << endl;
    // Read link utilities data
    string linkUtilsFileName = directoryPath + "/link-util-day" + to_string(day) + ".csv";
    readData(linkUtilsFileName, linkUtilsData, readLinkUtils, false);
    cout << "Still Processing" << endl;
    // Read flows data
    string flowsFileName = directoryPath + "/flow-traffic-day" + to_string(day) + ".csv";
    readData(flowsFileName, trafficData, readTraffic, false);
    cout << "Still Still Processing" << endl;
    // Read paths data
    string pathsFileName = directoryPath + "/flow-paths-day" + to_string(day) + ".csv";
    readData(pathsFileName, pathsData, readPaths, false);
    cout << "Still Still Still Processing" << endl;
    // Read routers data
    string routersFileName = directoryPath + "/routers.csv";
    readData(routersFileName, routersData, readRouters, false);
    cout << "Still Still Still Still Processing" << endl;
    // Read links data
    string linksFileName = directoryPath + "/links.csv";
    readData(linksFileName, linksData, readLinks, false);
    cout << "Still Still Still Still Still Processing" << endl;

    cout << "Done" << endl;

    int userInput;
    cin >> userInput;
}

void printTimestamp()
{
    // Get current time
    time_t currentTime = time(nullptr);

    // Convert current time to local time
    tm *localTime = localtime(&currentTime);

    // Format and print the local time
    char timeBuffer[80]; // Buffer to store formatted time
    strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", localTime);
    cout << "Current local time: " << timeBuffer << endl;
}

void printRouters(const vector<Router> &routersData, int numRoutersToPrint)
{
    cout << "Printing " << numRoutersToPrint << " routers:" << endl;
    int count = 0;
    for (const Router &router : routersData)
    {
        cout << "Router ID: " << router.id << ", Latitude: " << router.latitude << ", Longitude: " << router.longitude << ", Type: " << router.type << endl;
        count++;
        if (count >= numRoutersToPrint)
        {
            break; // Exit loop after printing desired number of routers
        }
    }
}

int main()
{
    string directoryPath = filesystem::current_path();
    directoryPath += "/data/";
    int day = 1; // Change this variable to process different days

    processDataForDay(directoryPath, day);

    return 0;
}
