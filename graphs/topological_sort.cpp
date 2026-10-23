#include <cassert>
#include <iostream>
#include <optional>
#include <queue>
#include <vector>

using namespace std;

// Directed adjacency list, valid vertex IDs 0..V-1.
// Kahn's algorithm, O(V + E) time and O(V) extra space.
// nullopt means a cycle exists; an empty graph has a valid empty ordering.
optional<vector<int>> topological_sort(const vector<vector<int>>& graph)
{
    vector<int> indegree(graph.size(), 0);
    for(const auto& neighbors : graph)
        for(int neighbor : neighbors)
            ++indegree[neighbor];

    queue<int> pending;
    for(size_t vertex = 0; vertex < graph.size(); ++vertex)
        if(indegree[vertex] == 0)
            pending.push(static_cast<int>(vertex));

    vector<int> order;
    while(!pending.empty())
    {
        int vertex = pending.front();
        pending.pop();
        order.push_back(vertex);
        for(int neighbor : graph[vertex])
            if(--indegree[neighbor] == 0)
                pending.push(neighbor);
    }
    if(order.size() != graph.size())
        return nullopt;
    return order;
}

int main()
{
    vector<vector<int>> graph = {{2}, {2}, {3}, {}, {}};
    auto order = topological_sort(graph);
    assert(order && order->size() == graph.size());
    vector<int> position(graph.size(), -1);
    for(size_t index = 0; index < order->size(); ++index)
    {
        assert(position[(*order)[index]] == -1);
        position[(*order)[index]] = static_cast<int>(index);
    }
    for(size_t vertex = 0; vertex < graph.size(); ++vertex)
        for(int neighbor : graph[vertex])
            assert(position[vertex] < position[neighbor]);
    auto empty = topological_sort({});
    assert(empty && empty->empty());
    assert(!topological_sort({{0}}));
    assert(!topological_sort({{}, {2}, {1}}));
    assert(topological_sort({{1, 1}, {}}));
    for(int vertex : *order)
        cout << vertex << ' ';
    cout << '\n';
}
