#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    vector<int> distances(G.numVertices, INF);
    vector<bool> visited(G.numVertices, false);

    distances[source] = 0;
    previous.resize(G.numVertices);
    priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({source, 0});

    while (!pq.empty()) {
        int u = pq.top().first;
        pq.pop();
        if (!visited[u]) {
            visited[u] = true;
            for (Edge edge: G[u]) {
                int v = edge.dst;
                int weight = edge.weight;
                if (distances[u] + weight < distances[v]) {
                    distances[v] = distances[u] + weight;
                    previous[v] = u;
                    pq.push({v, distances[v]});
                }
            }
        }
    }
    return distances;
}


