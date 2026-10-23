#include <cassert>
#include <iostream>
#include <optional>
#include <queue>
#include <vector>

using namespace std;

// Undirected adjacency list (both directions), valid vertex IDs 0..V-1.
// O(V + E) time, O(V) extra space. Handles disconnected graphs.
// Returns colors 0/1, or nullopt if an odd cycle exists.
optional<vector<int>> bipartite_coloring(const vector<vector<int>>& graph)
{
    vector<int> color(graph.size(), -1);
    for(size_t source = 0; source < graph.size(); ++source)
    {
        if(color[source] != -1)
            continue;
        queue<int> pending;
        pending.push(static_cast<int>(source));
        color[source] = 0;
        while(!pending.empty())
        {
            int vertex = pending.front();
            pending.pop();
            for(int neighbor : graph[vertex])
            {
                if(color[neighbor] == -1)
                {
                    color[neighbor] = 1 - color[vertex];
                    pending.push(neighbor);
                }
                else if(color[neighbor] == color[vertex])
                    return nullopt;
            }
        }
    }
    return color;
}

int main()
{
    vector<vector<int>> graph = {{1, 3}, {0, 2}, {1, 3}, {0, 2}, {}};
    auto color = bipartite_coloring(graph);
    assert(color && color->size() == graph.size());
    for(size_t vertex = 0; vertex < graph.size(); ++vertex)
        for(int neighbor : graph[vertex])
            assert((*color)[vertex] != (*color)[neighbor]);
    auto empty = bipartite_coloring({});
    assert(empty && empty->empty());
    assert(!bipartite_coloring({{0}}));
    assert(!bipartite_coloring({{}, {2, 3}, {1, 3}, {1, 2}}));
    assert(bipartite_coloring({{1, 1}, {0, 0}}));
    for(int value : *color)
        cout << value << ' ';
    cout << '\n';
}
