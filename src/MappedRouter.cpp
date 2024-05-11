#include "MappedRouter.h"
#include <algorithm>
#include <iostream>

MappedRouter::MappedRouter() {}

MappedRouter::MappedRouter(const string &id, double latitude, double longitude, const string &type) : Router(id, latitude, longitude, type)
{
}

MappedRouter::~MappedRouter()
{
}

void MappedRouter::addConnection(AugmentedLink *link, bool isInput)
{
    if (isInput)
    {
        inputs.push_back(link);
    }
    else
    {
        outputs.push_back(link);
    }
}

void MappedRouter::populateMappedRouters(vector<AugmentedLink> links, vector<MappedRouter> &routers)
{
    std::sort(routers.begin(), routers.end(), compareRouters);
    for (auto &link : links)
    {
        /*const auto placeStart = std::lower_bound(routers.begin(), routers.end(), link.start, [](const AugmentedLink &a, const std::string &b)
                                                 { return a.start < b; });
        const auto placeEnd = std::lower_bound(routers.begin(), routers.end(), link.start,
                                               [](AugmentedLink &a, const std::string &b)
                                               {
                                                   return a.start < b;
                                               });
        const auto placeStart = placeEnd;
        if (placeStart == routers.end() || placeEnd == routers.end())
        {
            std::cerr << "Invalid link found, router not found" << link.start << link.end << std::endl;
            continue;
        }
        const int indexStart = routers.begin() - placeStart;
        const int indexEnd = routers.begin() - placeEnd;
        std::cout << "index is: " << indexStart << " " << indexEnd << std::endl;*/
        int indexStart = binarySearch(routers, 0, routers.size() - 1, link.start, &isRouterIdSameAsTarget);
        int indexEnd = binarySearch(routers, 0, routers.size() - 1, link.end, &isRouterIdSameAsTarget);

        if (routers[indexStart].id != link.start || routers[indexEnd].id != link.end)
        {
            std::cerr << "Invalid link found, router not found" << link.start << link.end << std::endl;
            continue;
        }
        routers[indexStart].outputs.push_back(&link);
        routers[indexEnd].inputs.push_back(&link);
    }
}

bool MappedRouter::compareRouterToString(const MappedRouter &router, string &b)
{
    return router.id == b;
}

bool MappedRouter::compareRouters(const MappedRouter &a, const MappedRouter &b)
{
    for (int i = 0; i < a.id.length() && i < b.id.length(); i++)
    {
        if (a.id[i] != b.id[i])
        {
            return a.id[i] > b.id[i];
        }
    }
    return a.id.length() - b.id.length();
}

template <typename ARR, typename TARGET>
int MappedRouter::binarySearch(vector<ARR> arr, int low, unsigned long high, TARGET target, bool (*compareFunction)(ARR &, TARGET))
{
    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        // Check if x is present at mid
        if (isRouterIdSameAsTarget(arr[mid], target))
            return mid;

        // If x greater, ignore left half
        if (isRouterIdSameAsTarget(arr[mid], target))
            low = mid + 1;

        // If x is smaller, ignore right half
        else
            high = mid - 1;
    }

    // If we reach here, then element was not present
    return -1;
}

bool MappedRouter::isRouterIdSameAsTarget(MappedRouter &a, std::string target)
{
    return a.id == target;
}