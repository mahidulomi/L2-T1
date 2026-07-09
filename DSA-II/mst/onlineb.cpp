#include <bits/stdc++.h>
using namespace std;

class Edge
{
public:
    int u, v;
    long long wt;

    Edge(int u, int v, long long wt)
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

        parent.resize(V + 1);
        Rank.resize(V + 1, 0);

        for (int i = 1; i <= V; i++)
            parent[i] = i;
    }

    void addEdge(int u, int v, long long wt)
    {
        edges.push_back(Edge(u, v, wt));
    }

    int find(int x)
    {
        if (parent[x] == x)
            return x;

        return parent[x] = find(parent[x]);
    }

    void union_set(int a, int b)
    {
        int pa = find(a);
        int pb = find(b);

        if (pa == pb)
            return;

        if (Rank[pa] < Rank[pb])
            parent[pa] = pb;
        else if (Rank[pa] > Rank[pb])
            parent[pb] = pa;
        else
        {
            parent[pb] = pa;
            Rank[pa]++;
        }
    }

    void kruskal(int M, long long totalCost)
    {
        sort(edges.begin(), edges.end());

        vector<Edge> mst;
        long long mstCost = 0;
        int cnt = 0;

        for (auto &e : edges)
        {
            if (find(e.u) != find(e.v))
            {
                union_set(e.u, e.v);
                mst.push_back(e);
                mstCost += e.wt;
                cnt++;
            }
        }
 
        if (cnt != V - 1)
        {
            cout << "Impossible\n";
            return;
        }

        cout << "Routes shut down: " << M - (V - 1) << endl;
        cout << "Total savings: " << totalCost - mstCost << endl;
        cout << "Operational routes:\n";

        for (auto &e : mst)
        {
            cout << e.u << " " << e.v << " " << e.wt << endl;
        }
    }
};

int main()
{
    int N, M;
    cin >> N >> M;

    Graph g(N);

    long long totalCost = 0;

    for (int i = 0; i < M; i++)
    {
        int u, v;
        long long w;

        cin >> u >> v >> w;

        g.addEdge(u, v, w);
        totalCost += w;
    }

    g.kruskal(M, totalCost);

    return 0;
}