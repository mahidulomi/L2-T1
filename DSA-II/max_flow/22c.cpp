#include <bits/stdc++.h>
using namespace std;

class Person
{
public:
    int exp, age, crim, origin, weapon, trust, lang;

    Person() : exp(0), age(0), crim(0), origin(0), weapon(0), trust(0), lang(0) {}
    Person(int exp, int age, int crim, int origin, int weapon, int trust, int lang)
    {
        this->exp = exp;
        this->age = age;
        this->crim = crim;
        this->origin = origin;
        this->weapon = weapon;
        this->trust = trust;
        this->lang = lang;
    }
};


bool is_valid(const Person &m, const Person &p)
{
    if (abs(m.exp - p.exp) > 12) return false;       
    if (abs(m.age - p.age) > 5) return false;        
    if (m.crim != p.crim) return false;              
    if (m.origin != p.origin) return false;           
    if (m.weapon == 0 && p.weapon == 0) return false; 
    if (m.trust + p.trust < 10) return false;        
    if ((m.lang & p.lang) == 0) return false;        
    return true;
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
    int M, N;
    if (!(cin >> M >> N))
        return;

    vector<Person> members(M);
    for (int i = 0; i < M; i++)
    {
        int exp, age, crim, origin, weapon, trust, lang;
        cin >> exp >> age >> crim >> origin >> weapon >> trust >> lang;
        members[i] = Person(exp, age, crim, origin, weapon, trust, lang);
    }

    vector<Person> partners(N);
    for (int i = 0; i < N; i++)
    {
        int exp, age, crim, origin, weapon, trust, lang;
        cin >> exp >> age >> crim >> origin >> weapon >> trust >> lang;
        partners[i] = Person(exp, age, crim, origin, weapon, trust, lang);
    }

    int src = 0;
    int sink = M + N + 1;
    int total_nodes = sink + 1;

    vector<vector<int>> adj(total_nodes);
    vector<vector<int>> capacity(total_nodes, vector<int>(total_nodes, 0));

    // Source (0) to Members (1 ... M)
    for (int i = 1; i <= M; i++)
    {
        adj[src].push_back(i);
        adj[i].push_back(src);
        capacity[src][i] = 1;
    }

    // Members to Partners
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (is_valid(members[i], partners[j]))
            {
                int member_node = i + 1;
                int partner_node = M + 1 + j;

                adj[member_node].push_back(partner_node);
                adj[partner_node].push_back(member_node);
                capacity[member_node][partner_node] = 1;
            }
        }
    }

   
    for (int j = 0; j < N; j++)
    {
        int partner_node = M + 1 + j;

        adj[partner_node].push_back(sink);
        adj[sink].push_back(partner_node);
        capacity[partner_node][sink] = 1;
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