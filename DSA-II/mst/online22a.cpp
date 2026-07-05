#include <bits/stdc++.h>
using namespace std;
int primMst(int V, vector<vector<pair<int, int>>> &adj)
{
    vector<bool> inMST(V, false);
    // min heap
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 0}); // {weight, vertex}
    int minCost = 1;
    int secondMinCost = 1;

    while (!pq.empty())
    {
        int u = pq.top().second;
        int weight = pq.top().first;
        pq.pop();

        if (inMST[u])
            continue;

        inMST[u] = true;
        secondMinCost = minCost;
        minCost *= weight;

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
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    } 
}