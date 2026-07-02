#include <bits/stdc++.h>
using namespace std;

class Planet
{
public:
    int id;
    int x, y, z;

    Planet() {}

    Planet(int id, int x, int y, int z)
    {
        this->id = id;
        this->x = x;
        this->y = y;
        this->z = z;
    }
    
};

class Edge
{
public:
    int u, v, wt;

    Edge() {}

    Edge(int u, int v, int wt)
    {
        this->u = u;
        this->v = v;
        this->wt = wt;
    }

    bool operator<(const Edge &e) const
    {
        return wt < e.wt;
    }
};

class Graph
{
    int V;
    vector<Edge> edges;
    vector<int> parent, Rank;

public:
    Graph(int V)
    {
        this->V = V;

        parent.resize(V);
        Rank.assign(V, 0);

        for (int i = 0; i < V; i++)
            parent[i] = i;
    }

    void addEdge(int u, int v, int wt)
    {
        edges.push_back(Edge(u, v, wt));
    }

    int Find(int x)
    {
        if (parent[x] == x)
            return x;

        return parent[x] = Find(parent[x]);
    }

    void Union(int a, int b)
    {
        a = Find(a);
        b = Find(b);

        if (a == b)
            return;

        if (Rank[a] < Rank[b])
            swap(a, b);

        parent[b] = a;

        if (Rank[a] == Rank[b])
            Rank[a]++;
    }

    long long Kruskal()
    {
        sort(edges.begin(), edges.end());

        long long cost = 0;

        for (Edge e : edges)
        {
            if (Find(e.u) != Find(e.v))
            {
                Union(e.u, e.v);
                cost += e.wt;
            }
        }

        return cost;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Planet> p;

    for (int i = 0; i < n; i++)
    {
        int x, y, z;
        cin >> x >> y >> z;

        p.push_back(Planet(i, x, y, z));
    }

    Graph g(n);

    // sort by x
    sort(p.begin(), p.end(), [](Planet a, Planet b)
         { return a.x < b.x; });

    for (int i = 0; i < n - 1; i++)
    {
        g.addEdge(p[i].id, p[i + 1].id,
                  abs(p[i].x - p[i + 1].x));
    }

    // sort by y
    sort(p.begin(), p.end(), [](Planet a, Planet b)
         { return a.y < b.y; });

    for (int i = 0; i < n - 1; i++)
    {
        g.addEdge(p[i].id, p[i + 1].id,
                  abs(p[i].y - p[i + 1].y));
    }

    // sort by z
    sort(p.begin(), p.end(), [](Planet a, Planet b)
         { return a.z < b.z; });

    for (int i = 0; i < n - 1; i++)
    {
        g.addEdge(p[i].id, p[i + 1].id,
                  abs(p[i].z - p[i + 1].z));
    }

    cout << g.Kruskal() << "\n";

    return 0;
}