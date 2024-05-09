#ifndef GRAPHDATASTRUCT
#define GRAPHDATASTRUCT
#include <vector>
#include "link.h"
#include "linkutils.h"
#include "path.h"
#include "router.h"
#include "traffic.h"

struct graphDataStruct
{
  std::vector<Linkutils> linkUtilsData;
  std::vector<Traffic> trafficData;
  std::vector<Paths> pathsData;
  std::vector<Router> routersData;
  std::vector<Link> linksData;
  std::vector<Link> Augmentedlinks;
  graphDataStruct()
      : linkUtilsData(),
        trafficData(),
        pathsData(),
        routersData(),
        linksData(),
        Augmentedlinks() {}
};

#endif