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

void MappedRouter::populateMappedRouters(vector<AugmentedLink> &links, vector<MappedRouter> &routers)
{
    std::sort(routers.begin(), routers.end(), compareRouters);
    std::cout << "Link Size: " << links.size() << std::endl;
    for (auto &router : routers)
    {
        router.outputs.clear();
        router.inputs.clear();
    }
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
        int indexStart = binarySearch(routers, 0, routers.size() - 1, link.linkStart, &isRouterIdSameAsTarget, isRouterIdGreaterThanTarget);
        int indexEnd = binarySearch(routers, 0, routers.size() - 1, link.linkEnd, &isRouterIdSameAsTarget, isRouterIdGreaterThanTarget);

        if (routers[indexStart].id != link.linkStart || routers[indexEnd].id != link.linkEnd)
        {
            std::cerr << "Invalid link found, router not found: " << link.linkStart << link.linkEnd << std::endl;
            // std::cout << "Invalid link found, router not found: " << link.linkStart << link.linkEnd << std::endl;
            continue;
        }
        if (indexStart == -1)
        {
            std::cerr << "RouterStart not found" << std::endl;
            // std::cout << "RouterStart not found" << std::endl;
        }
        if (indexEnd == -1)
        {
            std::cerr << "RouterEnd not found" << std::endl;
            // std::cout << "RouterEnd not found" << std::endl;
        }
        // std::cout << "indexStart: " << indexStart << std::endl;
        // std::cout << "indexEnd: " << indexEnd << std::endl;
        // std::cout << "Populated Mappedrouter " << routers[indexStart].id << " and " << routers[indexEnd].id << std::endl;
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
int MappedRouter::binarySearch(vector<ARR> arr, int low, unsigned long high, TARGET target, bool (*compareFunction)(ARR &, TARGET), bool (*greaterThanFunction)(ARR &, TARGET))
{
    // std::cout << "Searching for: " << target << std::endl;
    while (low <= high)
    {

        int mid = low + (high - low) / 2;
        // std::cout << "low,mid,high: " << low << "," << mid << "," << high << std::endl;

        // Check if x is present at mid
        if (compareFunction(arr[mid], target))
        {
            std::cout << "Found at: " << mid << std::endl;
            return mid;
        }

        // If x greater, ignore left half
        if (greaterThanFunction(arr[mid], target))
        {
            // std::cout << "greater " << std::endl;
            low = mid + 1;
        }
        // If x is smaller, ignore right half
        else
        {
            // std::cout << "smaller " << std::endl;
            high = mid - 1;
        }
    }

    // If we reach here, then element was not present
    std::cout << "Not found" << std::endl;
    return -1;
}

bool MappedRouter::isRouterIdSameAsTarget(MappedRouter &a, std::string target)
{
    return a.id == target;
}

bool MappedRouter::isRouterIdGreaterThanTarget(MappedRouter &a, std::string target)
{
    // std::cout << "asd: " << (a.id > target) << std::endl;
    return a.id > target;
}

std::string MappedRouter::to_string() const
{
    std::string result = "Router: " + id + " inputs=[";
    for (int i = 0; i < inputs.size(); i++)
    {
        result += inputs[i]->to_string();
        if (i < inputs.size() - 1)
            result += ",";
    }
    result += "], outputs=[";
    for (int i = 0; i < outputs.size(); i++)
    {
        result += outputs[i]->to_string();
        if (i < outputs.size() - 1)
            result += ",";
    }
    result += "]";
    return result;
}