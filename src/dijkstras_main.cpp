#include "dijkstras.h"

int main() {
    Graph G;
    file_to_graph("src/largest.txt", G);
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);
    vector<int> path = extract_shortest_path(distances, previous, 99);
    print_path(path, distances[99]);
    return 0;
}