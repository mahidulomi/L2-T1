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


bool printRoute(int u, int sink, vector<vector<edge>> &adj_original, vector<vector<int>> &capacity, vector<int> &path)
{
    path.push_back(u);
    if (u == sink) return true;

    for (auto e : adj_original[u])
    {
        int v = e.V;
        
        if (capacity[u][v] == 0)
        {
            capacity[u][v] = -1; 
            if (printRoute(v, sink, adj_original, capacity, path))
                return true;
        }
    }

    path.pop_back();
    return false;
}


void solve(int t)
{
    int N, M;
    if (!(cin >> N >> M)) return;

    int src = 1;   
    int sink = N;  

    vector<vector<edge>> adj(N + 1);
    vector<vector<edge>> adj_original(N + 1); 
    vector<vector<int>> capacity(N + 1, vector<int>(N + 1, 0));

    for (int i = 0; i < M; i++)
    {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(edge(v));
        adj[v].push_back(edge(u)); 

        adj_original[u].push_back(edge(v)); 
        capacity[u][v] += 1; 
    }

    int maxPaths = fordFulkerson(adj, capacity, src, sink);

   
    cout << "Case " << t << ": " << maxPaths << "\n";

    if (maxPaths == 0)
    {
        cout << "No escape route possible! The Professor needs a new plan.\n";
    }
    else
    {
        
        for (int i = 0; i < maxPaths; i++)
        {
            vector<int> path;
            printRoute(src, sink, adj_original, capacity, path);

            for (size_t j = 0; j < path.size(); j++)
            {
                cout << path[j] << (j + 1 == path.size() ? "" : " -> ");
            }
            cout << "\n";
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (cin >> T)
    {
        // [ADDED] T সংখ্যক টেস্ট কেসের জন্য লুপ
        for (int t = 1; t <= T; t++)
        {
            solve(t);
        }
    }

    return 0;
}