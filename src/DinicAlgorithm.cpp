#include "DinicAlgorithm.h"
#include <functional>

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

DinicAlgorithm::DinicAlgorithm()
{
}
void DinicAlgorithm::PopulateAdjecencymap(const vector<AugmentedLink> &links, vector<MappedRouter> &routers)
{
    MappedRouter::populateMappedRouters(links, routers);
    applyindices();
}

/*
double computeFlow(MappedRouter source, MappedRouter sink)
{
    double CurrentFLow = 0;
    bool morePathsExists = true;
    while (!morePathsExists)
    {
        // First divide into layers with a breadth-first search
        std::vector<int> level(MappedRouterVector.size(), -1);
        {
            std::deque<std::tuple<int, int>> queue(1, std::make_tuple(0, source.id));
            level[source.id] = 0;
            while (queue.size() > 0)
            {
                int currentLvl;
                string currentRouter;
                std::tie(currentLvl, currentRouter) = queue.front; // initialize currentLvl and currentRouter to be the values at the front of the queue
                queue.pop_front();

                // for each link from this router, get connected routers
                for (Link *link : currentnode.outputs; i++)
                    string nextrouter = currentRouter.outputs[i].linkEnd;
                if (level[nextrouter] == -1)
                {
                    level[nextrouter] = currentLvl + 1;
                    queu.push_back(std::make_tuple(currentLvl + 1, nextrouter));
                }
            }
        }
*/
void DinicAlgorithm::applyindices()
{
    std::unordered_map<std::string, int> positions;
    for (int i = 0; i < nodes_.size(); i++)
    {
        positions.insert(std::pair(nodes_[i].id, i));
    }
    for (int i = 0; i < arcs_.size(); i++)
    {
        arcs_[i].start_ = positions[arcs_[i].start];
        arcs_[i].end_ = positions[arcs_[i].end];
    }
}

int DinicAlgorithm::compute_flow(int source_i, int sink_i)
{ // Compute the maximum flow with the Dinic's algorithm
    int result = 0;
    while (1)
    {
        // First divide into layers with a breadth-first search
        std::vector<int> level(nodes_.size(), -1);
        {
            std::deque<std::tuple<int, int>> queue(1, std::make_tuple(0, source_i));
            level[source_i] = 0;

            while (queue.size() > 0)
            {
                int cur_level;
                int cur_node_i;
                std::tie(cur_level, cur_node_i) = queue.front(); // Extract the values from queue
                queue.pop_front();

                for (const AugmentedLink *arc : nodes_[cur_node_i].getOutputs())
                    if (arc->getRemainingCapacity(cur_node_i) > 0)
                    {
                        int next_i = arc->get_dest(cur_node_i);
                        if (level[next_i] == -1)
                        {
                            level[next_i] = cur_level + 1;
                            queue.push_back(std::make_tuple(cur_level + 1, next_i));
                        }
                    }
            }

            if (level[sink_i] == -1)
            {
                return result; // Path to sink no longer exists, so return
            }
        }

        // Now perform DFS to push through the blocking flow
        // Since due to leveling we never push back flow, we can speed up DFS by remembering arc iteration indices
        std::vector<int> arc_index(nodes_.size(), 0);

        std::function<int(int, int)> dfs = [&](int cur_i, int capacity)
        {
            if (cur_i == sink_i)
            {
                return capacity;
            }

            for (int &i = arc_index[cur_i]; i < (int)nodes_[cur_i].getOutputs().size(); i++)
            {
                AugmentedLink *arc = nodes_[cur_i].getOutputs()[i];
                int next_i = arc->get_dest(cur_i);
                if (arc->getRemainingCapacity(cur_i) > 0 && level[cur_i] < level[next_i])
                {
                    int pushed_flow = dfs(next_i, std::min(capacity, arc->getRemainingCapacity(cur_i)));
                    if (pushed_flow > 0)
                    {
                        (*arc).addFlow(cur_i, pushed_flow);
                        return pushed_flow;
                    }
                }
            }
            return 0;
        };
        int pushed_flow;
        do
        {
            pushed_flow = dfs(source_i, std::numeric_limits<int>::max());
            result += pushed_flow;
        } while (pushed_flow > 0);
    }
}
// void DinicAlgorithm::PopulateAdjecencymap(const vector<Link> &links)
// {
//     if (adjecentMapIsPopulated)
//         return;
//     // Construct adjacency list (unordered map) from the provided links
//     for (const Link &link : links)
//     {
//         // Add the link to the adjacency map
//         AdjecentMap[link.linkStart].push_back(link);

//         // graph is undirected
//         AdjecentMap[link.linkEnd].push_back(link);
//     }

//     adjecentMapIsPopulated = true;
// }

// bool DinicAlgorithm::bfs(const string &source, const string &sink)
// {
//     // initializes/resets parameters
//     level.clear();
//     queue<string> q;
//     q.push(source);
//     level[source] = 0;
//     cout << "Starting BFS at node: " << source << endl;

//     while (!q.empty())
//     {
//         string queFront = q.front();
//         q.pop();
//         // For each Link link in the vector of links associated with the current node queFront in the adjacency list
//         for (const Link &link : AdjecentMap[queFront])
//         {
//             cout << "looping bfs in adjecencymap at link  " << link.linkStart << link.linkEnd << endl;
//             string linkEnd = link.linkEnd;
//             // level.find(linkEnd) checks if the node is in the level map; i.link., has it been visited before. remember: BFS-->DFS
//             if (level.find(linkEnd) == level.end() && link.capacity > 0)
//             {
//                 level[linkEnd] = level[queFront] + 1;
//                 q.push(linkEnd);
//             }
//         }
//     }
//     if (level.find(sink) != level.end())
//     {
//         cout << "Sink node " << sink << " reached!" << endl;
//         return true;
//     }
//     else
//     {
//         cout << "Sink node " << sink << " not reachable!" << endl;
//         return false;
//     }
// }

// // returns the minimum capacity of the current augmented path
// double DinicAlgorithm::dfs(const string &currentNode, const string &sink, double minCapacity)
// {
//     if (currentNode == sink)
//         return minCapacity; // we found the sink! DFS can stop

//     // iterates over the outgoing links from the current node.
//     // the loop uses an index i initialized with the value of NextEdgePointer[queFront], which represents the next Link to be explored from the adjacency list of node queFront.
//     for (int &i = NextEdgePointer[currentNode]; i < AdjecentMap[currentNode].size(); ++i)
//     {
//         Link &link = AdjecentMap[currentNode][i];
//         string linkEnd = link.linkEnd;
//         cout << "Running dfs on link " << link.linkStart << "," << link.linkEnd << endl;
//         if (level[linkEnd] == level[currentNode] + 1 && link.capacity > 0)
//         {
//             double bottleneck = dfs(linkEnd, sink, min(minCapacity, link.capacity));
//             if (bottleneck > 0)
//             {
//                 cout << "bottleneck (by dfs) found: " << bottleneck << endl;
//                 link.capacity -= bottleneck;
//                 for (Link &backEdge : AdjecentMap[linkEnd])
//                 {

//                     // checks if the end node of the backward edge (backEdge.linkEnd) is the current node queFront.
//                     // If it is, it means that this backward edge corresponds to the forward edge (link) that was just used in the augmenting path.
//                     //  In this case, the capacity of the backward edge is increased by the bottleneck capacity (bottleneck)
//                     if (backEdge.linkEnd == currentNode)
//                     {
//                         backEdge.capacity += bottleneck;
//                         cout << "additional backedge capacity found, now at:  " << backEdge.capacity << endl;
//                         break;
//                     }
//                 }
//                 cout << "bottleneck : " << bottleneck << endl;
//                 return bottleneck;
//             }
//         }
//     }
//     return 0;
// }

// double DinicAlgorithm::findMaxFlow(const string &source, const string &sink)
// {
//     cout << "Running findMaxFlow from: " << source << " to " << sink << endl;
//     if (AdjecentMap.empty())
//     {
//         throw "AdjecentMap Empty";
//     }
//     double maxFlow = 0.0;
//     while (bfs(source, sink))
//     {
//         NextEdgePointer.clear();

//         //  iterates over each element (pair) in the AdjecentMap. Each element consists of a node (key) and its corresponding adjacency list (value).
//         for (auto &i : AdjecentMap) // auto = no specific type ~generic ish
//             // For each node i.first, sets the value of its NextEdgePointer to 0.
//             //  This ensures that for each node, the next edge to be explored during DFS is set to the first edge in its adjacency list.
//             NextEdgePointer[i.first] = 0;
//         double flow;

//         // calls the dfs function to find augmenting paths and update the maximum flow until no more augmenting paths can be found
//         // If dfs returns 0, it means no more augmenting paths can be found, and the loop exits
//         while ((flow = dfs(source, sink, INF)) > 0)
//         {
//             cout << "First maxflow: " << maxFlow << endl;
//             maxFlow += flow;
//             cout << "Current flow: " << flow << endl;
//             std::cout << std::fixed << "Current maxflow: " << maxFlow << endl;
//         }
//     }
//     cout << "Final Max flow is: " << maxFlow << endl;
//     return maxFlow;
// }
