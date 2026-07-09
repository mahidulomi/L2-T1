#include <bits/stdc++.h>
using namespace std;

class Edge
{
public:
    int u, v, wt, id;
    Edge(int u, int v, int wt, int id)
    {
        this->u = u;
        this->v = v;
        this->wt = wt;
        this->id = id;
    }
    
    // Weight anushare choto theke boro sort korar jonno
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
    }

    void addedge(int u, int v, int wt, int id)
    {
        edges.push_back(Edge(u, v, wt, id));
    }

    // DSU logic reset korar jonno (protibar skip korle reset lagbe)
    void initDSU()
    {
        par.resize(V + 1);
        rank.resize(V + 1, 0);
        for (int i = 1; i <= V; i++)
        {
            par[i] = i;
        }
    }

    int find(int x)
    {
        if (par[x] == x)
            return x;
        return par[x] = find(par[x]);
    }

    bool union_set(int a, int b)
    {
        int parA = find(a);
        int parB = find(b);
        if (parA == parB)
            return false;

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
        return true;
    }

    void findSecondMST()
    {
        // Shob edge-ke weight anushare choto theke boro sort korbo
        sort(edges.begin(), edges.end());

        // 1. Prothome first/original MST ber korbo
        initDSU();
        long long minCost = 0;
        vector<int> original_mst_edges; // Original MST-er edge id gulo rakhbo
        int edges_count = 0;

        for (int i = 0; i < edges.size(); i++)
        {
            Edge e = edges[i];
            if (union_set(e.u, e.v))
            {
                minCost += e.wt;
                original_mst_edges.push_back(e.id);
                edges_count++;
            }
        }

        // Jodi graph connected-i na hoy
        if (edges_count < V - 1)
        {
            cout << "Spanning tree possible na!" << endl;
            return;
        }

        cout << "Minimum cost of 1st MST: " << minCost << endl;

        // 2. Second MST khujar kaj
        long long secondMinCost = LLONG_MAX;

        // original MST er protiti edge ekta ekta kore skip korbo
        for (int skip_id : original_mst_edges)
        {
            initDSU(); // DSU reset
            long long current_cost = 0;
            int current_edges_count = 0;

            for (int i = 0; i < edges.size(); i++)
            {
                Edge e = edges[i];
                if (e.id == skip_id) continue; // Ei edge bad diye kaj hobe

                if (union_set(e.u, e.v))
                {
                    current_cost += e.wt;
                    current_edges_count++;
                }
            }

            // Jodi skip korar por-o full spanning tree (V-1 edges) toiri hoy
            if (current_edges_count == V - 1)
            {
                secondMinCost = min(secondMinCost, current_cost);
            }
        }

        if (secondMinCost == LLONG_MAX)
        {
            cout << "No Second MST exists!" << endl;
        }
        else
        {
            cout << "Minimum cost of 2nd MST: " << secondMinCost << endl;
        }
    }
};

int main()
{
    Graph g(4);

    // Node count: 4, edges track korar jonno tracking id ashbe sheshe
    g.addedge(1, 2, 10, 1);
    g.addedge(1, 3, 6, 2);
    g.addedge(1, 4, 5, 3);
    g.addedge(2, 3, 15, 4);
    g.addedge(3, 4, 4, 5);
    
    g.findSecondMST();

    return 0;
}