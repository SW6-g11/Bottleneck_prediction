#include "DinicAlgorithm.h"

using namespace std;

// constant to represent infinity
const double INF = numeric_limits<double>::max();

// DinicAlgorithm::DinicAlgorithm(const vector<Link>& links) {
//     // Construct adjacency list (unordered map) from the provided links
//     for (const Link& Link : links) {
//         AdjecentMap[Link.linkStart].push_back(Link(Link.linkStart, Link.linkEnd, Link.capacity));
//         // If the graph is undirected, uncomment the line below
//         AdjecentMap[Link.linkEnd].push_back(Link(Link.linkEnd, Link.linkStart, Link.capacity));
//     }
// }


// DinicAlgorithm::DinicAlgorithm(const vector<Link>& links) {
//     // Construct adjacency list (unordered map) from the provided links
//     for (const Link& link : links) {
//         AdjecentMap[link.linkStart].push_back(Link(link.linkStart, link.linkEnd, link.capacity));
//         // If the graph is undirected, uncomment the line below
//         AdjecentMap[link.linkEnd].push_back(Link(link.linkEnd, link.linkStart, link.capacity));
//     }
// }


DinicAlgorithm::DinicAlgorithm(const vector<Link>& links) {
    // Construct adjacency list (unordered map) from the provided links
    for (const Link& link : links) {
        // Add the link to the adjacency map
        AdjecentMap[link.linkStart].push_back(link);

        //graph is undirected
        AdjecentMap[link.linkEnd].push_back(link);
    }
}


bool DinicAlgorithm::bfs(const string& source, const string& sink) {
    // initializes/resets parameters
    level.clear();
    queue<string> q;
    q.push(source);
    level[source] = 0;
    cout << "Starting BFS at node: " << source << endl;

    while (!q.empty()) {
        string u = q.front();
        q.pop();
        // For each Link e in the vector of links associated with the current node u in the adjacency list
        for (const Link& e : AdjecentMap[u]) {
            string v = e.linkEnd;
            // level.find(v) checks if the node is in the level map; i.e., has it been visited before. remember: BFS-->DFS
            if (level.find(v) == level.end() && e.capacity > 0) {
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    }
    if (level.find(sink) != level.end()) {
        cout << "Sink node " << sink << " reached!" << endl;
        return true;
    } else {
        cout << "Sink node " << sink << " not reachable!" << endl;
        return false;
    }
}

// returns the minimum capacity of the current augmented path
double DinicAlgorithm::dfs(const string& currentNode, const string& sink, double minCapacity) {
    if (currentNode == sink)
        return minCapacity; //we found the sink! DFS can stop

// iterates over the outgoing links from the current node. 
// the loop uses an index i initialized with the value of NextEdgePointer[u], which represents the next Link to be explored from the adjacency list of node u.
    for (int& i = NextEdgePointer[currentNode]; i < AdjecentMap[currentNode].size(); ++i) {
        Link& e = AdjecentMap[currentNode][i];
        string v = e.linkEnd;
        if (level[v] == level[currentNode] + 1 && e.capacity > 0) {
            double bottleneck = dfs(v, sink, min(minCapacity, e.capacity));
            if (bottleneck > 0) {
                e.capacity -= bottleneck;
                for (Link& backEdge : AdjecentMap[v]) {

                    // checks if the end node of the backward edge (backEdge.linkEnd) is the current node u. 
                    // If it is, it means that this backward edge corresponds to the forward edge (e) that was just used in the augmenting path.
                    //  In this case, the capacity of the backward edge is increased by the bottleneck capacity (bottleneck)
                    if (backEdge.linkEnd == currentNode) {
                        backEdge.capacity += bottleneck;
                        break;
                    }
                }
                cout << "bottleneck : " << bottleneck << endl;
                return bottleneck;
            }
        }
    }
    return 0;
}

double DinicAlgorithm::findMaxFlow(const string& source, const string& sink) {
    double maxFlow = 0.0;
    while (bfs(source, sink)) {
        NextEdgePointer.clear();

        //  iterates over each element (pair) in the AdjecentMap. Each element consists of a node (key) and its corresponding adjacency list (value).
        for (auto& i : AdjecentMap) //auto = no specific type ~generic ish
        //For each node i.first, sets the value of its NextEdgePointer to 0. 
        // This ensures that for each node, the next edge to be explored during DFS is set to the first edge in its adjacency list.
            NextEdgePointer[i.first] = 0; 
        double flow;

        // calls the dfs function to find augmenting paths and update the maximum flow until no more augmenting paths can be found
        // If dfs returns 0, it means no more augmenting paths can be found, and the loop exits
        while ((flow = dfs(source, sink, INF)) > 0) {
            maxFlow += flow;
            cout << "Current maxflow: " << maxFlow << endl;
        }
    }
    cout << "Final Max flow is: " << maxFlow << endl;
    return maxFlow;
}
