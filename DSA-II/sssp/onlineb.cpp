#include <bits/stdc++.h>
using namespace std;

// ১e১৮ ব্যবহার করছি ওভারফ্লো এড়াতে
const long long INF = 1e18; 

class Edge
{
public:
    int dest;
    long long weight; // int থেকে long long করা হলো
    Edge(int d, long long w)
    {
        dest = d;
        weight = w;
    }
};

// src প্যারামিটারটি বাদ দেওয়া হয়েছে
void dijkstra(int n, vector<vector<Edge>> &g, vector<int> &emergency)
{
    // ১-বেসড ইনডেক্সিং এর জন্য n + 1 সাইজ এবং long long টাইপ
    vector<long long> dist(n + 1, INF); 

    // min-heap: {distance, vertex}
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    
    for (int i = 0; i < emergency.size(); i++)
    {
        dist[emergency[i]] = 0;
        pq.push({0, emergency[i]});
    }

    while (!pq.empty())
    {
        int u = pq.top().second;
        long long d = pq.top().first; // কারেন্ট ডিস্টেন্স ট্র্যাকিং
        pq.pop();

        // অপটিমাইজেশন: যদি অলরেডি ছোট দূরত্ব প্রসেস হয়ে থাকে
        if (d > dist[u]) continue;

        for (auto &edge : g[u])
        {
            int v = edge.dest;
            long long weight = edge.weight;

            if (dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    // আউটপুট ফরম্যাট অনুযায়ী ১ থেকে n পর্যন্ত প্রিন্ট করা
    for (int i = 1; i <= n; i++)
    {
        if (dist[i] == INF)
        {
            cout << -1 << "\n";
        }
        else
        {
            cout << dist[i] << "\n";
        }
    }
}

int main()
{
    // ফাস্ট আইও (কন্টেস্টের জন্য জরুরি)
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    if (!(cin >> n >> m >> k)) return 0;

    vector<int> emergency(k);
    for (int i = 0; i < k; i++)
    {
        cin >> emergency[i];
    }

    vector<vector<Edge>> g(n + 1);
    // Read edges and build the REVERSED graph
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        // এজ উল্টে দেওয়া হলো: u -> v এর বদলে v -> u
        g[v].push_back(Edge(u, w)); 
    }

    // n + 1 এর জায়গায় n পাঠানো হলো এবং src বাদ দেওয়া হলো
    dijkstra(n, g, emergency); 
    return 0;
}