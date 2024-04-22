#include "sheetreader.h"
#include "path.h"
#include "link.h"
#include "router.h"
#include "inputverifyer.h"
using namespace std;
template <typename T>


class SheetReader{
    // overloading constructor (have one use the other) gives us an optional input "limit"
    //public: SheetReader(int Limit) {
       // Line limit(for ram usage) 0 = unlimited(in theory)
    //    const int limit = Limit;
    }
    public: SheetReader() {
       // Line limit(for ram usage) 0 = unlimited(in theory)
        Limit defaultValue = 100;
        SheetReader(Limit);
    }
    
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

    void readLinkUtils(istringstream &iss, Linkutils &linkUtilsItem)
    {
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
};
