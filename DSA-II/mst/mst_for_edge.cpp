#include<bits/stdc++.h>
using namespace std;
int primsMst(int src, int n, vector<vector<pair<int,int>>> &adj)
{
    vector<bool> inMST(n, false);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, src});
    int mstWeight = 0;
    while(!pq.empty())
    {
        auto [wt, u] = pq.top();
        pq.pop();
        if(inMST[u]) continue;
        inMST[u] = true;
        mstWeight += wt;
        for(auto [v, edgeWt] : adj[u])
        {
            if(!inMST[v])
            {
                pq.push({edgeWt, v});
            }
        }
    }
    return mstWeight;
}
int main()
{
    int n, m;
    cin >> n>> m;
    vector<vector<pair<int,int>>> adj(n);
    for(int i = 0; i< n-1; i++)
    {
        int u, v, wt;
        cin >> u >> v >> wt;
        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt});
    }
    cout << primsMst(n, adj) << endl;
}