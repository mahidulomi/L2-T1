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

        // Find minimum residual capacity
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

    int P, C;
    if (!(cin >> P >> C)) return 0;

    // Node layout:
    // Power Plants: 0 to P-1
    // Cities: P to P+C-1
    // Super Source: P+C
    // Super Sink: P+C+1
    
    int total_nodes = P + C + 2;
    int super_source = P + C;
    int super_sink = P + C + 1;

    vector<vector<edge>> adj(total_nodes);
    vector<vector<int>> capacity(total_nodes, vector<int>(total_nodes, 0));

    // 1. Connect Super Source to each Power Plant
    for (int i = 0; i < P; i++)
    {
        int cap;
        cin >> cap;

        adj[super_source].push_back(edge(i));
        adj[i].push_back(edge(super_source)); // Reverse edge for residual graph

        capacity[super_source][i] += cap;
    }

    // 2. Connect each City to Super Sink
    for (int j = 0; j < C; j++)
    {
        int city_node = P + j;
        int demand;
        cin >> demand;

        adj[city_node].push_back(edge(super_sink));
        adj[super_sink].push_back(edge(city_node)); 

        capacity[city_node][super_sink] += demand;
    }

  
    int M;
    cin >> M;

    for (int i = 0; i < M; i++)
    {
        int u, v, cap;
        cin >> u >> v >> cap;

        adj[u].push_back(edge(v));
        adj[v].push_back(edge(u));

        capacity[u][v] += cap; 
    }

   
    cout << fordFulkerson(adj, capacity, super_source, super_sink) << endl;

    return 0;
}