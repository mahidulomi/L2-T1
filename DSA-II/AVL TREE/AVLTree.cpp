#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

class AVLTree {
private:
    struct Node {
        int key;
        Node* left;
        Node* right;
        int height;

        Node(int val) : key(val), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    int getHeight(Node* n) {
        return (n == nullptr) ? 0 : n->height;
    }

    int getBalanceFactor(Node* n) {
        return (n == nullptr) ? 0 : getHeight(n->left) - getHeight(n->right);
    }

    void updateHeight(Node* n) {
        if (n != nullptr) {
            n->height = 1 + max(getHeight(n->left), getHeight(n->right));
        }
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node* insertHelper(Node* node, int key, bool& inserted) {
        if (node == nullptr) {
            inserted = true;
            return new Node(key);
        }

        if (key < node->key)
            node->left = insertHelper(node->left, key, inserted);
        else if (key > node->key)
            node->right = insertHelper(node->right, key, inserted);
        else {
            inserted = false; // Duplicate
            return node;
        }

        updateHeight(node);
        int balance = getBalanceFactor(node);

        // LL Case
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        // RR Case
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        // LR Case
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // RL Case
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* getMinValueNode(Node* node) {
        Node* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    Node* eraseHelper(Node* node, int key, bool& erased) {
        if (node == nullptr) {
            erased = false;
            return node;
        }

        if (key < node->key)
            node->left = eraseHelper(node->left, key, erased);
        else if (key > node->key)
            node->right = eraseHelper(node->right, key, erased);
        else {
            erased = true;
            if ((node->left == nullptr) || (node->right == nullptr)) {
                Node* temp = node->left ? node->left : node->right;
                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                Node* temp = getMinValueNode(node->right);
                node->key = temp->key;
                node->right = eraseHelper(node->right, temp->key, erased);
            }
        }

        if (node == nullptr) return node;

        updateHeight(node);
        int balance = getBalanceFactor(node);

        // Deletion Balancing Rules (Includes Balance Factor = 0)
        // LL Case
        if (balance > 1 && getBalanceFactor(node->left) >= 0)
            return rightRotate(node);

        // LR Case
        if (balance > 1 && getBalanceFactor(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // RR Case
        if (balance < -1 && getBalanceFactor(node->right) <= 0)
            return leftRotate(node);

        // RL Case
        if (balance < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    bool findHelper(Node* node, int key) {
        if (node == nullptr) return false;
        if (node->key == key) return true;
        if (key < node->key) return findHelper(node->left, key);
        return findHelper(node->right, key);
    }

    void traverseHelper(Node* node, vector<int>& res) {
        if (node != nullptr) {
            traverseHelper(node->left, res);
            res.push_back(node->key);
            traverseHelper(node->right, res);
        }
    }

    string toParenthesesFormat(Node* node) {
        if (node == nullptr) return "";
        if (node->left == nullptr && node->right == nullptr) {
            return to_string(node->key);
        }
        string leftStr = toParenthesesFormat(node->left);
        string rightStr = toParenthesesFormat(node->right);
        return to_string(node->key) + "(" + leftStr + "," + rightStr + ")";
    }

    void destroyTree(Node* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    AVLTree() : root(nullptr) {}

    ~AVLTree() {
        destroyTree(root);
    }

    bool insert(int key) {
        bool inserted = false;
        root = insertHelper(root, key, inserted);
        return inserted;
    }

    bool erase(int key) {
        bool erased = false;
        root = eraseHelper(root, key, erased);
        return erased;
    }

    bool find(int key) {
        return findHelper(root, key);
    }

    vector<int> traverse() {
        vector<int> res;
        traverseHelper(root, res);
        return res;
    }

    string getParenthesesRepresentation() {
        return toParenthesesFormat(root);
    }
};

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: ./avl_tree <input-file> <output-file>" << endl;
        return 1;
    }

    ifstream inFile(argv[1]);
    ofstream outFile(argv[2]);

    if (!inFile || !outFile) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    AVLTree tree;

    // Timing Variables
    long long insert_ns = 0, delete_ns = 0, find_ns = 0, traverse_ns = 0;
    int insert_cnt = 0, delete_cnt = 0, find_cnt = 0, traverse_cnt = 0;

    char op;
    int key;

    while (inFile >> op) {
        if (op == 'I') {
            inFile >> key;
            auto start = chrono::steady_clock::now();
            bool ok = tree.insert(key);
            auto end = chrono::steady_clock::now();
            insert_ns += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            insert_cnt++;

            if (ok) outFile << tree.getParenthesesRepresentation() << "\n";
            else outFile << "duplicate\n";
        }
        else if (op == 'D') {
            inFile >> key;
            auto start = chrono::steady_clock::now();
            bool ok = tree.erase(key);
            auto end = chrono::steady_clock::now();
            delete_ns += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            delete_cnt++;

            if (ok) outFile << tree.getParenthesesRepresentation() << "\n";
            else outFile << "not found\n";
        }
        else if (op == 'F') {
            inFile >> key;
            auto start = chrono::steady_clock::now();
            bool ok = tree.find(key);
            auto end = chrono::steady_clock::now();
            find_ns += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            find_cnt++;

            if (ok) outFile << "found\n";
            else outFile << "not found\n";
        }
        else if (op == 'T') {
            auto start = chrono::steady_clock::now();
            vector<int> res = tree.traverse();
            auto end = chrono::steady_clock::now();
            traverse_ns += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            traverse_cnt++;

            for (size_t i = 0; i < res.size(); i++) {
                outFile << res[i] << (i + 1 == res.size() ? "" : " ");
            }
            outFile << "\n";
        }
    }

    // Console (stdout) Timing Report
    cout << "operation,count,total_ns,average_ns\n";
    cout << "insert," << insert_cnt << "," << insert_ns << "," 
         << (insert_cnt ? to_string(insert_ns / insert_cnt) : "N/A") << "\n";
    cout << "delete," << delete_cnt << "," << delete_ns << "," 
         << (delete_cnt ? to_string(delete_ns / delete_cnt) : "N/A") << "\n";
    cout << "find," << find_cnt << "," << find_ns << "," 
         << (find_cnt ? to_string(find_ns / find_cnt) : "N/A") << "\n";
    cout << "traverse," << traverse_cnt << "," << traverse_ns << "," 
         << (traverse_cnt ? to_string(traverse_ns / traverse_cnt) : "N/A") << "\n";
  
    inFile.close();
    outFile.close();
    return 0;
}

/*
g++ AVLTree.cpp -o avl_tree
g++ -O2 IntervalScheduler.cpp -o IntervalScheduler
.\AVLTree.exe testcase_avl.txt my_output_avl.txt
.\IntervalScheduler.exe testcase_basic_interval.txt output_avl.txt
.\IntervalScheduler.exe testcase_edge_interval.txt output_edge.txt
.\IntervalScheduler.exe testcase_large_interval.txt output_large.txt
*/

