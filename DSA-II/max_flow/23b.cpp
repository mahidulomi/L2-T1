#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int N, M, P;
vector<vector<int>> cap;
vector<vector<int>> adj;


bool max_flow_bfs(int src, int sink, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[src] = -2;
    queue<pair<int, int>> q;
    q.push({src, INF});

    while (!q.empty()) {
        int u = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int v : adj[u]) {
            if (parent[v] == -1 && cap[u][v] > 0) {
                parent[v] = u;
                int new_flow = min(flow, cap[u][v]);
                if (v == sink) return true;
                q.push({v, new_flow});
            }
        }
    }
    return false;
}

void runMaxFlow(int src, int sink) {
    vector<int> parent(N + 1);
    while (max_flow_bfs(src, sink, parent)) {
        int path_flow = INF;
        for (int v = sink; v != src; v = parent[v]) {
            int u = parent[v];
            path_flow = min(path_flow, cap[u][v]);
        }
        for (int v = sink; v != src; v = parent[v]) {
            int u = parent[v];
            cap[u][v] -= path_flow;
            cap[v][u] += path_flow;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> N >> M)) return 0;

    cap.assign(N + 1, vector<int>(N + 1, 0));
    adj.resize(N + 1);

    for (int i = 0; i < M; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        if (cap[u][v] == 0 && cap[v][u] == 0) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        cap[u][v] += c;
    }

    int src = 1, sink = N;

  
    runMaxFlow(src, sink);

    
    vector<bool> fromSource(N + 1, false);
    queue<int> q1;
    q1.push(src);
    fromSource[src] = true;

    while (!q1.empty()) {
        int u = q1.front();
        q1.pop();
        for (int v : adj[u]) {
            if (!fromSource[v] && cap[u][v] > 0) {
                fromSource[v] = true;
                q1.push(v);
            }
        }
    }

   
    vector<bool> toSink(N + 1, false);
    queue<int> q2;
    q2.push(sink);
    toSink[sink] = true;

    while (!q2.empty()) {
        int u = q2.front();
        q2.pop();
        for (int v : adj[u]) {
            // v -> u ক্যাপাসিটি থাকলে মানে v থেকে u (বা Sink) এ যাওয়া সম্ভব
            if (!toSink[v] && cap[v][u] > 0) {
                toSink[v] = true;
                q2.push(v);
            }
        }
    }

    // ৪. ফ্লাইওভার প্রসেস করা
    cin >> P;
    vector<int> result;

    for (int i = 1; i <= P; i++) {
        int u, v, c;
        cin >> u >> v >> c;

        // Source থেকে u যাওয়া যায় এবং v থেকে Sink এ যাওয়া যায়
        if (fromSource[u] && toSink[v]) {
            result.push_back(i);
        }
    }

    // ৫. আউটপুট প্রিন্ট
    if (result.empty()) {
        cout << "None\n";
    } else {
        for (int i = 0; i < result.size(); i++) {
            cout << result[i] << (i == result.size() - 1 ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}