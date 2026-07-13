#include <bits/stdc++.h>
using namespace std;

class Edge {
public:
    int dest;
    int weight; // Cost
    int time;   // Travel Time
    Edge(int d, int w, int t) {
        dest = d;
        weight = w;
        time = t;
    }
};

void dijkstra(int V, vector<vector<Edge>> &g, int src, int dest, int K) {
    // We store total cost in dist array
    vector<long long> dist(V + 1, LLONG_MAX);
    vector<int> time_taken(V + 1, 0);
    vector<int> parent(V + 1, -1);
    
    dist[src] = 0;
    time_taken[src] = 0;

    // priority_queue elements: {total_cost, current_node}
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        long long curr_cost = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (curr_cost > dist[u]) continue;
        if (u == dest) break;

        for (auto &edge : g[u]) {
            int v = edge.dest;
            int t = edge.time;
            int c = edge.weight;

            // Intermediate transfer penalty check
            int wait_time = (u == src) ? 0 : 1;

            int next_time = time_taken[u] + t + wait_time;
            // Total cost for this edge = travel cost + travel time cost + wait time cost
            long long next_cost = curr_cost + c + (1LL * t * K) + (1LL * wait_time * K);

            if (next_cost < dist[v]) {
                dist[v] = next_cost;
                time_taken[v] = next_time;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        } 
    }

    // Checking if path exists
    if (dist[dest] == LLONG_MAX) {
        cout << "Error\n";
        return;
    }

    // Path Reconstruction
    vector<int> path;
    int curr = dest;
    while (curr != -1) {
        path.push_back(curr);
        curr = parent[curr];
    }
    reverse(path.begin(), path.end());

    // Formatting Path string
    for (int i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i < path.size() - 1) cout << "->";
    }
    
    // Output total time and total cost
    cout << " " << time_taken[dest] << " " << dist[dest] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int k, n, x;
    if (!(cin >> k >> n >> x)) return 0;

    vector<vector<Edge>> g(n + 1);
    for (int i = 1; i <= x; i++) {
        int u, v, t, w;
        cin >> u >> v >> t >> w;
        // Bidirectional edges inserted
        g[u].push_back(Edge(v, w, t));
        g[v].push_back(Edge(u, w, t));
    }

    int src, dest;
    cin >> src >> dest;

    dijkstra(n, g, src, dest, k);

    return 0;
}