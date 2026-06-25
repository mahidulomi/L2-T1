// topological sort using Kahn's algorithm
#include <bits/stdc++.h>
using namespace std;
class Graph
{
    int V;
    list<int> *adj;

public:
    Graph(int V)
    {
        this->V = V;
        adj = new list<int>[V];
    }
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        ; // only directed edges
    }
    void topologicalSort()
    {
        //   create a result vector to store the topological order
        vector<int> result;
        // 1. calculate inddegree for all vertices
        vector<int> indegree(V, 0);
        for (int u = 0; u < V; u++)
        {
            for (int v : adj[u])
            {
                indegree[v]++;
            }
        }

        // 2. create a queue and enqueue all vertices with indegree 0
        queue<int> q;
        for (int i = 0; i < V; i++)
        {
            if (indegree[i] == 0)
            {
                q.push(i);
            }
        }
        // 3. complete bfs
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            result.push_back(u);
            for (int v : adj[u])
            {
                indegree[v]--;
                if (indegree[v] == 0)
                {
                    q.push(v);
                }
            }
        }
        // print the topological order
        for (int u : result)
        {
            cout << u << " ";
        }
        cout << endl;
    }
};
int main()
{
    Graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    g.topologicalSort();
    return 0;
}