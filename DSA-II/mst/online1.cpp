#include <bits/stdc++.h>
using namespace std;
int primMst(int V, vector<vector<pair<int, int>>> &adj)
{
    vector<bool> inMST(V, false);
    // min heap
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 0}); // {weight, vertex}
    int minCost = 0;

    while (!pq.empty())
    {
        int u = pq.top().second;
        int weight = pq.top().first;
        pq.pop();

        if (inMST[u])
            continue;

        inMST[u] = true;
        minCost += weight;

        for (auto &edge : adj[u])
        {
            int v = edge.first;
            int w = edge.second;

            if (!inMST[v])
            {
                pq.push({w, v});
            }
        }
    }
    return minCost;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<pair<int,int>>> adj(n + 1);

    for(int i=1;i<=n;i++)
    {
        int p;
        cin >> p;

        // Virtual node 0
        adj[0].push_back({i,p});
        adj[i].push_back({0,p});
    }

    int m;
    cin >> m;

    while(m--)
    {
        int u,v,w;
        cin >> u >> v >> w;

        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    cout << primMst(n, adj) << '\n';
}
