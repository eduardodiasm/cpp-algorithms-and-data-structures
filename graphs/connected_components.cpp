#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

// Undirected adjacency list: include both directions of each edge.
// Valid vertex IDs are 0..V-1. O(V + E) time, O(V) extra space.
// Returns a component ID per vertex; IDs start at zero.
vector<int> connected_components(const vector<vector<int>>& graph)
{
    vector<int> component(graph.size(), -1);
    int id = 0;
    for(size_t source = 0; source < graph.size(); ++source)
    {
        if(component[source] != -1)
            continue;
        vector<int> pending = {static_cast<int>(source)};
        component[source] = id;
        while(!pending.empty())
        {
            int vertex = pending.back();
            pending.pop_back();
            for(int neighbor : graph[vertex])
            {
                if(component[neighbor] != -1)
                    continue;
                component[neighbor] = id;
                pending.push_back(neighbor);
            }
        }
        ++id;
    }
    return component;
}

int main()
{
    auto component = connected_components({{1}, {0}, {3}, {2}, {}});
    assert((component == vector<int>{0, 0, 1, 1, 2}));
    assert(connected_components({}).empty());
    assert((connected_components({{0}, {}}) == vector<int>{0, 1}));
    for(int id : component)
        cout << id << ' ';
    cout << '\n';
}
