#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <filesystem>
#include "SheetToGraphConverter/GraphMaker.h"

// Line limit(for ram usage) 0 = unlimited(in theory)

using namespace std;
template <typename T>

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
    std::string directoryPath = std::filesystem::current_path().string().append("/data/");
    int day = 1; // Change this variable to process different days


    // Create an instance of Graphmaker with the complete file path
    Graphmaker GraphOne(directoryPath);

    // Process data for the specified day using the complete file path
    GraphOne.processDataForDay(directoryPath, day);

    return 0;
}
