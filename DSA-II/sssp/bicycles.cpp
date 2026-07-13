#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

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

struct State
{
    long long time;
    int city;
    int bike;

    bool operator>(const State &other) const
    {
        return time > other.time;
    }
};

void dijkstra(int V, vector<vector<Edge>> &g, vector<long long> &s)
{

    vector<vector<long long>> dist(V + 1, vector<long long>(V + 1, INF));

    priority_queue<State, vector<State>, greater<State>> pq;

    dist[1][1] = 0;
    pq.push({0, 1, 1});

    long long ans = INF;

    while (!pq.empty())
    {
        State curr = pq.top();
        pq.pop();

        long long curr_time = curr.time;
        int u = curr.city;
        int b = curr.bike;

        if (u == V)
        {
            ans = curr_time;
            break;
        }

        if (curr_time > dist[u][b])
            continue;

        for (auto &edge : g[u])
        {
            int v = edge.dest;
            long long weight = edge.weight;

            int next_bike = (s[b] < s[v]) ? b : v;

            long long travel_cost = weight * s[b];

            if (dist[u][b] + travel_cost < dist[v][next_bike])
            {
                dist[v][next_bike] = dist[u][b] + travel_cost;
                pq.push({dist[v][next_bike], v, next_bike});
            }
        }
    }

    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--)
    {
        int V, m;
        cin >> V >> m;

        vector<vector<Edge>> g(V + 1);
        for (int i = 0; i < m; i++)
        {
            int u, v;
            long long w;
            cin >> u >> v >> w;
            g[u].push_back(Edge(v, w));
            g[v].push_back(Edge(u, w)); // undirected graph
        }

        vector<long long> s(V + 1);
        for (int i = 1; i <= V; i++)
        {
            cin >> s[i];
        }

        dijkstra(V, g, s);
    }
    return 0;
}