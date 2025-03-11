#include "dijkstras.h"
#include <queue>

using Vertex = int;
using Weight = int;

//Edge has src, dst, and weight
vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous)
{
    vector<int> distances(G.numVertices, INF);
    // std::cout << "Num verts = " << G.numVertices << std::endl;

    std::vector<bool> visited(G.numVertices, false);
    previous.resize(G.numVertices, -1);

    std::priority_queue<std::pair<Vertex, Weight>, std::vector<std::pair<Vertex, Weight>>, CompareSecond> minHeap;

    minHeap.push({source, 0});
    distances[source] = 0;

    while (!minHeap.empty())
    {
        // std::cout << "Hello World" << std::endl;
        Vertex u = minHeap.top().first;
        minHeap.pop();
        // std::cout << "Top of q is: " << u << std::endl;

        if (visited[u])
            continue;

        visited[u] = true;
        for (const Edge & neighbor : G[u])
        {
            // std::cout << "Current neighbor is: " << neighbor << std::endl;
            Vertex v = neighbor.dst;
            Weight weight = neighbor.weight;

            if (!visited[v] && distances[u] + weight < distances[v])
            {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({v, distances[v]});
            }
        }
    }
    return distances;
}

// distances: stores distance from source vert to dest vert (index reps the vertex number)
// previous: stores the previous vertex visited to arrie at index vertex
// destination: assuming this is the source vertex
vector<int> extract_shortest_path(const vector<int>& distances/*distances*/, const vector<int>& previous, int destination)
{
    vector<Vertex> path;
    std::stack<int> vertices;

    if (distances[destination == INF])
        return path;

    vertices.push(destination);
    Vertex prev = previous[destination];
    while (prev != -1)
    {
        vertices.push(prev);
        prev = previous[prev];
    }

    while (!vertices.empty())
    {
        path.push_back(vertices.top());
        vertices.pop();
    }
    return path;
}

void print_path(const vector<int>& v, int total)
{
    for (Vertex vert : v)
    {
        std::cout << vert << ' ';
    }
    std::cout << std::endl << "Total cost is: " << total << std::endl;
}
