#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

class Graph
{
public:
    int V;
    vector<vector<pair<int, int>>> adj;
    
    Graph(int V)
    {
        this->V = V;
        adj.resize(V + 1);
    }
    
    void addEdge(int u, int v, int w)
    {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    
    vector<vector<long long>> floydWarshall()
    {
        vector<vector<long long>> dist(V + 1, vector<long long>(V + 1, INF));
        
        for (int i = 1; i <= V; i++)
        {
            dist[i][i] = 0;
        }
        
        for (int u = 1; u <= V; u++)
        {
            for (auto p : adj[u])
            {
                int v = p.first;
                long long w = p.second;
                dist[u][v] = min(dist[u][v], w);
            }
        }
        
        for (int k = 1; k <= V; k++)
        {
            for (int i = 1; i <= V; i++)
            {
                for (int j = 1; j <= V; j++)
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

    int V, E, Q;
    if (!(cin >> V >> E >> Q)) return 0;
    
    Graph g(V);
    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }
    
    vector<vector<long long>> dist = g.floydWarshall();
    
    for (int i = 0; i < Q; i++)
    {
        int a, b;
        cin >> a >> b;
        if (dist[a][b] >= INF)
        {
            cout << -1 << "\n";
        }
        else
        {
            cout << dist[a][b] << "\n";
        }
    }
    return 0;
}