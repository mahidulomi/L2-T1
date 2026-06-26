
#include <bits/stdc++.h>
using namespace std;
class graph
{
    int V;
    int x;
    vector<vector<int>> adj;

public:
    graph(int v, int x)
    {
        this->V = v;
        this->x = x;
        adj.resize(v + 1);
    }
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> bfs(int src)
    {
        vector<int> dist(V + 1, -1);

        queue<int> q;
        q.push(src);
        dist[src] = 0;

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (int v : adj[u])
            {
                if (dist[v] == -1)
                {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }

        return dist;
    }
    int solve()
    {
        int mx = INT_MIN;
        vector<int> dist1 = bfs(1);
        vector<int> distx = bfs(x);
        for (int i = 1; i <= V; i++)
        {
            if (distx[i] < dist1[i])
            {
                mx = max(mx, dist1[i]);
            }
        }
        return 2 * mx;
    }
};

int main()
{
    int n, x;
    cin >> n >> x;
    graph g(n, x);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    cout << g.solve() << endl;

    return 0;
}