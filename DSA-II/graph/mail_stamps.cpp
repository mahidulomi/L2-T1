#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    unordered_map<long long, vector<long long>> adj;

    for(int i = 0; i < n; i++)
    {
        long long u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    long long start = -1;

    for(auto x : adj)
    {
        if(x.second.size() == 1)
        {
            start = x.first;
            break;
        }
    }

    vector<long long> ans;

    long long prev = -1;
    long long curr = start;

    while(true)
    {
        ans.push_back(curr);

        bool found = false;

        for(auto nxt : adj[curr])
        {
            if(nxt != prev)
            {
                prev = curr;
                curr = nxt;
                found = true;
                break;
            }
        }

        if(!found) break;
    }

    for(auto x : ans)
        cout << x << " ";
}