#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;
class edge
{
public:
    int u, v, wt;
    edge(int u, int v, int wt)
    {
        this->u = u;
        this->v = v;
        this->wt = wt;
    }
    bool operator<(const edge &e) const
    {
        return this->wt < e.wt;
    }
};
class graph
{
    int V;
    vector<edge> edges;
    vector<int> parent, rank;
    int m;

public:
    graph(int V, int m)
    {
        this->V = V;
        parent.resize(V + 1);
        rank.resize(V + 1, 0);

        for (int i = 1; i <= V; i++)
            parent[i] = i;
        this->m = m;
    }
    void addedge(int u, int v, int wt)
    {
        edges.push_back(edge(u, v, wt));
    }
    int find(int x)
    {
        if (parent[x] == x)
            return x;
        return parent[x] = find(parent[x]);
    }
    void union_set(int a, int b)
    {
        int parA = find(a);
        int parB = find(b);
        if (parA == parB)
            return;

        if (rank[parB] == rank[parA])
        {
            parent[parB] = parA;
            rank[parA]++;
        }
        else if (rank[parA] > rank[parB])
        {
            parent[parB] = parA;
        }
        else
        {
            parent[parA] = parB;
        }
    }
    void kruskal(long long total_cost, int number_of_edges)
    {
        vector<edge> ans;
        vector<edge> not_included;
        sort(edges.begin(), edges.end());
        int cost = 0;
        for (int i = 0; i < edges.size(); i++)
        {
            edge e = edges[i];
            if (find(e.u) != find(e.v))
            {
                union_set(e.u, e.v);
                cost += e.wt;
                ans.push_back(e);
            }
            if(find(e.u) == find(e.v))
            {
                not_included.push_back(e);
            }
        }
        if (ans.size() != V - 1)
        {
            cout << "IMPOSSIBLE\n";
            return;
        }
         for (auto e : not_included)
        {
            cout << e.u << " " << e.v << " " << e.wt << '\n';
        }
        cout << number_of_edges - ans.size() << endl;
        cout << total_cost - cost << endl;
        cout << cost << endl;

        for (auto e : ans)
        {
            cout << e.u << " " << e.v << " " << e.wt << '\n';
        }
    }
};

int main()
{
    int n, m;
    cin >> n >> m;
    graph g(n, m);
    long long total_cost = 0;
    int number_of_edges = 0;
    for (int i = 0; i < m; i++)
    {
        int u, v, wt;
        cin >> u >> v >> wt;
        g.addedge(u, v, wt);
        total_cost += wt;
        number_of_edges++;
    }
    g.kruskal(total_cost, number_of_edges);
}