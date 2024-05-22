#ifndef GRAPHDATASTRUCT
#define GRAPHDATASTRUCT
#include <vector>
#include "link.h"
#include "Linkutils.h"
#include "Path.h"
#include "Router.h"
#include "Traffic.h"
#include "MappedRouter.h"

struct graphDataStruct
{
  std::vector<Linkutils> linkUtilsData;
  std::vector<Traffic> trafficData;
  std::vector<Paths> pathsData;
  // std::vector<Router> routersData;
  // std::vector<Link> linksData;
  std::vector<AugmentedLink> Augmentedlinks;
  std::vector<MappedRouter> MappedRouterVector;
  graphDataStruct()
      : linkUtilsData(),
        trafficData(),
        pathsData(),
        Augmentedlinks(),
        MappedRouterVector()
  {
  }
};

#endif