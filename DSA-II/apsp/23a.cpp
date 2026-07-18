#include <bits/stdc++.h>
using namespace std;

int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (cin >> n) 
    {
        vector<string> names(n);
        map<string, int> name_to_id;
        
        for (int i = 0; i < n; i++) 
        {
            cin >> names[i];
            name_to_id[names[i]] = i;
        }

        vector<vector<double>> dist(n, vector<double>(n, 0.0));
        for (int i = 0; i < n; i++) 
        {
            dist[i][i] = 1.0;
        }

        int m;
        cin >> m;
        for (int i = 0; i < m; i++) 
        {
            string u_str, v_str;
            double rate;
            cin >> u_str >> rate >> v_str;
            
            int u = name_to_id[u_str];
            int v = name_to_id[v_str];
            dist[u][v] = max(dist[u][v], rate);
        }

        // Floyd-Warshall to find max path between any two different nodes
        for (int k = 0; k < n; k++) 
        {
            for (int i = 0; i < n; i++) 
            {
                for (int j = 0; j < n; j++) 
                {
                    if (dist[i][k] > 0 && dist[k][j] > 0) 
                    {
                        dist[i][j] = max(dist[i][j], dist[i][k] * dist[k][j]);
                    }
                }
            }
        }

        // Check if node 'i' can participate in any arbitrage cycle via node 'j'
        vector<string> result;
        for (int i = 0; i < n; i++) 
        {
            bool can_arbitrage = false;
            for (int j = 0; j < n; j++) 
            {
                if (dist[i][j] > 0 && dist[j][i] > 0) 
                {
                    if (dist[i][j] * dist[j][i] > 1.0) 
                    {
                        can_arbitrage = true;
                        break;
                    }
                }
            }
            if (can_arbitrage) 
            {
                result.push_back(names[i]);
            }
        }

        if (result.empty()) 
        {
            cout << "No Arbitrage\n";
        } 
        else 
        {
            for (const string& name : result) 
            {
                cout << name << "\n";
            }
        }
    }

    return 0;
}