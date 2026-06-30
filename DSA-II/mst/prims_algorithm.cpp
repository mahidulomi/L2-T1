#include <bits/stdc++.h>
using namespace std;
int primMst(int V, vector<vector<pair<int, int>>> &adj)
{
    vector<bool> inMST(V, false);
    // min heap
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 0}); // {weight, vertex}
    int minCost = 0;

    while(!pq.empty())
    {
        int u = pq.top().second;
        int weight = pq.top().first;
        pq.pop();

        if(inMST[u]) continue;

        inMST[u] = true;
        minCost += weight;

        for(auto &edge : adj[u])
        {
            int v = edge.first;
            int w = edge.second;

            if(!inMST[v])
            {
                pq.push({w, v});
            }
        }
    }
    return minCost;
}

int main()
{
    int V = 4;
    vector<vector<pair<int, int>>> adj(V);
//  undirected graph for prim's algorithm

    adj[0].push_back({1, 10});
    adj[0].push_back({2, 6});
    adj[0].push_back({3, 5});
    adj[1].push_back({0, 10});
    adj[1].push_back({2, 5});
    adj[2].push_back({0, 6});
    adj[2].push_back({1, 5});
    adj[3].push_back({0, 5});
    adj[3].push_back({2, 5});

    cout<< "Mininum Cost Spanning Tree: " <<primMst(V,adj) << endl;
    return 0;
}