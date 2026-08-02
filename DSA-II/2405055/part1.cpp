#include <bits/stdc++.h>
using namespace std;

bool bfs(vector<vector<int>> &adj,
         vector<vector<int>> &capacity,
         vector<int> &parent,
         int src,
         int sink)
{
    int n = adj.size();

    vector<bool> vis(n, false);
    queue<int> q;

    q.push(src);
    vis[src] = true;
    parent[src] = -1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (auto e : adj[u])
        {
            int v = e;

            if (!vis[v] && capacity[u][v] > 0)
            {
                vis[v] = true;
                parent[v] = u;
                q.push(v);

                if (v == sink)
                    return true;
            }
        }
    }

    return false;
}

int edmondsKarp(vector<vector<int>> &adj,
                vector<vector<int>> &capacity,
                int src,
                int sink)
{
    int n = adj.size();

    vector<int> parent(n);

    int maxFlow = 0;

    while (bfs(adj, capacity, parent, src, sink))
    {
        int pathFlow = INT_MAX;

        
        for (int v = sink; v != src; v = parent[v])
        {
            int u = parent[v];
            pathFlow = min(pathFlow, capacity[u][v]);
        }

        
        for (int v = sink; v != src; v = parent[v])
        {
            int u = parent[v];

            capacity[u][v] -= pathFlow;
            capacity[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

int main()
{
    int N, M;
    cin >> N >> M;

    vector<vector<int>> adj(N);
    vector<vector<int>> capacity(N, vector<int>(N, 0));

    for (int i = 0; i < M; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;

        adj[u].push_back(v);
        adj[v].push_back(u); 

        capacity[u][v] += w;
    }

    int source = 0;
    int sink = N - 1;

    cout << edmondsKarp(adj, capacity, source, sink) << endl;

    return 0;
}