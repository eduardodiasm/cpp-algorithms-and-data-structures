#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <stdexcept>
#include <utility>
#include <vector>

using namespace std;

constexpr long long INF = numeric_limits<long long>::max();

struct Edge
{
    int to;
    long long weight;
};

struct ShortestPaths
{
    vector<long long> distance;
    vector<int> parent;
};

// Adjacency list with valid IDs 0..V-1. For undirected graphs, add both
// directions. All weights must be nonnegative and shortest distances < INF.
// Lazy min-heap: O(V + E log(E + 1)) time, O(V + E) extra space.
// Unreachable vertices have distance INF and parent -1.
ShortestPaths dijkstra(const vector<vector<Edge>>& graph, int source)
{
    if(source < 0 || static_cast<size_t>(source) >= graph.size())
        throw out_of_range("Invalid source vertex");
    for(const auto& edges : graph)
        for(const Edge& edge : edges)
            if(edge.weight < 0)
                throw invalid_argument("Dijkstra requires nonnegative weights");

    ShortestPaths result{vector<long long>(graph.size(), INF),
                         vector<int>(graph.size(), -1)};
    using Entry = pair<long long, int>;
    priority_queue<Entry, vector<Entry>, greater<Entry>> pending;
    result.distance[source] = 0;
    pending.push({0, source});

    while(!pending.empty())
    {
        auto [distance, vertex] = pending.top();
        pending.pop();
        if(distance != result.distance[vertex])
            continue;
        for(const Edge& edge : graph[vertex])
        {
            // Avoid overflow; INF is reserved for unreachable vertices.
            if(edge.weight >= INF - distance)
                continue;
            long long candidate = distance + edge.weight;
            if(candidate >= result.distance[edge.to])
                continue;
            result.distance[edge.to] = candidate;
            result.parent[edge.to] = vertex;
            pending.push({candidate, edge.to});
        }
    }
    return result;
}

// Uses the unmodified result of dijkstra and a valid target ID.
vector<int> reconstruct_path(const ShortestPaths& paths, int target)
{
    if(paths.distance[target] == INF)
        return {};
    vector<int> path;
    for(int vertex = target; vertex != -1; vertex = paths.parent[vertex])
        path.push_back(vertex);
    reverse(path.begin(), path.end());
    return path;
}

int main()
{
    vector<vector<Edge>> graph = {
        {{1, 10}, {2, 1}, {2, 4}}, {{3, 2}}, {{1, 2}, {3, 8}}, {}, {}};
    auto paths = dijkstra(graph, 0);
    assert((paths.distance == vector<long long>{0, 3, 1, 5, INF}));
    assert((reconstruct_path(paths, 3) == vector<int>{0, 2, 1, 3}));
    assert((reconstruct_path(paths, 0) == vector<int>{0}));
    assert(reconstruct_path(paths, 4).empty());
    auto zero = dijkstra({{{0, 0}, {1, 0}}, {{0, 0}}}, 0);
    assert((zero.distance == vector<long long>{0, 0}));
    assert((reconstruct_path(zero, 1) == vector<int>{0, 1}));
    assert((dijkstra({{}}, 0).distance == vector<long long>{0}));
    auto large = dijkstra({{{1, INF - 2}, {2, 7}}, {{2, 10}}, {}}, 0);
    assert((large.distance == vector<long long>{0, INF - 2, 7}));
    auto wide = dijkstra({{{1, 3000000000LL}}, {{2, 3000000000LL}}, {}}, 0);
    assert(wide.distance[2] == 6000000000LL);

    bool rejected = false;
    try
    {
        dijkstra({{}, {{1, -1}}}, 0);
    }
    catch(const invalid_argument&)
    {
        rejected = true;
    }
    assert(rejected);
    rejected = false;
    try
    {
        dijkstra({}, 0);
    }
    catch(const out_of_range&)
    {
        rejected = true;
    }
    assert(rejected);

    for(size_t vertex = 0; vertex < paths.distance.size(); ++vertex)
    {
        cout << vertex << ": ";
        if(paths.distance[vertex] == INF)
            cout << "unreachable\n";
        else
            cout << paths.distance[vertex] << '\n';
    }
}
