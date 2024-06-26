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
    static bool isRouterIdGreaterThanTarget(MappedRouter &a, std::string target);
    static bool isRouterIdSameAsTarget(MappedRouter &a, std::string target);
    static bool alphaNumbericCompare(const string &a, const std::string &b);

public:
    MappedRouter();
    MappedRouter(const string &id, double latitude, double longitude, const string &type);
    ~MappedRouter();
    void addConnection(AugmentedLink *, bool);
    static void populateMappedRouters(vector<AugmentedLink> &links, vector<MappedRouter> &routers);
    static bool compareRouters(const MappedRouter &a, const MappedRouter &b);
    static bool compareRouterToString(const MappedRouter &router, string &b);

    template <typename ARR, typename TARGET>
    static int binarySearch(vector<ARR> arr, int low, unsigned long high, TARGET target, bool (*compareFunction)(ARR &, TARGET), bool (*greaterThanFunction)(ARR &, TARGET));
    std::string to_string() const;

    std::vector<AugmentedLink *> getOutputs()
    {
        return outputs;
    }
    std::vector<AugmentedLink *> getInAndOutputs()
    {
        std::vector<AugmentedLink *> concatenatedResult;
        concatenatedResult.insert(concatenatedResult.end(), inputs.begin(), inputs.end());
        concatenatedResult.insert(concatenatedResult.end(), outputs.begin(), outputs.end());
        return concatenatedResult;
    }

    std::string toString() const { return id; };
};

#endif