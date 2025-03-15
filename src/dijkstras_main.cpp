#include "dijkstras.h"

void setUpGraph(Graph & G, vector<int> & distances, vector<int> & prev, const std::string & filename)
{
    file_to_graph(filename, G);
    distances = dijkstra_shortest_path(G, 0, prev);
}

void extract_print_graph(vector<int> & distances, vector<int> & prev, const std::string & testSuite)
{
    for (size_t vert = 0; vert < distances.size(); ++vert)
    {
        if (distances[vert] != INF)
        {
            vector<int> pathToVert = extract_shortest_path(distances, prev, vert);
            print_path(pathToVert, distances[vert]);
        }
    }

    std::cout << "--------------------Completed test on: " << testSuite << "------------------------" << std::endl;
}

void verify_shortest_path_small()
{
    Graph small;
    vector<int> prevSmall;
    vector<int> distancesSmall;

    setUpGraph(small, distancesSmall, prevSmall, "/home/hjardine/ics46/ics-46-hw-9-HectorJardines/src/small.txt");
    extract_print_graph(distancesSmall, prevSmall, "smallFile");
}

void verify_shortest_path_medium()
{
    Graph medium;
    vector<int> prevMedium;
    vector<int> distancesMedium;

    setUpGraph(medium, distancesMedium, prevMedium, "/home/hjardine/ics46/ics-46-hw-9-HectorJardines/src/medium.txt");
    extract_print_graph(distancesMedium, prevMedium, "mediumFile");
}

void verify_shortest_path_large()
{
    Graph large;
    vector<int> prevLarge;
    vector<int> distancesLarge;

    setUpGraph(large, distancesLarge, prevLarge, "/home/hjardine/ics46/ics-46-hw-9-HectorJardines/src/large.txt");
    extract_print_graph(distancesLarge, prevLarge, "largeFile");
}

void verify_shortest_path_largest()
{
    Graph largest;
    vector<int> prevLargest;
    vector<int> distancesLargest;

    setUpGraph(largest, distancesLargest, prevLargest, "/home/hjardine/ics46/ics-46-hw-9-HectorJardines/src/largest.txt");
    extract_print_graph(distancesLargest, prevLargest, "LargestFile");
}

int main()
{
    verify_shortest_path_small();
    verify_shortest_path_medium();
    verify_shortest_path_large();
    verify_shortest_path_largest();
}