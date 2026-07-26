#include <bits/stdc++.h>
using namespace std;

class Edge
{
public:
    int dest;
    long long weight;

    Edge(int d, long long w)
    {
        dest = d;
        weight = w;
    }
};

void dijkstra(int V, vector<vector<Edge>> &g, int src)
{
    vector<vector<long long>> dist(V + 1, vector<long long>(3, LLONG_MAX));

    // {cost, {node, usedCoupon}}
    priority_queue<
        pair<long long, pair<int, int>>,
        vector<pair<long long, pair<int, int>>>,
        greater<pair<long long, pair<int, int>>>>
        pq;

    dist[src][0] = 0;
    pq.push({0, {src, 0}});

    while (!pq.empty())
    {
        long long cost = pq.top().first;
        int u = pq.top().second.first;
        int used = pq.top().second.second;
        pq.pop();

        if (cost > dist[u][used])
            continue;

        for (auto &edge : g[u])
        {
            int v = edge.dest;
            long long w = edge.weight;

            // Coupon use na kore
            if (cost + w < dist[v][used])
            {
                dist[v][used] = cost + w;
                pq.push({dist[v][used], {v, used}});
            }

            // Coupon use korbo (maximum 2 bar)
            if (used < 2)
            {
                if (cost + w / 2 < dist[v][used + 1])
                {
                    dist[v][used + 1] = cost + w / 2;
                    pq.push({dist[v][used + 1], {v, used + 1}});
                }
            }
        }
    }

    cout << "Minimum Cost = " << dist[V][2] << endl;
}

int main()
{
    int V, m;
    cin >> V >> m;

    vector<vector<Edge>> g(V + 1);

    for (int i = 1; i <= m; i++)
    {
        int u, v;
        long long w;
        cin >> u >> v >> w;

        g[u].push_back(Edge(v, w));
    }

    dijkstra(V, g, 1);

    return 0;
}