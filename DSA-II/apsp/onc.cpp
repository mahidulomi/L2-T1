#include <bits/stdc++.h>
using namespace std;

const int INF = 1e8; 

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
    
    vector<vector<int>> floydWarshall()
    {
        vector<vector<int>> dist(V + 1, vector<int>(V + 1, INF));
        
        for(int i = 1; i <= V; i++)
        {
            dist[i][i] = 0;
        }
        
        for(int u = 1; u <= V; u++)
        {
            for(auto p : adj[u])
            {
                int v = p.first;
                int w = p.second;
                dist[u][v] = min(dist[u][v], w); 
            }
        }
        
        for(int k = 1; k <= V; k++)
        {
            for(int i = 1; i <= V; i++)
            {
                for(int j = 1; j <= V; j++)
                {
                    if(dist[i][k] < INF && dist[k][j] < INF)
                    {
                        if(dist[i][k] + dist[k][j] < dist[i][j])
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

    vector<int> scenic_score(V + 1);
    for(int i = 1; i <= V; i++)
    {
        cin >> scenic_score[i];
    }

    Graph g(V);
    for(int i = 0; i < E; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w); 
    }

    vector<vector<int>> dist = g.floydWarshall();

    for(int i = 0; i < Q; i++)
    {
        int s, t;
        cin >> s >> t; 

        int max_satisfaction = -INF;
        int best_total_cost = INF;
        int best_a = -1, best_b = -1;
        bool found = false;

        for(int a = 1; a <= V; a++)
        {
            if(a == s || a == t) continue;
            if(dist[s][a] == INF) continue; 

            for(int b = 1; b <= V; b++)
            {
                if(b == s || b == t || b == a) continue;
                if(dist[a][b] == INF || dist[b][t] == INF) continue; 

                int total_cost = dist[s][a] + dist[a][b] + dist[b][t];
                int satisfaction = scenic_score[a] + scenic_score[b] - total_cost;

                if(!found || satisfaction > max_satisfaction)
                {
                    max_satisfaction = satisfaction;
                    best_total_cost = total_cost;
                    best_a = a;
                    best_b = b;
                    found = true;
                }
                else if(satisfaction == max_satisfaction)
                {
                    if(a < best_a)
                    {
                        best_a = a;
                        best_b = b;
                        best_total_cost = total_cost;
                    }
                    else if(a == best_a && b < best_b)
                    {
                        best_b = b;
                        best_total_cost = total_cost;
                    }
                }
            }
        }

        if(found)
        {
            cout << best_a << " " << best_b << " " << max_satisfaction << " " << best_total_cost << "\n";
        }
        else
        {
            cout << "No expedition\n";
        }
    }
    return 0;
}