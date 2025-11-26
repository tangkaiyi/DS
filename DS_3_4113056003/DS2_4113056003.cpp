#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

int stations = 0;

int dfs(TreeNode* node) {
    if (!node) return 0;

    int leftState = dfs(node->left);
    int rightState = dfs(node->right);

    if (leftState == 2 || rightState == 2) {
        stations++;
        return 1;
    }
    if (leftState == 1 || rightState == 1) {
        return 0;
    }

    return 2;
}

TreeNode* buildTree(const string& data) {
    if (data.empty()) return nullptr;
    
    stringstream ss(data);
    string segment;
    vector<string> nodes;
    while (getline(ss, segment, ',')) {
        nodes.push_back(segment);
    }

    if (nodes.empty() || nodes[0] == "N") return nullptr;

    TreeNode* root = new TreeNode(0);
    queue<TreeNode*> q;
    q.push(root);

    int i = 1;
    while (!q.empty() && i < nodes.size()) {
        TreeNode* curr = q.front();
        q.pop();

        if (i < nodes.size() && nodes[i] != "N") {
            curr->left = new TreeNode(0);
            q.push(curr->left);
        }
        i++;

        if (i < nodes.size() && nodes[i] != "N") {
            curr->right = new TreeNode(0);
            q.push(curr->right);
        }
        i++;
    }
    return root;
}

int main() {
    if (freopen("testcase2.txt", "r", stdin) == NULL) {
       fprintf(stderr, "Error: Input file not found\n");
    return 1;
    }
    if (freopen("output2.txt", "w", stdout) == NULL) {
        fprintf(stderr, "Error: Unable to create output file\n");
        return 1;
    }

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        string dummy;
        getline(cin, dummy);
        while (t--) {
            string line;
            getline(cin, line);

            stations = 0;
            TreeNode* root = buildTree(line);
            
            if (root) {
                int rootState = dfs(root);
                if (rootState == 2) {
                    stations++;
                }
            }
            
            cout << stations << "\n";
        }
    }
    return 0;
}