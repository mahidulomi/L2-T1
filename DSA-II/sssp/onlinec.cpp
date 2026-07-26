#include <bits/stdc++.h>
using namespace std;

class Edge
{
public:
    int dest;
    double weight;

    Edge(int d, double w)
    {
        dest = d;
        weight = w;
    }
};

void dijkstra(int V, vector<vector<Edge>> &g, int src, int dest)
{
    vector<double> dist(V + 1, 0.0);

    dist[src] = 1.0;

    priority_queue<pair<double, int>> pq;

    pq.push({1.0, src});

    while (!pq.empty())
    {
        double curReliability = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // Ignore old state
        if (curReliability < dist[u])
            continue;

        for (auto &edge : g[u])
        {
            int v = edge.dest;
            double weight = edge.weight;

            if (dist[u] * weight > dist[v])
            {
                dist[v] = dist[u] * weight;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[dest] == 0.0)
    {
        cout << -1 << endl;
    }
    else
    {
        cout << fixed << setprecision(6) << dist[dest] << endl;
    }
}

int main()
{
    int V, m;
    cin >> V >> m;

    int src, dest;
    cin >> src >> dest;

    vector<vector<Edge>> g(V + 1);

    for (int i = 0; i < m; i++)
    {
        int u, v;
        double w;

        cin >> u >> v >> w;

        g[u].push_back(Edge(v, w));
    }

    dijkstra(V, g, src, dest);

    return 0;
}