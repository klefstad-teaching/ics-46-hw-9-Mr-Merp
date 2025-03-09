#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    vector<int> distances(G.numVertices, INF);
    vector<bool> visited(G.numVertices, false);
    previous.resize(G.numVertices, -1);
    
    distances[source] = 0;
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});
    
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        
        if (visited[u])
            continue;
        
        visited[u] = true;

        for (const Edge& edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;
            
            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                pq.push({distances[v], v});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    if (distances[destination] == INF)
        return {};

    vector<int> path;
    vector<bool> visited(previous.size(), false);
    for (int i = destination; i != -1; i = previous[i]){
        path.push_back(i);
        if (visited[i]) {
            cout << "cycle detected" << endl;
            break;
        }
        visited[i] = true;
    }
    
    return vector<int>(path.rbegin(), path.rend());
}

void print_path(const vector<int>& path, int total) {
    if (path.empty()) {
        cout << "No path exists" << endl;
        return;
    }
    int plen = path.size();
    for (size_t i = 0; i < plen; ++i) {
        cout << path[i] << ' ';
    }
    cout << endl;
    
    cout << "Total cost is " << total << endl;
}
