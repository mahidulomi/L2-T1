#include <bits/stdc++.h>
using namespace std;
class Edge
{
public:
    int dest;
    int weight;
    Edge(int d, int w)
    {
        dest = d;
        weight = w;
    }
};
void bellmanFord(int V, vector<vector<Edge>> &g, int src)
{
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    for (int i = 1; i <= V - 1; i++)
    {
        for (int u = 0; u < V; u++)
        {
            for (auto &edge : g[u])
            {
                int v = edge.dest;
                int weight = edge.weight;

                if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                {
                    dist[v] = dist[u] + weight;
                }
            }
        }
    }

    cout << "Vertex Distance from Source\n";
    for (int i = 0; i < V; i++)
    {
        cout << i << "\t\t" << dist[i] << "\n";
    }
}


int main()
{
    int V = 6;
    vector<vector<Edge>> g(V);
    g[0].push_back(Edge(1, 4));
    g[0].push_back(Edge(2, 3));
    g[1].push_back(Edge(2, 1));
    g[1].push_back(Edge(3, 2));
    g[2].push_back(Edge(3, 4));
    g[3].push_back(Edge(4, 2));
    g[4].push_back(Edge(5, 3));
    bellmanFord(V, g, 0);
    return 0;
}
