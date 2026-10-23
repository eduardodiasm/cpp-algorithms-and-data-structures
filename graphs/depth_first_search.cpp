#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

// Adjacency list, vertices 0..V-1, valid source and neighbors.
// Iterative DFS avoids recursion limits; works on directed/undirected graphs.
// O(V + E) time, O(V) extra space. Returns reachability from source.
vector<bool> depth_first_search(const vector<vector<int>>& graph, int source)
{
    vector<bool> visited(graph.size(), false);
    vector<int> pending = {source};
    visited[source] = true;

    while(!pending.empty())
    {
        int vertex = pending.back();
        pending.pop_back();
        for(int neighbor : graph[vertex])
        {
            if(visited[neighbor])
                continue;
            visited[neighbor] = true;
            pending.push_back(neighbor);
        }
    }
    return visited;
}

int main()
{
    auto visited = depth_first_search({{1}, {2}, {0}, {}}, 0);
    assert((visited == vector<bool>{true, true, true, false}));
    assert((depth_first_search({{0}}, 0) == vector<bool>{true}));
    assert((depth_first_search({{}, {0}}, 0) == vector<bool>{true, false}));
    for(bool value : visited)
        cout << value << ' ';
    cout << '\n';
}
