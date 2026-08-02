#include <bits/stdc++.h>
using namespace std;

class edge
{
public:
    int V;

    edge(int V)
    {
        this->V = V;
    }
};

bool dfs(vector<vector<edge>> &adj,
         vector<vector<int>> &capacity,
         vector<int> &parent,
         int src,
         int sink)
{
    int n = adj.size();

    vector<bool> vis(n, false);
    stack<int> st;

    st.push(src);
    vis[src] = true;
    parent[src] = -1;

    while (!st.empty())
    {
        int u = st.top();
        st.pop();

        for (auto e : adj[u])
        {
            int v = e.V;

            if (!vis[v] && capacity[u][v] > 0)
            {
                vis[v] = true;
                parent[v] = u;
                st.push(v);

                if (v == sink)
                    return true;
            }
        }
    }

    return false;
}

int fordFulkerson(vector<vector<edge>> &adj,
                  vector<vector<int>> &capacity,
                  int src,
                  int sink)
{
    int n = adj.size();

    vector<int> parent(n);

    int maxFlow = 0;

    while (dfs(adj, capacity, parent, src, sink))
    {
        int pathFlow = INT_MAX;

        // Find minimum residual capacity along the augmenting path
        for (int v = sink; v != src; v = parent[v])
        {
            int u = parent[v];
            pathFlow = min(pathFlow, capacity[u][v]);
        }

        // Update residual graph
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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    if (!(cin >> N >> M)) return 0;

    int src, sink;
    cin >> src >> sink;

    vector<vector<edge>> adj(N);
    vector<vector<int>> capacity(N, vector<int>(N, 0));

    for (int i = 0; i < M; i++)
    {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(edge(v));
        adj[v].push_back(edge(u)); // Reverse edge for residual capacity flow

        capacity[u][v] += 1; // Each directed link allows 1 unit of flow
    }

    int maxPaths = fordFulkerson(adj, capacity, src, sink);

    if (maxPaths == 0)
    {
        cout << -1 << "\n";
    }
    else
    {
        cout << maxPaths << "\n";
    }

    return 0;
}