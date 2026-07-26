#include <bits/stdc++.h>
using namespace std;

class Edge
{
public:
    int src;
    int dest;
    long long weight;

    Edge(int s, int d, long long w)
    {
        src = s;
        dest = d;
        weight = w;
    }
};

void bellmanFord(int V, vector<Edge> &edges, vector<int> &emergency, vector<bool> &blocked)
{
    const long long INF = 1e18;

    vector<long long> dist(V + 1, INF);

    // Super Source = 0
    dist[0] = 0;

    // Bellman-Ford
    for (int i = 1; i <= V; i++)
    {
        bool updated = false;

        for (auto &edge : edges)
        {
            int u = edge.src;
            int v = edge.dest;
            long long w = edge.weight;

            if (dist[u] != INF && dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                updated = true;

                // Negative cycle detected
                if (i == V)
                {
                    cout << "Abyss Detected\n";
                    return;
                }
            }
        }

        if (!updated)
            break;
    }

    // Print answer
    for (int x : emergency)
    {
        if (blocked[x] || dist[x] == INF)
            cout << "Abyss\n";
        else
            cout << dist[x] << endl;
    }
}

int main()
{
    int n, m, k, b, e;
    cin >> n >> m >> k >> b >> e;

    vector<int> capitals(k);

    for (int i = 0; i < k; i++)
        cin >> capitals[i];

    vector<bool> blocked(n + 1, false);

    for (int i = 0; i < b; i++)
    {
        int x;
        cin >> x;
        blocked[x] = true;
    }

    vector<int> emergency(e);

    for (int i = 0; i < e; i++)
        cin >> emergency[i];

    vector<Edge> edges;

    // Read edges
    for (int i = 0; i < m; i++)
    {
        int u, v;
        long long w;
        cin >> u >> v >> w;

        // Ignore blocked cities
        if (blocked[u] || blocked[v])
            continue;

        edges.push_back(Edge(u, v, w));
    }

    // Super Source (0) -> every capital
    for (int x : capitals)
    {
        edges.push_back(Edge(0, x, 0));
    }

    bellmanFord(n, edges, emergency, blocked);

    return 0;
}