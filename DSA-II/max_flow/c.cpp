#include <bits/stdc++.h>
using namespace std;

class edge
{
public:
    int V;

    edge(int V)
    {
        this->V = V;
    }
};

// Edmonds-Karp uses BFS to find the shortest augmenting path
bool bfs(vector<vector<edge>> &adj,
         vector<vector<int>> &capacity,
         vector<int> &parent,
         int src,
         int sink)
{
    int n = adj.size();

    vector<bool> vis(n, false);
    queue<int> q;

    q.push(src);
    vis[src] = true;
    parent[src] = -1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (auto e : adj[u])
        {
            int v = e.V;

            if (!vis[v] && capacity[u][v] > 0)
            {
                vis[v] = true;
                parent[v] = u;
                q.push(v);

                if (v == sink)
                    return true;
            }
        }
    }

    return false;
}

int edmondsKarp(vector<vector<edge>> &adj,
                 vector<vector<int>> &capacity,
                 int src,
                 int sink)
{
    int n = adj.size();
    vector<int> parent(n);
    int maxFlow = 0;

    while (bfs(adj, capacity, parent, src, sink))
    {
        int pathFlow = INT_MAX;

        // Find minimum residual capacity along the path
        for (int v = sink; v != src; v = parent[v])
        {
            int u = parent[v];
            pathFlow = min(pathFlow, capacity[u][v]);
        }

        // Update residual capacities
        for (int v = sink; v != src; v = parent[v])
        {
            int u = parent[v];

            capacity[u][v] -= pathFlow;
            capacity[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

void solve()
{
    int P, C;
    if (!(cin >> P >> C))
        return;

    vector<int> plant_supply(P);
    for (int i = 0; i < P; i++)
    {
        cin >> plant_supply[i];
    }

    vector<int> city_demand(C);
    for (int i = 0; i < C; i++)
    {
        cin >> city_demand[i];
    }

    int M;
    cin >> M;

    // Node definitions:
    // Super Source = 0
    // Plants = 1 to P
    // Cities = P + 1 to P + C
    // Super Sink = P + C + 1

    int src = 0;
    int sink = P + C + 1;
    int total_nodes = sink + 1;

    vector<vector<edge>> adj(total_nodes);
    vector<vector<int>> capacity(total_nodes, vector<int>(total_nodes, 0));

    // 1. Connect Super Source (0) to Power Plants (1 to P)
    for (int i = 0; i < P; i++)
    {
        int plant_node = i + 1;
        adj[src].push_back(edge(plant_node));
        adj[plant_node].push_back(edge(src));
        capacity[src][plant_node] += plant_supply[i];
    }

    // 2. Connect Transmission Lines (P Plants & C Cities)
    for (int i = 0; i < M; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;

        // Shift 0-based input nodes to 1-based internal structure
        int real_u = u + 1;
        int real_v = v + 1;

        adj[real_u].push_back(edge(real_v));
        adj[real_v].push_back(edge(real_u));
        capacity[real_u][real_v] += w; // Supports multiple edges if present
    }

    // 3. Connect Cities (P + 1 to P + C) to Super Sink
    for (int j = 0; j < C; j++)
    {
        int city_node = P + 1 + j;
        adj[city_node].push_back(edge(sink));
        adj[sink].push_back(edge(city_node));
        capacity[city_node][sink] += city_demand[j];
    }

    // Calculate Max Flow
    int total_delivered_power = edmondsKarp(adj, capacity, src, sink);

    cout << total_delivered_power << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}