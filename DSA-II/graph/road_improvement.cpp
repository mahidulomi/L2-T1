#include <bits/stdc++.h>
using namespace std;
class graph
{
    int V;
    vector<vector<int>> adj;

public:
    graph(int v)
    {
        this->V = v;
        adj.resize(v + 1);
    }
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int solve()
    {
        
    }
};
int main()
{
    int n;
    cin >> n;
    graph g(n);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }
    cout << g.solve() << endl;

    return 0;
}