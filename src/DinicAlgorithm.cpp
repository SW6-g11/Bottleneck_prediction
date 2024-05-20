#include "DinicAlgorithm.h"
#include <functional>
#include <algorithm>

using namespace std;

// constant to represent infinity
const double INF = numeric_limits<double>::max();

DinicAlgorithm::DinicAlgorithm()
{
}

void DinicAlgorithm::populateDinics(vector<AugmentedLink> &links, vector<MappedRouter> &routers, bool overwrite)
{
    // std::cout << "Populating" << std::endl;

    for (auto &link : links)
    {
        std::cout << "resetting" << std::endl;
        link.flow = 0;
    }

    if (overwrite)
    {
        nodes_.clear();
        arcs_.clear();
    }
    // std::cout << "Populating2" << std::endl;
    // std::cout << "Sizes: R: " << routers.size() << endl;
    routers.erase(std::remove_if(routers.begin(), routers.end(), isEmpty), routers.end());
    if (overwrite)
    {
        MappedRouter::populateMappedRouters(links, routers);
        nodes_ = routers;
    }
    // std::cout << "Sizes: N,R: " << routers.size() << endl;
    applyindices(links);
    arcs_ = deque(links.begin(), links.end());
}
bool DinicAlgorithm::isEmpty(const Router &router)
{
    return router.id == "";
}

void DinicAlgorithm::applyindices(vector<AugmentedLink> &links)
{
    std::unordered_map<std::string, int> positions;
    for (int i = 0; i < nodes_.size(); i++)
    {
        positions.insert(std::pair(nodes_[i].id, i));
    }
    for (int i = 0; i < links.size(); i++)
    {
        links[i].start_ = positions[links[i].linkStart];
        // std::cout << "sta mapping: " << links[i].linkStart << "->" << positions[links[i].linkStart] << std::endl;
        // std::cout << "end mapping: " << links[i].linkEnd << "->" << positions[links[i].linkEnd] << std::endl;
        links[i].end_ = positions[links[i].linkEnd];
    }
}

// returns false if both are found ok
bool DinicAlgorithm::getIndexOfSourceAndSink(int &indexSource, int &indexSink, std::string source, std::string sink)
{
    bool foundSource = false;
    bool foundSink = false;
    // std::cout << "Node size at get: " << nodes_.size() << std::endl;
    for (int i = 0; i < nodes_.size(); i++)
    {
        // std::cout << "Node ID: " << nodes_[i].id << std::endl;
        if (nodes_[i].id == source)
        {
            foundSource = true;
            indexSource = i;
            // std::cout << "indexSource: " << indexSource << std::endl;
        }
        if (nodes_[i].id == sink)
        {
            foundSink = true;
            indexSink = i;
            // std::cout << "indexSink: " << indexSink << std::endl;
        }
        if (foundSource && foundSink)
            return false;
    }
    return true;
}

int DinicAlgorithm::compute_flow(std::string source, std::string sink, bool usePreLoad, bool isCalculatingMincut)
{ // Compute the maximum flow with the Dinic's algorithm
    std::cout << "ComputeFLow is asking for Preload?: " << usePreLoad << std::endl;
    int source_i;
    int sink_i;
    if (getIndexOfSourceAndSink(source_i, sink_i, source, sink))
    {
        std::cerr << "Could not find source or sink" << std::endl;
        return -1;
    }
    // std::cout << "nodes_.size():" << nodes_.size() << std::endl;
    if (nodes_.size() < 1)
    {
        std::cerr << "No nodes in dinics" << std::endl;
        return -1;
    }

    int asd = 0;
    int result = 0;
    while (true)
    {
        asd++;
        // std::cout << "While1" << std::endl;
        //  First divide into layers with a breadth-first search
        std::vector<int> level(nodes_.size(), -1);
        printArr(level, "Level");
        {
            // std::cout << "Source_I: " << source_i << endl;
            std::deque<std::tuple<int, int>> queue(1, std::make_tuple(0, source_i));
            level[source_i] = 0;

            while (queue.size() > 0)
            {
                // std::cout << "While2" << std::endl;
                int current_level;
                // std::cout << "While2.1" << std::endl;
                int current_node_i;
                // std::cout << "While2.2" << std::endl;
                std::tie(current_level, current_node_i) = queue.front(); // Extract the values from queue
                // std::cout << "While2.3" << std::endl;
                queue.pop_front();
                // std::cout << "While2.4" << std::endl;

                // std::cout << "Current_node_i: " << current_node_i << std::endl;
                // std::cout << "Current_node_i: " << nodes_[current_node_i].to_string() << std::endl;
                // std::cout << "outputs.size : " << nodes_[current_node_i].getInAndOutputs().size() << std::endl;
                // std::cout << "Node name : " << nodes_[current_node_i].id << std::endl;

                for (const AugmentedLink *arc : nodes_[current_node_i].getOutputs()) // TODO: getOutputs or getInAndOutputs?
                {
                    // std::cout << "arc: " << arc->toString() << std::endl;
                    // std::cout << "ComputeFLow2 is asking for Preload?: " << usePreLoad << std::endl;

                    if (arc->getRemainingCapacity(current_node_i, usePreLoad, isCalculatingMincut) <= 0)
                    {
                        std::cout << "Node capacity: " << arc->getRemainingCapacity(current_node_i, usePreLoad, isCalculatingMincut) << std::endl;
                        continue;
                    }
                    // std::cout << "For1" << std::endl;

                    int next_i = arc->get_dest(current_node_i);
                    // std::cout << "next_i: " << next_i << std::endl;
                    if (level[next_i] == -1)
                    {
                        std::cout << "level[next_i] = -1" << std::endl;
                        level[next_i] = current_level + 1;
                        queue.push_back(std::make_tuple(current_level + 1, next_i));
                    }
                }
            }
            printArr(level, "Level");
            // std::cout << sink_i << std::endl;
            if (level[sink_i] == -1)
            {
                std::cout << "Path to sink no longer exists, so return" << std::endl;
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
                std::cout << "Returned capacity: " + capacity << std::endl;
                return capacity;
            }

            for (int &i = arc_index[cur_i]; i < (int)nodes_[cur_i].getOutputs().size(); i++)
            {
                // std::cout << "For2" << std::endl;

                AugmentedLink *arc = nodes_[cur_i].getOutputs()[i];
                int next_i = arc->get_dest(cur_i);
                if (arc->getRemainingCapacity(cur_i, usePreLoad, isCalculatingMincut) > 0 && level[cur_i] < level[next_i])
                {
                    int pushed_flow = dfs(next_i, std::min(capacity, arc->getRemainingCapacity(cur_i, usePreLoad, isCalculatingMincut)));
                    if (pushed_flow > 0)
                    {
                        (*arc).addFlow(cur_i, pushed_flow);
                        // std::cout << "Returned pushed flow: " + pushed_flow << std::endl;
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
            // std::cout << "While3" << std::endl;

        } while (pushed_flow > 0);
    }
    return -1;
};

void DinicAlgorithm::findMinCut(string source, vector<int> &level, vector<pair<string, string>> &minCut)
{
    cout << "Start of MinCut" << endl;
    int source_i;
    int sink_i;
    getIndexOfSourceAndSink(source_i, sink_i, source, source);
    // Use BFS to mark all reachable vertices from the source in the residual graph
    vector<bool> visited(nodes_.size(), false);
    deque<int> queue(1, source_i);
    visited[source_i] = true;

    while (!queue.empty())
    {
        int current = queue.front();
        queue.pop_front();

        for (const AugmentedLink *arc : nodes_[current].getOutputs())
        {
            int next_i = arc->get_dest(current);
            if (!visited[next_i] && arc->getRemainingCapacity(current, false, true) > 0)
            {
                visited[next_i] = true;
                queue.push_back(next_i);
            }
        }
    }

    // Find all edges that cross the cut
    for (int i = 0; i < nodes_.size(); ++i)
    {
        if (visited[i])
        {
            for (const AugmentedLink *arc : nodes_[i].getOutputs())
            {
                int next_i = arc->get_dest(i);
                if (!visited[next_i])
                {
                    minCut.push_back({nodes_[i].id, nodes_[next_i].id});
                }
            }
        }
    }
    cout << "end of MinCut" << endl;
}
/*
int DinicAlgorithm::findMinCut2(string source, string &sink, vector<pair<string, string>> &minCut)
{
    int source_i;
    int sink_i;
    getIndexOfSourceAndSink(source_i, sink_i, source, source);
    // Use BFS to mark all reachable vertices from the source in the residual graph
    vector<bool> visited(nodes_.size(), false);
    deque<int> queue(1, source_i);
    visited[source_i] = true;

    while (!queue.empty())
    {
        int current = queue.front();
        queue.pop_front();

        for (const AugmentedLink *arc : nodes_[current].getOutputs())
        {
            int next_i = arc->get_dest(current);
            if (!visited[next_i] && arc->getRemainingCapacity(current, false) > 0)
            {
                visited[next_i] = true;
                queue.push_back(next_i);
            }
        }
    }

    // Find all edges that cross the cut and sum their capacities
    int minCutValue = 0;
    for (int i = 0; i < nodes_.size(); ++i)
    {
        if (visited[i])
        {
            for (const AugmentedLink *arc : nodes_[i].getOutputs())
            {
                int next_i = arc->get_dest(i);
                if (!visited[next_i])
                {
                    minCut.push_back({nodes_[i].id, nodes_[next_i].id});
                    minCutValue += arc->capacity;
                }
            }
        }
    }
    return minCutValue;
}
*/
template <typename T>
void DinicAlgorithm::printArr(const std::vector<T> &arr, const std::string name)
{
    std::string stringResult = name + "=[";
    for (int i = 0; i < arr.size(); i++)
    {
        stringResult += arr[i].to_string();
        if (i < arr.size() - 1)
            stringResult += ",";
    }
    stringResult += "]";
    // std::cout << stringResult << std::endl;
}

void DinicAlgorithm::printArr(const std::vector<int> &arr, const std::string name)
{
    std::string stringResult = name + "=[";
    for (int i = 0; i < arr.size(); i++)
    {
        stringResult += std::to_string(arr[i]);
        if (i < arr.size() - 1)
            stringResult += ",";
    }
    stringResult += "]";
    // std::cout << stringResult << std::endl;
}

vector<MappedRouter> DinicAlgorithm::getNodes()
{
    return nodes_;
}