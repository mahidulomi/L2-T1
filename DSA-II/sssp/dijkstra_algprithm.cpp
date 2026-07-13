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
void dijkstra(int V, vector<vector<Edge>> &g, int src)
{
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src});

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        for (auto &edge : g[u])
        {
            int v = edge.dest;
            int weight = edge.weight;

            if (dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "Vertex Distance from Source\n";
    for (int i = 0; i < V; i++)
    {
        cout << i << "\t\t" << dist[i] << "\n";
    }
}

int main()
{
    int V,m;
    cin >> V >> m;
    vector<vector<Edge>> g(V+1);
    for(int i = 1; i <= m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back(Edge(v, w));
    }
    dijkstra(V, g, 1);
    return 0;
}