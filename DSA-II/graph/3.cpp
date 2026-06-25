#include <bits/stdc++.h>
using namespace std;
class Graph
{
    int n, m;
    vector<vector<int>> adj;
    vector<int> cat;
    int ans;

public:
    Graph(int n, int m)
    {
        this->n = n;
        this->m = m;
        adj.resize(n + 1);
        cat.resize(n + 1);
        ans = 0;
    }

    void setCats()
    {
        for (int i = 1; i <= n; i++)
            cin >> cat[i];
    }
    void addedges(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int u, int parent, int consecutive)
    {
        if (cat[u])
            consecutive++;
        else
            consecutive = 0;

        if (consecutive > m)
            return;

        bool isLeaf = true;
        for (int v : adj[u])
        {
            if (v != parent)
            {
                isLeaf = false;
                dfs(v, u, consecutive);
            }
        }

        if (isLeaf)
            ans++;
    }
    int solve()
    {
        dfs(1, 0, 0);
        return ans;
    }
};

int main()
{
    int n, m;
    cin >> n >> m;
    Graph g(n, m);
    g.setCats();

    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        g.addedges(u, v);
    }
    cout << g.solve() << '\n';
}