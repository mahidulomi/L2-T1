#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 1e18; 

class RohanGraph {
private:
    int numVertices;
    
public:
    vector<vector<long long>> dist;

    RohanGraph(int vertices) {
        this->numVertices = vertices;
        dist.assign(vertices + 1, vector<long long>(vertices + 1, INF));

        for (int i = 1; i <= vertices; i++) {
            dist[i][i] = 0;
        }
    }

    void addEdge(int u, int v, long long w) {
        if (w < dist[u][v]) {
            dist[u][v] = w;
        }
    }

    void computeAllPairsShortestPath() {
        for (int k = 1; k <= numVertices; k++) {
            for (int i = 1; i <= numVertices; i++) {
                for (int j = 1; j <= numVertices; j++) {
                    if (dist[i][k] < INF && dist[k][j] < INF) {
                        if (dist[i][k] + dist[k][j] < dist[i][j]) {
                            dist[i][j] = dist[i][k] + dist[k][j];
                        }
                    }
                }
            }
        }
    }

    long long getTravelCost(int from, int to) {
        return dist[from][to];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    if (!(cin >> n >> m >> k)) return 0;

    vector<int> start_stations(n);
    for (int i = 0; i < n; i++) {
        cin >> start_stations[i];
    }

    vector<int> target_stations(n);
    for (int i = 0; i < n; i++) {
        cin >> target_stations[i];
    }

    RohanGraph graph(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        graph.addEdge(u, v, w); 
    }

    graph.computeAllPairsShortestPath();

    vector<long long> valid_costs;

    for (int i = 0; i < n; i++) {
        int u = start_stations[i];
        int v = target_stations[i];
        long long cost = graph.getTravelCost(u, v);

        if (cost < INF) {
            valid_costs.push_back(cost);
        }
    }

    sort(valid_costs.begin(), valid_costs.end(), greater<long long>());

    long long total_minimum_cost = 0;
    long long current_multiplier = 1; 
    int batch_count = 0;

    for (size_t i = 0; i < valid_costs.size(); i++) {
        total_minimum_cost += (valid_costs[i] * current_multiplier);
        batch_count++;

        if (batch_count == k) {
            current_multiplier *= 2;
            batch_count = 0; 
        }
    }

    cout << total_minimum_cost << "\n";

    return 0;
}