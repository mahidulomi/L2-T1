#include <bits/stdc++.h>
using namespace std;

class Edge {
public:
    int u, v, wt, id;
    bool is_capital;
    int current_wt;

    Edge(int u, int v, int wt, int id) {
        this->u = u;
        this->v = v;
        this->wt = wt;
        this->id = id;
        this->is_capital = (u == 1 || v == 1);
        this->current_wt = wt;
    }
};

class graph {
    int V;
    vector<Edge> edges;
    vector<int> par, rank_arr;
    int k;

public:
    graph(int V, int k) {
        this->V = V;
        this->k = k;
        par.resize(V + 1);
        rank_arr.resize(V + 1, 0);
        reset_dsu();
    }

    void addedge(int u, int v, int wt, int id) {
        edges.push_back(Edge(u, v, wt, id));
    }

    void reset_dsu() {
        for (int i = 0; i <= V; i++) {
            par[i] = i;
            rank_arr[i] = 0;
        }
    }

    int find(int x) {
        if (par[x] == x) return x;
        return par[x] = find(par[x]);
    }

    bool union_set(int a, int b) {
        int parA = find(a);
        int parB = find(b);
        if (parA == parB) return false;
        
        if (rank_arr[parA] < rank_arr[parB]) {
            par[parA] = parB;
        } else if (rank_arr[parA] > rank_arr[parB]) {
            par[parB] = parA;
        } else {
            par[parB] = parA;
            rank_arr[parA]++;
        }
        return true;
    }

    pair<int, int> run_kruskal(int lambda, bool prefer_capital) {
        for (auto &e : edges) {
            if (e.is_capital) e.current_wt = e.wt + lambda;
            else e.current_wt = e.wt;
        }

        sort(edges.begin(), edges.end(), [prefer_capital](const Edge &a, const Edge &b) {
            if (a.current_wt != b.current_wt) return a.current_wt < b.current_wt;
            if (a.is_capital != b.is_capital) {
                return prefer_capital ? a.is_capital : !a.is_capital;
            }
            return a.id < b.id;
        });

        reset_dsu();
        int total_edges = 0;
        int capital_count = 0;

        for (const auto &e : edges) {
            if (union_set(e.u, e.v)) {
                total_edges++;
                if (e.is_capital) capital_count++;
            }
        }
        return make_pair(total_edges, capital_count);
    }

    void kruskal() {
        int low = -100005, high = 100005;
        int opt_lambda = -2e9;
        bool possible = false;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            pair<int, int> min_res = run_kruskal(mid, false);
            int edges_min = min_res.first;
            int cap_min = min_res.second;

            pair<int, int> max_res = run_kruskal(mid, true);
            int edges_max = max_res.first;
            int cap_max = max_res.second;

            if (edges_max < V - 1) {
                cout << -1 << "\n";
                return;
            }

            if (k >= cap_min && k <= cap_max) {
                opt_lambda = mid;
                possible = true;
                break;
            } else if (cap_max < k) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        if (!possible) {
            cout << -1 << "\n";
            return;
        }

        for (auto &e : edges) {
            if (e.is_capital) e.current_wt = e.wt + opt_lambda;
            else e.current_wt = e.wt;
        }

        sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
            if (a.current_wt != b.current_wt) return a.current_wt < b.current_wt;
            if (a.is_capital != b.is_capital) return a.is_capital;
            return a.id < b.id;
        });

        reset_dsu();
        vector<int> final_mst;
        int current_cap = 0;

        for (const auto &e : edges) {
            if (e.is_capital) {
                if (current_cap < k && find(e.u) != find(e.v)) {
                    union_set(e.u, e.v);
                    final_mst.push_back(e.id);
                    current_cap++;
                }
            }
        }

        for (const auto &e : edges) {
            if (!e.is_capital) {
                if (union_set(e.u, e.v)) {
                    final_mst.push_back(e.id);
                }
            }
        }

        if (final_mst.size() != V - 1 || current_cap != k) {
            cout << -1 << "\n";
        } else {
            cout << final_mst.size() << "\n";
            for (int i = 0; i < final_mst.size(); i++) {
                cout << final_mst[i] << (i == final_mst.size() - 1 ? "" : " ");
            }
            cout << "\n";
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    if (!(cin >> n >> m >> k)) return 0;

    graph g(n, k);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addedge(u, v, w, i);
    }

    g.kruskal();

    return 0;
}