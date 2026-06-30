#include <bits/stdc++.h>
using namespace std;
class Edge
{ 
    public :
    int u, v, wt;
    Edge(int u, int v, int wt)
    {
        this->u = u;
        this->v = v;
        this->wt = wt;
    }
    //  comoparator function for sorting edges based on weight
    bool operator<(const Edge &e) const
    {
        return this->wt < e.wt;
    }
};

class Graph
{
    int V;
    vector<Edge> edges;
    vector<int> par, rank;

public:
    Graph(int V)
    {
        this->V = V;
        for (int i = 0; i < V; i++)
        {
            par.push_back(i);
            rank.push_back(0);
        }
    }
    void addedge(int u, int v, int wt)
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

        if (rank[parB] == rank[parA])
        {

            par[parB] = parA;
            rank[parA]++;
        }
        else if (rank[parA] > rank[parB])
        {
            par[parB] = parA;
        }
        else
        {
            par[parA] = parB;
        }
    }
    void kruskalMST()
    {
        sort(edges.begin(), edges.end());
        int minCost = 0;
        for (int i = 0; i < edges.size(); i++)
        {
            Edge e = edges[i];
            int parU = find(e.u);
            int parV = find(e.v);
            if (parU != parV)
            {
                union_set(parU, parV);
                minCost += e.wt;
            }
        }
        cout << "Minimum cost of MST: " << minCost << endl;
    }
};

int main()
{
    Graph g(4);

    g.addedge(0, 1, 10);
    g.addedge(0, 2, 6);
    g.addedge(0, 3, 5);
    g.addedge(1, 2, 15);
    g.addedge(2, 3, 4);
    g.kruskalMST();
}