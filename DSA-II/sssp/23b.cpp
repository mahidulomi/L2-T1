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

void dijkstra(int V, vector<vector<Edge>> &g, int src,
              vector<vector<long long>> &dist)
{
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

            // Coupon use korbo na
            if (cost + w < dist[v][used])
            {
                dist[v][used] = cost + w;
                pq.push({dist[v][used], {v, used}});
            }

            // Coupon use korbo
            if (used == 0)
            {
                if (cost + w / 2 < dist[v][1])
                {
                    dist[v][1] = cost + w / 2;
                    pq.push({dist[v][1], {v, 1}});
                }
            }
        }
    }
}

int main()
{
    int V, m;
    cin >> V >> m;

    vector<vector<Edge>> g(V + 1);
    vector<vector<Edge>> rev(V + 1);

    for (int i = 0; i < m; i++)
    {
        int u, v;
        long long w;
        cin >> u >> v >> w;

        g[u].push_back(Edge(v, w));
        rev[v].push_back(Edge(u, w));
    }

    int x, y;
    long long w;
    cin >> x >> y >> w;

    vector<vector<long long>> dist1(V + 1, vector<long long>(2, LLONG_MAX));
    vector<vector<long long>> dist2(V + 1, vector<long long>(2, LLONG_MAX));

    dijkstra(V, g, 1, dist1);      // Source -> sob node
    dijkstra(V, rev, V, dist2);    // Sob node -> Destination

    long long ans = LLONG_MAX;

    // Case 1 : Coupon agei use hoye geche
    if (dist1[x][1] != LLONG_MAX && dist2[y][0] != LLONG_MAX)
    {
        ans = min(ans, dist1[x][1] + w + dist2[y][0]);
    }

    // Case 2 : Coupon mandatory edge e use
    if (dist1[x][0] != LLONG_MAX && dist2[y][0] != LLONG_MAX)
    {
        ans = min(ans, dist1[x][0] + w / 2 + dist2[y][0]);
    }

    // Case 3 : Coupon pore use hobe
    if (dist1[x][0] != LLONG_MAX && dist2[y][1] != LLONG_MAX)
    {
        ans = min(ans, dist1[x][0] + w + dist2[y][1]);
    }

    if (ans == LLONG_MAX)
        cout << "Not possible\n";
    else
        cout << ans << endl;

    return 0;
}