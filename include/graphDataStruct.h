#ifndef graphData
#define graphData
#include <vector>
#include "link.h"
#include "linkutils.h"
#include "path.h"
#include "router.h"
#include "traffic.h"

struct graphData {
    std::vector<Linkutils> linkUtilsData;
    std::vector<Traffic> trafficData;
    std::vector<Paths> pathsData;
    std::vector<Router> routersData;
    std::vector<Link> linksData;
} graphdata;

#endif