#include <cassert>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

// Directed adjacency list, valid vertex IDs 0..V-1.
// Kahn's algorithm: a cycle exists if not all vertices can be removed.
// O(V + E) time, O(V) extra space.
bool has_directed_cycle(const vector<vector<int>>& graph)
{
    vector<int> indegree(graph.size(), 0);
    for(const auto& neighbors : graph)
        for(int neighbor : neighbors)
            ++indegree[neighbor];

    queue<int> pending;
    for(size_t vertex = 0; vertex < graph.size(); ++vertex)
        if(indegree[vertex] == 0)
            pending.push(static_cast<int>(vertex));

    size_t removed = 0;
    while(!pending.empty())
    {
        int vertex = pending.front();
        pending.pop();
        ++removed;
        for(int neighbor : graph[vertex])
            if(--indegree[neighbor] == 0)
                pending.push(neighbor);
    }
    return removed != graph.size();
}

// Undirected adjacency list of (neighbor, edge ID). Each edge has a unique
// ID, shared by its two adjacency entries. Supports parallel edges/self-loops.
// O(V + E) time, O(V) extra space. Edge IDs must be nonnegative.
bool has_undirected_cycle(const vector<vector<pair<int, int>>>& graph)
{
    vector<bool> visited(graph.size(), false);
    for(size_t source = 0; source < graph.size(); ++source)
    {
        if(visited[source])
            continue;
        vector<pair<int, int>> pending = {{static_cast<int>(source), -1}};
        visited[source] = true;
        while(!pending.empty())
        {
            auto [vertex, parent_edge] = pending.back();
            pending.pop_back();
            for(auto [neighbor, edge] : graph[vertex])
            {
                if(edge == parent_edge)
                    continue;
                if(visited[neighbor])
                    return true;
                visited[neighbor] = true;
                pending.push_back({neighbor, edge});
            }
        }
    }
    return false;
}

int main()
{
    assert(!has_directed_cycle({}));
    assert(!has_directed_cycle({{1, 2}, {2}, {}}));
    assert(has_directed_cycle({{}, {2}, {1}}));
    assert(has_directed_cycle({{0}}));
    assert(!has_directed_cycle({{1, 1}, {}}));
    assert(!has_undirected_cycle({}));
    assert(!has_undirected_cycle({{{1, 0}}, {{0, 0}}, {}}));
    assert(has_undirected_cycle({{{0, 0}, {0, 0}}}));
    assert(has_undirected_cycle({{{1, 0}, {1, 1}}, {{0, 0}, {0, 1}}}));
    assert(has_undirected_cycle({{}, {{2, 0}, {3, 2}},
                               {{1, 0}, {3, 1}}, {{2, 1}, {1, 2}}}));
    cout << "Cycle detection checks passed\n";
}
