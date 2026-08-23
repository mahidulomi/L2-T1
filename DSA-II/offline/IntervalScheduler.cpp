#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <unordered_map>
#include <climits>
#include <windows.h> 

using namespace std;

struct IntervalNode {
    int id;
    int s;
    int e;
    int maxEnd;
    int height;
    IntervalNode* left;
    IntervalNode* right;

    IntervalNode(int id, int s, int e)
        : id(id), s(s), e(e), maxEnd(e), height(1), left(nullptr), right(nullptr) {}
};

class IntervalAVLTree {
private:
    IntervalNode* root = nullptr;

    int getHeight(IntervalNode* n) { return n ? n->height : 0; }
    int getMaxEnd(IntervalNode* n) { return n ? n->maxEnd : INT_MIN; }
    int getBalanceFactor(IntervalNode* n) { return n ? getHeight(n->left) - getHeight(n->right) : 0; }

    void updateNode(IntervalNode* n) {
        if (n) {
            n->height = 1 + max(getHeight(n->left), getHeight(n->right));
            n->maxEnd = max({n->e, getMaxEnd(n->left), getMaxEnd(n->right)});
        }
    }

    IntervalNode* rotateRight(IntervalNode* y) {
        IntervalNode* x = y->left;
        IntervalNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        updateNode(y);
        updateNode(x);
        return x;
    }

    IntervalNode* rotateLeft(IntervalNode* x) {
        IntervalNode* y = x->right;
        IntervalNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        updateNode(x);
        updateNode(y);
        return y;
    }

    IntervalNode* rebalance(IntervalNode* node) {
        if (!node) return nullptr;
        updateNode(node);
        int balance = getBalanceFactor(node);

        if (balance > 1 && getBalanceFactor(node->left) >= 0) return rotateRight(node);
        if (balance > 1 && getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && getBalanceFactor(node->right) <= 0) return rotateLeft(node);
        if (balance < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rotateLeft(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    bool isLess(int s1, int id1, int s2, int id2) {
        if (s1 != s2) return s1 < s2;
        return id1 < id2;
    }

    IntervalNode* insertHelper(IntervalNode* node, int id, int s, int e) {
        if (!node) return new IntervalNode(id, s, e);

        if (isLess(s, id, node->s, node->id)) node->left = insertHelper(node->left, id, s, e);
        else node->right = insertHelper(node->right, id, s, e);
        
        return rebalance(node);
    }

    IntervalNode* getMinNode(IntervalNode* node) {
        IntervalNode* curr = node;
        while (curr && curr->left) curr = curr->left;
        return curr;
    }

    IntervalNode* deleteHelper(IntervalNode* node, int id, int s) {
        if (!node) return nullptr;

        if (isLess(s, id, node->s, node->id)) {
            node->left = deleteHelper(node->left, id, s);
        } else if (isLess(node->s, node->id, s, id)) {
            node->right = deleteHelper(node->right, id, s);
        } else {
            if (!node->left || !node->right) {
                IntervalNode* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            } else {
                IntervalNode* succ = getMinNode(node->right);
                node->id = succ->id;
                node->s = succ->s;
                node->e = succ->e;
                node->right = deleteHelper(node->right, succ->id, succ->s);
            }
        }
        return rebalance(node);
    }

    bool hasConflict(IntervalNode* node, int qs, int qe) {
        if (!node) return false;
        if (node->s < qe && qs < node->e) return true;
        if (node->left && node->left->maxEnd > qs) {
            if (hasConflict(node->left, qs, qe)) return true;
        }
        if (node->right && node->s < qe) {
            if (hasConflict(node->right, qs, qe)) return true;
        }
        return false;
    }

    void findOverlaps(IntervalNode* node, int qs, int qe, vector<int>& res) {
        if (!node) return;
        if (node->left && node->left->maxEnd > qs) findOverlaps(node->left, qs, qe, res);
        if (node->s < qe && qs < node->e) res.push_back(node->id);
        if (node->right && node->s < qe) findOverlaps(node->right, qs, qe, res);
    }

    void findAt(IntervalNode* node, int t, vector<int>& res) {
        if (!node) return;
        if (node->left && node->left->maxEnd > t) findAt(node->left, t, res);
        if (node->s <= t && t < node->e) res.push_back(node->id);
        if (node->right && node->s <= t) findAt(node->right, t, res);
    }

    IntervalNode* findNext(IntervalNode* node, int t) {
        IntervalNode* curr = node;
        IntervalNode* candidate = nullptr;
        while (curr) {
            if (curr->s >= t) {
                candidate = curr;
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }
        return candidate;
    }

    string formatTree(IntervalNode* node) {
        if (!node) return "";
        if (!node->left && !node->right) return to_string(node->id);
        return to_string(node->id) + "(" + formatTree(node->left) + "," + formatTree(node->right) + ")";
    }

    void destroy(IntervalNode* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    ~IntervalAVLTree() { destroy(root); }

    void add(int id, int s, int e) { root = insertHelper(root, id, s, e); }
    void remove(int id, int s) { root = deleteHelper(root, id, s); }
    bool conflict(int s, int e) { return hasConflict(root, s, e); }
    vector<int> overlaps(int s, int e) {
        vector<int> res;
        findOverlaps(root, s, e, res);
        return res;
    }
    vector<int> at(int t) {
        vector<int> res;
        findAt(root, t, res);
        return res;
    }
    IntervalNode* next(int t) { return findNext(root, t); }
    string getTreeString() { return formatTree(root); }
};

int main(int argc, char* argv[]) {
    if (argc < 3) return 1;

    ifstream infile(argv[1]);
    ofstream outfile(argv[2]);

    if (!infile.is_open() || !outfile.is_open()) return 1;

    // Windows Timer Resolution Setup
    LARGE_INTEGER frequency, t1, t2;
    QueryPerformanceFrequency(&frequency);

    IntervalAVLTree tree;
    unordered_map<int, pair<int, int>> idMap;
    int autoNextId = 1;

    string line;

    long long add_cnt = 0, remove_cnt = 0, update_cnt = 0, conflict_cnt = 0, overlaps_cnt = 0, at_cnt = 0, next_cnt = 0;
    double add_time = 0, remove_time = 0, update_time = 0, conflict_time = 0, overlaps_time = 0, at_time = 0, next_time = 0;

    while (getline(infile, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string cmd;
        ss >> cmd;

        if (cmd == "ADD") {
            int s, e; ss >> s >> e;
            int id = autoNextId++;

            add_cnt++;
            QueryPerformanceCounter(&t1);
            tree.add(id, s, e);
            QueryPerformanceCounter(&t2);
            add_time += ((t2.QuadPart - t1.QuadPart) * 1e9) / frequency.QuadPart;

            idMap[id] = {s, e};
            outfile << tree.getTreeString() << "\n";
        } 
        else if (cmd == "REMOVE") {
            int id; ss >> id;
            if (idMap.find(id) == idMap.end()) {
                outfile << "not found\n";
            } else {
                auto p = idMap[id];
                remove_cnt++;

                QueryPerformanceCounter(&t1);
                tree.remove(id, p.first);
                QueryPerformanceCounter(&t2);
                remove_time += ((t2.QuadPart - t1.QuadPart) * 1e9) / frequency.QuadPart;

                idMap.erase(id);
                outfile << tree.getTreeString() << "\n";
            }
        } 
        else if (cmd == "UPDATE") {
            int id, ns, ne; ss >> id >> ns >> ne;
            if (idMap.find(id) == idMap.end()) {
                outfile << "not found\n";
            } else {
                auto p = idMap[id];
                update_cnt++;

                QueryPerformanceCounter(&t1);
                tree.remove(id, p.first);
                tree.add(id, ns, ne);
                QueryPerformanceCounter(&t2);
                update_time += ((t2.QuadPart - t1.QuadPart) * 1e9) / frequency.QuadPart;

                idMap[id] = {ns, ne};
                outfile << tree.getTreeString() << "\n";
            }
        } 
        else if (cmd == "CONFLICT") {
            int s, e; ss >> s >> e;
            conflict_cnt++;

            QueryPerformanceCounter(&t1);
            bool hasConf = tree.conflict(s, e);
            QueryPerformanceCounter(&t2);
            conflict_time += ((t2.QuadPart - t1.QuadPart) * 1e9) / frequency.QuadPart;

            outfile << (hasConf ? "yes" : "no") << "\n";
        } 
        else if (cmd == "OVERLAPS") {
            int s, e; ss >> s >> e;
            overlaps_cnt++;

            QueryPerformanceCounter(&t1);
            vector<int> res = tree.overlaps(s, e);
            QueryPerformanceCounter(&t2);
            overlaps_time += ((t2.QuadPart - t1.QuadPart) * 1e9) / frequency.QuadPart;

            if (res.empty()) outfile << "none\n";
            else {
                for (size_t i = 0; i < res.size(); i++) {
                    outfile << res[i] << (i + 1 == res.size() ? "" : " ");
                }
                outfile << "\n";
            }
        } 
        else if (cmd == "AT") {
            int t; ss >> t;
            at_cnt++;

            QueryPerformanceCounter(&t1);
            vector<int> res = tree.at(t);
            QueryPerformanceCounter(&t2);
            at_time += ((t2.QuadPart - t1.QuadPart) * 1e9) / frequency.QuadPart;

            if (res.empty()) outfile << "none\n";
            else {
                for (size_t i = 0; i < res.size(); i++) {
                    outfile << res[i] << (i + 1 == res.size() ? "" : " ");
                }
                outfile << "\n";
            }
        } 
        else if (cmd == "NEXT") {
            int t; ss >> t;
            next_cnt++;

            QueryPerformanceCounter(&t1);
            IntervalNode* resNode = tree.next(t);
            QueryPerformanceCounter(&t2);
            next_time += ((t2.QuadPart - t1.QuadPart) * 1e9) / frequency.QuadPart;

            if (!resNode) outfile << "none\n";
            else outfile << resNode->id << " " << resNode->s << " " << resNode->e << "\n";
        }
    }

    infile.close();
    outfile.close();

    cout << "operation, count, total_ns, average_ns\n";
    cout << "add, " << add_cnt << ", " << (long long)add_time << ", " << (add_cnt ? to_string((long long)(add_time / add_cnt)) : "N/A") << "\n";
    cout << "remove, " << remove_cnt << ", " << (long long)remove_time << ", " << (remove_cnt ? to_string((long long)(remove_time / remove_cnt)) : "N/A") << "\n";
    cout << "update, " << update_cnt << ", " << (long long)update_time << ", " << (update_cnt ? to_string((long long)(update_time / update_cnt)) : "N/A") << "\n";
    cout << "conflict, " << conflict_cnt << ", " << (long long)conflict_time << ", " << (conflict_cnt ? to_string((long long)(conflict_time / conflict_cnt)) : "N/A") << "\n";
    cout << "overlaps, " << overlaps_cnt << ", " << (long long)overlaps_time << ", " << (overlaps_cnt ? to_string((long long)(overlaps_time / overlaps_cnt)) : "N/A") << "\n";
    cout << "at, " << at_cnt << ", " << (long long)at_time << ", " << (at_cnt ? to_string((long long)(at_time / at_cnt)) : "N/A") << "\n";
    cout << "next, " << next_cnt << ", " << (long long)next_time << ", " << (next_cnt ? to_string((long long)(next_time / next_cnt)) : "N/A") << "\n";

    return 0;
}