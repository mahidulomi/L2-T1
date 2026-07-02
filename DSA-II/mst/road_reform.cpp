#include <bits/stdc++.h>
using namespace std;

class Edge
{
public:
    int u, v, wt;
    Edge(int u, int v, int wt)
    {
        this->u = u;
        this->v = v;
        this->wt = wt;
    }
    bool operator<(const Edge &e) const
    {
        return this->wt < e.wt;
    }
};

class graph
{
    int V;
    vector<Edge> edges;
    vector<int> par, Rank;

public:
    graph(int V)
    {
        this->V = V;
        par.resize(V + 1);
        Rank.resize(V + 1, 0);

        for (int i = 0; i <= V; i++)
            par[i] = i;
    }

    void addEdge(int u, int v, int wt)
    {
        edges.push_back(Edge(u, v, wt));
    }

    int find(int x)
    {
        if (par[x] == x)
            return x;
        return par[x] = find(par[x]);
    }

    void union_set(int a, int b)
    {
        int parA = find(a);
        int parB = find(b);

        if (parA == parB)
            return;

        if (Rank[parA] == Rank[parB])
        {
            par[parB] = parA;
            Rank[parA]++;
        }
        else if (Rank[parA] > Rank[parB])
        {
            par[parB] = parA;
        }
        else
        {
            par[parA] = parB;
        }
    }

    long long kruskal(int k)
    {
        sort(edges.begin(), edges.end());

       

        long long ans = 0;

        for (auto e : edges)
        {
            if (find(e.u) != find(e.v))
            {
                union_set(e.u, e.v);

                if (e.wt > k)
                    ans += (e.wt - k);
            }
        }

        return ans;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
    {
        int n, m, k;
        cin >> n >> m >> k;

        graph g(n);

        long long best = LLONG_MAX;

        for (int i = 0; i < m; i++)
        {
            int u, v, s;
            cin >> u >> v >> s;

            g.addEdge(u, v, s);

            best = min(best, 1LL * abs(s - k));
        }

        long long ans = g.kruskal(k);

        if (ans == 0)
            cout << best << "\n";
        else
            cout << ans << "\n";
    }

    return 0;
}