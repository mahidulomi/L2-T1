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

// Edmonds-Karp uses BFS to find the shortest augmenting path
bool bfs(const vector<vector<edge>> &adj,
         const vector<vector<int>> &capacity,
         vector<int> &parent,
         int src,
         int sink)
{
    int n = adj.size();

    vector<bool> vis(n, false);
    queue<int> q;

    q.push(src);
    vis[src] = true;
    parent[src] = -1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (auto e : adj[u])
        {
            int v = e.V;

            if (!vis[v] && capacity[u][v] > 0)
            {
                vis[v] = true;
                parent[v] = u;
                q.push(v);

                if (v == sink)
                    return true;
            }
        }
    }

    return false;
}

int edmondsKarp(const vector<vector<edge>> &adj,
                 vector<vector<int>> capacity, // Passed by value to work on a copy
                 int src,
                 int sink)
{
    int n = adj.size();
    vector<int> parent(n);
    int maxFlow = 0;

    while (bfs(adj, capacity, parent, src, sink))
    {
        int pathFlow = INT_MAX;

        // Find minimum residual capacity along the path
        for (int v = sink; v != src; v = parent[v])
        {
            int u = parent[v];
            pathFlow = min(pathFlow, capacity[u][v]);
        }

        // Update residual capacities
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

struct Proposal
{
    int u, v, c;
};

void solve()
{
    int N, M;
    if (!(cin >> N >> M))
        return;

    // Node 1 = Uttara (Source), Node N = Motijheel (Sink)
    int src = 1;
    int sink = N;
    int total_nodes = N + 1;

    vector<vector<edge>> base_adj(total_nodes);
    vector<vector<int>> base_capacity(total_nodes, vector<int>(total_nodes, 0));

    // Input existing roads
    for (int i = 0; i < M; i++)
    {
        int u, v, c;
        cin >> u >> v >> c;

        base_adj[u].push_back(edge(v));
        base_adj[v].push_back(edge(u)); // Residual reverse edge
        base_capacity[u][v] += c;
    }

    int P;
    cin >> P;

    vector<Proposal> proposals(P);
    for (int i = 0; i < P; i++)
    {
        cin >> proposals[i].u >> proposals[i].v >> proposals[i].c;
    }

    // 1. Calculate Base Max Flow without any new flyover
    int base_max_flow = edmondsKarp(base_adj, base_capacity, src, sink);

    vector<int> valid_proposals;

    // 2. Evaluate each flyover project independently
    for (int i = 0; i < P; i++)
    {
        vector<vector<edge>> adj = base_adj;
        vector<vector<int>> capacity = base_capacity;

        int u = proposals[i].u;
        int v = proposals[i].v;
        int c = proposals[i].c;

        // Add proposed flyover
        adj[u].push_back(edge(v));
        adj[v].push_back(edge(u));
        capacity[u][v] += c;

        // Calculate new flow
        int new_max_flow = edmondsKarp(adj, capacity, src, sink);

        // Check if flow strictly increases
        if (new_max_flow > base_max_flow)
        {
            valid_proposals.push_back(i + 1); // 1-based index corresponding to input order
        }
    }

    // Output Result
    if (valid_proposals.empty())
    {
        cout << "None\n";
    }
    else
    {
        for (int i = 0; i < (int)valid_proposals.size(); i++)
        {
            cout << valid_proposals[i] << (i == (int)valid_proposals.size() - 1 ? "" : " ");
        }
        cout << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}