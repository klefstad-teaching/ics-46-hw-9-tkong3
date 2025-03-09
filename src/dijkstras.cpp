#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    vector<int> distances(G.numVertices, INF);
    previous.resize(G.numVertices, -1);
    vector<bool> visited(G.numVertices, false);

    distances[source] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if (visited[u]) continue;
        visited[u] = true;
        for (Edge edge: G[u]) {
            int v = edge.dst;
            int weight = edge.weight;
            if (!visited[v] && (distances[u] + weight < distances[v])) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                pq.push({distances[v], v});
            }
        }
    }
    return distances;
}



vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> shortest_path;
    if (distances[destination] == INF) {
        return shortest_path;
    }
    while (destination != -1) {
        shortest_path.push_back(destination);
        destination = previous[destination];
    }
    reverse(shortest_path.begin(), shortest_path.end());
    return shortest_path;
}


void print_path(const vector<int>& v, int total) {
    for (int vertex : v) {
        cout << vertex << ' ';
    }
    cout << total;
}