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
                int w = p.second;
                dist[u][v] = min(dist[u][v], (long long)w);
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
    
    int A, B;
    cin >> A >> B;
    
    vector<vector<long long>> dist = g.floydWarshall();
    
    int q;
    cin >> q;
    while (q--)
    {
        int s, d;
        cin >> s >> d;
        
        long long costA = INF;
        long long costB = INF;
        
        if (dist[s][A] < INF && dist[A][d] < INF) {
            costA = dist[s][A] + dist[A][d];
        }
        
        if (dist[s][B] < INF && dist[B][d] < INF) {
            costB = dist[s][B] + dist[B][d];
        }
        
        if (costA == INF && costB == INF) {
            cout << -1 << "\n";
        }
        else {
            if (costA < costB) {
                cout << costA << " " << A << "\n";
            } 
            else if (costB < costA) {
                cout << costB << " " << B << "\n";
            } 
            else {
                cout << costA << " " << min(A, B) << "\n";
            }
        }
    }

    return 0;
}