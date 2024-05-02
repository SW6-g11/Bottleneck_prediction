#include "graphviz.h"
#include "graphmaker.h"
#include "link.h"
#include "linkutils.h"
#include "path.h"
#include "router.h"
#include "sheetreader.h"
#include "traffic.h"

using namespace std;

void Graphviz::GenerateGraphViz(const vector<Linkutils>& linkUtilsData,
                                const vector<Traffic>& trafficData,
                                const vector<Paths>& pathsData,
                                const vector<Router>& routersData,
                                const vector<Link>& linksData,
                                const string& filename) {
  std::ofstream dotFile(filename);
  dotFile << "graph G {\n";
  // Write routers as nodes
  for (const auto& router : routersData) {
    dotFile << "\t" << router.id << " [label=\"" << router.id
            << "\", shape=circle];\n";
  }

  // Write traffic data as edges with labels
  for (const auto& traffic : trafficData) {
    dotFile << "\t" << traffic.origin << " -- " << traffic.destination
            << " [label=\"" << traffic.avgTraffic << "\", color=red];\n";
  }

  // Write paths data as edges
  for (const auto& path : pathsData) {
    for (size_t i = 0; i < path.path.size() - 1; ++i) {
      dotFile << "\t" << path.path[i] << " -- " << path.path[i + 1]
              << " [style=dashed];\n";
    }
  }

  // Write link utils data as edges with labels
  for (const auto& linkUtils : linkUtilsData) {
    dotFile << "\t" << linkUtils.linkStart << " -- " << linkUtils.linkEnd
            << " [label=\"" << linkUtils.avgUtilization << "\", color=blue];\n";
  }

  // Write links data as edges with labels
  for (const auto& link : linksData) {
    dotFile << "\t" << link.linkStart << " -- " << link.linkEnd << " [label=\""
            << link.capacity << "\", color=green];\n";
  }
  dotFile << "}\n";

  dotFile.close();
}
