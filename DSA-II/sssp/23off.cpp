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
    vector<long long> dist1(V + 1, LLONG_MAX); // Coupon use hoyni
    vector<long long> dist2(V + 1, LLONG_MAX); // Coupon use hoye geche

    priority_queue<pair<long long, pair<int, int>>,
                   vector<pair<long long, pair<int, int>>>,
                   greater<pair<long long, pair<int, int>>>> pq;

    dist1[src] = 0;

    // {cost,{node,used}}
    pq.push({0, {src, 0}});

    while (!pq.empty())
    {
        long long cost = pq.top().first;
        int u = pq.top().second.first;
        int used = pq.top().second.second;
        pq.pop();

        if (used == 0 && cost > dist1[u])
            continue;

        if (used == 1 && cost > dist2[u])
            continue;

        for (auto &edge : g[u])
        {
            int v = edge.dest;
            long long w = edge.weight;

            // Coupon use kori nai
            if (used == 0)
            {
                // Coupon use na kore
                if (dist1[u] + w < dist1[v])
                {
                    dist1[v] = dist1[u] + w;
                    pq.push({dist1[v], {v, 0}});
                }

                // Coupon use kore
                if (dist1[u] + w / 2 < dist2[v])
                {
                    dist2[v] = dist1[u] + w / 2;
                    pq.push({dist2[v], {v, 1}});
                }
            }
            else
            {
                // Coupon agei use hoye geche
                if (dist2[u] + w < dist2[v])
                {
                    dist2[v] = dist2[u] + w;
                    pq.push({dist2[v], {v, 1}});
                }
            }
        }
    }

    cout << dist2[V] << endl;
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