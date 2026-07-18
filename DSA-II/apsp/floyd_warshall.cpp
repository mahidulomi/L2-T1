#include <bits/stdc++.h>
using namespace std;

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
    void floydWarshall()
    {
        const int INF = 1e9;
        vector<vector<int>> dist(V, vector<int>(V, INF));
        for(int i = 0; i < V; i++)
        {
            dist[i][i] = 0;
        }
        for(int u = 0; u < V; u++)
        {
            for(auto p : adj[u])
            {
                int v = p.first;
                int w = p.second;
                dist[u][v] = w;
            }
        }
        for(int k = 0; k < V; k++)
        {
            for(int i = 0; i < V; i++)
            {
                for(int j = 0; j < V; j++)
                {
                    if(dist[i][k] + dist[k][j] < dist[i][j])
                    {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }

};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int V, E;
    cin >> V >> E;
    Graph g(V);
    for(int i = 0; i < E; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }
    g.floydWarshall();
    return 0;
}