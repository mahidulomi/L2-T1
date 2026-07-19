#include <bits/stdc++.h>
using namespace std;


const long long INF = 1e16; 

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
    vector<vector<long long>> floydWarshall()
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
                dist[u][v] = min(dist[u][v], w); 
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
    
    vector<vector<long long>> dist = g.floydWarshall();
    
    int A, B;
    cin >> A >> B; 
    
    int q;
    cin >> q; 
    
    for (int i = 0; i < q; i++)
    {
        int u, v;
        cin >> u >> v;
        
        long long costA = INF;
        if (dist[u][A] < INF && dist[A][v] < INF) {
            costA = dist[u][A] + dist[A][v];
        }
        
        long long costB = INF;
        if (dist[u][B] < INF && dist[B][v] < INF) {
            costB = dist[u][B] + dist[B][v];
        }
        
        long long final_ans = min(costA, costB);
        
        if (final_ans >= INF)
        {
            cout << "-1\n";
        }
        else
        {
            cout << final_ans << "\n";
        }
    }
    return 0;
}