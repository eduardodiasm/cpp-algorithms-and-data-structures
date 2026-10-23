#include <cassert>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Adjacency list, vertices 0..V-1, valid source and neighbors.
// Works on directed and undirected graphs. O(V + E) time, O(V) extra space.
// Returns minimum edge counts from source; -1 means unreachable.
vector<int> breadth_first_search(const vector<vector<int>>& graph, int source)
{
    vector<int> distance(graph.size(), -1);
    queue<int> pending;
    distance[source] = 0;
    pending.push(source);

    while(!pending.empty())
    {
        int vertex = pending.front();
        pending.pop();
        for(int neighbor : graph[vertex])
        {
            if(distance[neighbor] != -1)
                continue;
            distance[neighbor] = distance[vertex] + 1;
            pending.push(neighbor);
        }
    }
    return distance;
}

int main()
{
    vector<vector<int>> graph = {{1, 2}, {0, 3}, {0, 3}, {1, 2}, {}};
    auto distance = breadth_first_search(graph, 0);
    assert((distance == vector<int>{0, 1, 1, 2, -1}));
    assert((breadth_first_search({{}}, 0) == vector<int>{0}));
    assert((breadth_first_search({{0, 1, 1}, {}}, 0) == vector<int>{0, 1}));
    for(int value : distance)
        cout << value << ' ';
    cout << '\n';
}
