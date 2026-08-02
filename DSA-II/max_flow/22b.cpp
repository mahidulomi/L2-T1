#include <bits/stdc++.h>
using namespace std;

class Mouse
{
public:
    double x, y;

    Mouse() : x(0), y(0) {}
    Mouse(double x, double y)
    {
        this->x = x;
        this->y = y;
    }
};

class Hole
{
public:
    double x, y;
    int cap;

    Hole() : x(0), y(0), cap(0) {}
    Hole(double x, double y, int cap)
    {
        this->x = x;
        this->y = y;
        this->cap = cap;
    }
};

double get_dist(const Mouse &m, const Hole &h)
{
    return sqrt((m.x - h.x) * (m.x - h.x) + (m.y - h.y) * (m.y - h.y));
}

bool dfs(vector<vector<int>> &adj,
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

        for (int v : adj[u])
        {
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

int fordFulkerson(vector<vector<int>> &adj,
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

void solve(int t)
{
    int M, H;
    double R;
    if (!(cin >> M >> H >> R))
        return;

    vector<Mouse> mice(M);
    for (int i = 0; i < M; i++)
    {
        double x, y;
        cin >> x >> y;
        mice[i] = Mouse(x, y);
    }

    vector<Hole> holes(H);
    for (int i = 0; i < H; i++)
    {
        double x, y;
        int cap;
        cin >> x >> y >> cap;
        holes[i] = Hole(x, y, cap);
    }

    int src = 0;
    int sink = M + H + 1;
    int total_nodes = sink + 1;

    vector<vector<int>> adj(total_nodes);
    vector<vector<int>> capacity(total_nodes, vector<int>(total_nodes, 0));

    for (int i = 1; i <= M; i++)
    {
        adj[src].push_back(i);
        adj[i].push_back(src);
        capacity[src][i] = 1;
    }

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < H; j++)
        {
            if (get_dist(mice[i], holes[j]) <= R + 1e-9)
            {
                int mouse_node = i + 1;
                int hole_node = M + 1 + j;

                adj[mouse_node].push_back(hole_node);
                adj[hole_node].push_back(mouse_node);
                capacity[mouse_node][hole_node] = 1;
            }
        }
    }

    for (int j = 0; j < H; j++)
    {
        int hole_node = M + 1 + j;

        adj[hole_node].push_back(sink);
        adj[sink].push_back(hole_node);
        capacity[hole_node][sink] = holes[j].cap;
    }
    int ans = fordFulkerson(adj, capacity, src, sink);

    cout << "Case " << t << ": " << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (cin >> T)
    {
        for (int t = 1; t <= T; t++)
        {
            solve(t);
        }
    }

    return 0;
}