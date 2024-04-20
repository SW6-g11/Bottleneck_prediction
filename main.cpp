#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <filesystem>

class LinkUtils
{
public:
    std::string timestamp;
    std::string linkStart;
    std::string linkEnd;
    double avgUtilization;

    // Default constructor
    LinkUtils() : timestamp(""), linkStart(""), linkEnd(""), avgUtilization(0.0) {}

    // Constructor with parameters
    LinkUtils(const std::string &timestamp, const std::string &linkStart, const std::string &linkEnd, double avgUtilization)
        : timestamp(timestamp), linkStart(linkStart), linkEnd(linkEnd), avgUtilization(avgUtilization) {}
};

class Traffic
{
public:
    std::string timestamp;
    std::string origin;
    std::string destination;
    double avgTraffic;

    // Default constructor
    Traffic() : timestamp(""), origin(""), destination(""), avgTraffic(0.0) {}

    // Constructor with parameters
    Traffic(const std::string &timestamp, const std::string &origin, const std::string &destination, double avgTraffic)
        : timestamp(timestamp), origin(origin), destination(destination), avgTraffic(avgTraffic) {}
};
//this is a change
int change = 2;
class Paths
{
public:
    std::string timestamp;
    std::string origin;
    std::string destination;
    std::vector<std::string> path; // Changed to a pointer

    // Default constructor
    Paths() : timestamp(""), origin(""), destination(""), path() {}

    // Constructor with parameters
    Paths(const std::string &timestamp, const std::string &origin, const std::string &destination, std::vector<std::string> path)
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
    std::string id;
    double latitude;
    double longitude;
    std::string type;

    // Default constructor
    Router() : id(""), latitude(0.0), longitude(0.0), type("") {}

    // Constructor with parameters
    Router(const std::string &id, double latitude, double longitude, const std::string &type)
        : id(id), latitude(latitude), longitude(longitude), type(type) {}
};

class Link
{
public:
    std::string linkStart;
    std::string linkEnd;
    double capacity;

    // Default constructor
    Link() : linkStart(""), linkEnd(""), capacity(0.0) {}

    // Constructor with parameters
    Link(const std::string &linkStart, const std::string &linkEnd, double capacity)
        : linkStart(linkStart), linkEnd(linkEnd), capacity(capacity) {}
};

template <typename T>
void readData(const std::string &fileName, std::vector<T> &data, void (*readFunction)(std::istringstream &, T &), bool debug)
{
    // std::cout << "Inside function 1 ";
    if (debug)
        std::cout << "Inside function 1 ";
    std::ifstream file(fileName);
    if (debug)
        std::cout << "2 ";
    if (!file)
    {
        std::cout << "Error ";
        std::cerr << "Error: Unable to open file " << fileName << std::endl;
        return;
    }
    if (debug)
        std::cout << "3 ";
    const int bufferSize = 1024; // Adjust buffer size as needed
    if (debug)
        std::cout << "4 ";
    char buffer[bufferSize];
    if (debug)
        std::cout << "5 ";
    int count = 0;
    if (debug)
        std::cout << "6 ";
    while (file.getline(buffer, bufferSize))
    {
        if (debug)
        {
            std::cout << std::to_string(count) + fileName + ": ";
        }
        std::istringstream iss(buffer);
        if (debug)
            std::cout << "1 ";
        T item;
        if (debug)
            std::cout << "2 ";
        readFunction(iss, item);
        if (debug)
            std::cout << "3 ";
        data.push_back(item);
        if (debug)
            std::cout << "4 ";
        count++;
    }
}

void readLinkUtils(std::istringstream &iss, LinkUtils &linkUtilsItem)
{
    std::string timestamp, linkStart, linkEnd;
    double avgUtilization;
    if (std::getline(iss, timestamp, ',') &&
        std::getline(iss, linkStart, ',') &&
        std::getline(iss, linkEnd, ',') &&
        iss >> avgUtilization)
    {
        linkUtilsItem = LinkUtils(timestamp, linkStart, linkEnd, avgUtilization);
    }
    else
    {
        std::cerr << "Warning: Skipping line with insufficient data: " << iss.str() << std::endl;
    }
}

void readTraffic(std::istringstream &iss, Traffic &trafficItem)
{
    std::string timestamp, origin, destination;
    double avgTraffic;
    if (std::getline(iss, timestamp, ',') &&
        std::getline(iss, origin, ',') &&
        std::getline(iss, destination, ',') &&
        iss >> avgTraffic)
    {
        trafficItem = Traffic(timestamp, origin, destination, avgTraffic);
    }
    else
    {
        std::cerr << "Warning: Skipping line with insufficient data: " << iss.str() << std::endl;
    }
}

void readPaths(std::istringstream &iss, Paths &pathsItem)
{

    // Read the timestamp, origin, and destination directly from the file stream
    if (std::getline(iss, pathsItem.timestamp, ',') &&
        std::getline(iss, pathsItem.origin, ',') &&
        std::getline(iss, pathsItem.destination, ','))
    {
        // Read the rest of the columns (nodes in the path)
        std::string pathNode;
        // pathsItem.path = new std::vector<std::string>(); // Manual memory allocation

        while (std::getline(iss, pathNode, ','))
        {

            // Skip '[' and ']' characters
            if (pathNode.front() == '[')
                pathNode.erase(0, 1);
            if (pathNode.back() == ']')
                pathNode.pop_back();

            // Split the nodes separated by tabs
            std::istringstream pathStream(pathNode);
            std::string pathItem;
            int itemCount = 0;
            std::vector<std::string> itemPaths;
            while (std::getline(pathStream, pathItem, '\t'))
            {
                itemPaths.push_back(std::move(pathItem));
                itemCount++;
                // pathsItem.path.push_back(std::move(pathItem));
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
        std::cerr << "Warning: Skipping line with insufficient data: " << iss.str() << std::endl;
    }
}

void readRouters(std::istringstream &iss, Router &routerItem)
{
    std::string id, type;
    double latitude, longitude;
    if (std::getline(iss, id, ',') &&
        iss >> latitude &&
        iss.ignore() && // Skip the comma
        iss >> longitude &&
        iss.ignore() && // Skip the comma
        std::getline(iss, type))
    {
        routerItem = Router(id, latitude, longitude, type);
    }
    else
    {
        std::cerr << "Warning: Skipping line with insufficient data: " << iss.str() << std::endl;
    }
}

void readLinks(std::istringstream &iss, Link &linkItem)
{
    std::string linkStart, linkEnd;
    double capacity;
    if (std::getline(iss, linkStart, ',') &&
        std::getline(iss, linkEnd, ',') &&
        iss >> capacity)
    {
        linkItem = Link(linkStart, linkEnd, capacity);
    }
    else
    {
        std::cerr << "Warning: Skipping line with insufficient data: " << iss.str() << std::endl;
    }
}

void processDataForDay(const std::string &directoryPath, int day)
{
    std::vector<LinkUtils> linkUtilsData;
    std::vector<Traffic> trafficData;
    std::vector<Paths> pathsData;
    std::vector<Router> routersData;
    std::vector<Link> linksData;
    std::cout << "Processing" << std::endl;
    // Read link utilities data
    std::string linkUtilsFileName = directoryPath + "/link-util-day" + std::to_string(day) + ".csv";
    readData(linkUtilsFileName, linkUtilsData, readLinkUtils, false);
    std::cout << "Still Processing" << std::endl;
    // Read flows data
    std::string flowsFileName = directoryPath + "/flow-traffic-day" + std::to_string(day) + ".csv";
    readData(flowsFileName, trafficData, readTraffic, false);
    std::cout << "Still Still Processing" << std::endl;
    // Read paths data
    std::string pathsFileName = directoryPath + "/flow-paths-day" + std::to_string(day) + ".csv";
    readData(pathsFileName, pathsData, readPaths, false);
    std::cout << "Still Still Still Processing" << std::endl;
    // Read routers data
    std::string routersFileName = directoryPath + "/routers.csv";
    readData(routersFileName, routersData, readRouters, false);
    std::cout << "Still Still Still Still Processing" << std::endl;
    // Read links data
    std::string linksFileName = directoryPath + "/links.csv";
    readData(linksFileName, linksData, readLinks, false);
    std::cout << "Still Still Still Still Still Processing" << std::endl;

    int userInput;
    std::cin >> userInput;
}

void printTimestamp()
{
    // Get current time
    std::time_t currentTime = std::time(nullptr);

    // Convert current time to local time
    std::tm *localTime = std::localtime(&currentTime);

    // Format and print the local time
    char timeBuffer[80]; // Buffer to store formatted time
    std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", localTime);
    std::cout << "Current local time: " << timeBuffer << std::endl;
}

void printRouters(const std::vector<Router> &routersData, int numRoutersToPrint)
{
    std::cout << "Printing " << numRoutersToPrint << " routers:" << std::endl;
    int count = 0;
    for (const Router &router : routersData)
    {
        std::cout << "Router ID: " << router.id << ", Latitude: " << router.latitude << ", Longitude: " << router.longitude << ", Type: " << router.type << std::endl;
        count++;
        if (count >= numRoutersToPrint)
        {
            break; // Exit loop after printing desired number of routers
        }
    }
}

int main()
{
    std::string directoryPath = std::filesystem::current_path();
    int day = 1; // Change this variable to process different days

    processDataForDay(directoryPath, day);

    return 0;
}
