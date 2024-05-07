#include "graphviz.h"
#include "graphmaker.h"
#include "link.h"
#include "linkutils.h"
#include "path.h"
#include "router.h"
#include "sheetreader.h"
#include "traffic.h"
#include <iostream>
//#include "../Graphviz/include/graphviz/cgraph.h"
//#include "../Graphviz/include/graphviz/gvc.h"
//#include "../Graphviz/include/graphviz/xdot.h"

using namespace std;

void Graphviz::GenerateGraphViz(const string& filename) {
  Graphmaker graphTwo;
  const vector<Linkutils>& linkUtilsData = graphTwo.getLinkUtilsData();
  const vector<Traffic>& trafficData = graphTwo.getTrafficData();
  const vector<Paths>& pathsData = graphTwo.getPathsData();
  const vector<Router>& routersData = graphTwo.getRoutersData();
  const vector<Link>& linksData = graphTwo.getLinksData();

  std::ofstream dotFile(filename);

  // Check if the stream is open and ready for writing
  if (!dotFile.is_open()) {
    std::cerr << "Error: Failed to open file " << filename << std::endl;
    return; // Return from the function if opening the file failed
  }

  dotFile << "graph G {\n";
  cout << "Write routers as nodes" << endl;
  // Write routers as nodes
  for (const auto& router : routersData) {
    dotFile << "\t" << router.id << " [label=\"" << router.id << "\", shape=circle];\n";
  }
  cout << "Write traffic data as edges with labels" << endl;
  // Write traffic data as edges with labels
  for (const auto& traffic : trafficData) {
    dotFile << "\t" << traffic.origin << " -- " << traffic.destination << " [label=\"" << traffic.avgTraffic << "\", color=red];\n";
  }
  cout << "Write paths data as edges" << endl;
  // Write paths data as edges
  for (const auto& path : pathsData) {
    for (size_t i = 0; i < path.path.size() - 1; ++i) {
      dotFile << "\t" << path.path[i] << " -- " << path.path[i + 1] << " [style=dashed];\n";
    }
  }

  if (dotFile.fail()) {
    std::cerr << "Error: Failed to write to file " << filename << std::endl;
    dotFile.close(); // Close the file stream
    return; // Return from the function if writing to the file failed
  }

  cout << "Write link utils data as edges with labels" << endl;
  // Write link utils data as edges with labels
  for (const auto& linkUtils : linkUtilsData) {
    dotFile << "\t" << linkUtils.linkStart << " -- " << linkUtils.linkEnd << " [label=\"" << linkUtils.avgUtilization << "\", color=blue];\n";
  }

  if (dotFile.fail()) {
    std::cerr << "Error: Failed to write to file " << filename << std::endl;
    dotFile.close(); // Close the file stream
    return; // Return from the function if writing to the file failed
  }
  cout << "Write links data as edges with labels" << endl;
  // Write links data as edges with labels
  for (const auto& link : linksData) {
    dotFile << "\t" << link.linkStart << " -- " << link.linkEnd << " [label=\"" << link.capacity << "\", color=green];\n";
  }
  dotFile << "}\n";

  dotFile.close();

  if (dotFile.fail()) {
    std::cerr << "Error: Failed to write to file " << filename << std::endl;
    dotFile.close(); // Close the file stream
    return; // Return from the function if writing to the file failed
  }
}
