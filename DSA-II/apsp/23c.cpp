#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e15;

class Graph
{
public:
    int V;
    vector<vector<pair<int, int>>> adj;
    
    Graph(int V)
    {
        this->V = V;
        adj.resize(V);
    }
    
    void addEdge(int u, int v, int w)
    {
        adj[u].push_back({v, w});
    }
    
    vector<vector<long long>> floydWarshall(bool discount)
    {
        vector<vector<long long>> dist(V, vector<long long>(V, INF));
        for (int i = 0; i < V; i++)
        {
            dist[i][i] = 0;
        }
        for (int u = 0; u < V; u++)
        {
            for (auto p : adj[u])
            {
                int v = p.first;
                long long w = p.second;
                if (discount)
                {
                    dist[u][v] = min(dist[u][v], w - 1);
                }
                else
                {
                    dist[u][v] = min(dist[u][v], w);
                }
            }
        }
        for (int k = 0; k < V; k++)
        {
            for (int i = 0; i < V; i++)
            {
                for (int j = 0; j < V; j++)
                {
                    if (dist[i][k] < INF && dist[k][j] < INF)
                    {
                        if (dist[i][k] + dist[k][j] < dist[i][j])
                        {
                            dist[i][j] = dist[i][k] + dist[k][j];
                        }
                    }
                }
            }
        }
        return dist;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int V, E;
    if (!(cin >> V >> E)) return 0;
    
    Graph g(V);
    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }
    
    int target_city; 
    cin >> target_city;
    
    vector<vector<long long>> dist_normal = g.floydWarshall(false);
    vector<vector<long long>> dist_discount = g.floydWarshall(true);
    
    int q;
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        int u, v;
        cin >> u >> v;
        
        long long ans = dist_normal[u][v];
        
        if (dist_discount[u][target_city] < INF && dist_discount[target_city][v] < INF)
        {
            long long discount_path = dist_discount[u][target_city] + dist_discount[target_city][v];
            ans = min(ans, discount_path);
        }
        
        if (ans >= INF)
        {
            cout << -1 << "\n";
        }
        else
        {
            cout << ans << "\n";
        }
    }

    return 0;
}