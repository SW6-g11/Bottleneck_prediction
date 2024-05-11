#ifndef MAPPEDROUTER
#define MAPPEDROUTER

#include <string>
#include <vector>
#include "link.h"
#include "Router.h"
#include "AugmentedLink.h"

class MappedRouter : public Router
{
private:
    std::vector<AugmentedLink *> inputs;
    std::vector<AugmentedLink *> outputs;

public:
    MappedRouter();
    MappedRouter(const string &id, double latitude, double longitude, const string &type);
    ~MappedRouter();
    void addConnection(AugmentedLink *, bool);
    static void populateMappedRouters(vector<AugmentedLink> links, vector<MappedRouter> &routers);
    static bool compareRouters(const MappedRouter &a, const MappedRouter &b);
    static bool compareRouterToString(const MappedRouter &router, string &b);

    template <typename ARR, typename TARGET>
    static int binarySearch(vector<ARR> arr, int low, unsigned long high, TARGET target, bool (*compareFunction)(ARR &, TARGET));

    static bool isRouterIdSameAsTarget(MappedRouter &a, std::string target);

    std::vector<AugmentedLink *> getOutputs()
    {
        return outputs;
    }
};

#endif