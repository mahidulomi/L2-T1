#include <bits/stdc++.h>
using namespace std;

class Edge
{
public:
    int dest;
    int weight;

    Edge(int d, int w)
    {
        dest = d;
        weight = w;
    }
};

void bellmanFord(int V, vector<vector<Edge>> &g, int src, int k)
{
    const long long INF = 1e18;

    vector<vector<long long>> dist(V, vector<long long>(2, INF));

    dist[src][0] = 0;

    for (int step = 1; step <= k; step++)
    {
        vector<vector<long long>> newDist = dist;

        for (int u = 0; u < V; u++)
        {
            for (auto &edge : g[u])
            {
                int v = edge.dest;
                int w = edge.weight;

               
                if (dist[u][0] != INF)
                {
                  
                    if (dist[u][0] + w < newDist[v][0])
                    {
                        newDist[v][0] = dist[u][0] + w;
                    }

               
                    if (dist[u][0] + w / 2 < newDist[v][1])
                    {
                        newDist[v][1] = dist[u][0] + w / 2;
                    }
                }

              
                if (dist[u][1] != INF)
                {
                    if (dist[u][1] + w < newDist[v][1])
                    {
                        newDist[v][1] = dist[u][1] + w;
                    }
                }
            }
        }

        dist = newDist;
    }

    long long ans = min(dist[V - 1][0], dist[V - 1][1]);

    if (ans == INF)
        cout << "Not possible" << endl;
    else
        cout << ans << endl;
}

int main()
{
    int V, E, k;
    cin >> V >> E >> k;

    vector<vector<Edge>> g(V);

    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;

        u--;
        v--;

        g[u].push_back(Edge(v, w));
    }

    bellmanFord(V, g, 0, k);

    return 0;
}