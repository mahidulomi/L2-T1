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

void dijkstra(int V, vector<vector<Edge>> &g, vector<long long> &dist)
{
    priority_queue<pair<long long, int>,
                   vector<pair<long long, int>>,
                   greater<pair<long long, int>>> pq;

    dist[1] = 0;
    pq.push({0, 1});

    while (!pq.empty())
    {
        long long d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u])
            continue;

        for (auto &edge : g[u])
        {
            int v = edge.dest;
            int w = edge.weight;

            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}

int main()
{
    int N, M, F;
    cin >> N >> M >> F;

    vector<int> capacity(N + 1);

    for (int i = 1; i <= N; i++)
        cin >> capacity[i];

    vector<vector<Edge>> g(N + 1);

    for (int i = 0; i < M; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;

        g[u].push_back(Edge(v, w));
        g[v].push_back(Edge(u, w));
    }

    int K;
    cin >> K;

    vector<long long> dist(N + 1, LLONG_MAX);

    dijkstra(N, g, dist);

    vector<long long> costs;

    for (int i = 1; i <= N; i++)
    {
        long long total = dist[i] + F;

        for (int j = 0; j < capacity[i]; j++)
        {
            costs.push_back(total);
        }
    }

    sort(costs.begin(), costs.end());

    for (int i = 0; i < K; i++)
    {
        if (i < costs.size())
            cout << costs[i] << " ";
        else
            cout << -1 << " ";
    }

    cout << endl;

    return 0;
}