#include "dijkstras.h"

int main()
{
    Graph G;
    vector<int> prev;
    file_to_graph("/home/hjardine/ics46/ics-46-hw-9-HectorJardines/src/medium.txt", G);
    vector<int> distances = dijkstra_shortest_path(G, 0, prev);

    for (size_t vert = 0; vert < distances.size(); ++vert)
    {
        if (distances[vert] != INF)
        {
            vector<int> pathToVert = extract_shortest_path(distances, prev, vert);
            print_path(pathToVert, distances[vert]);
        }
    }
}