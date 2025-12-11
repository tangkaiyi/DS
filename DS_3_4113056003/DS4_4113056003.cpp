#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 500001;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int v) : val(v), left(NULL), right(NULL) {}
};

struct Task {
    TreeNode* parent;
    bool isLeft;
    int l, r;
};

int inorderPos[MAXN];
int subtreeSize[MAXN];
TreeNode* targetNode = NULL;

int countSize(TreeNode* node) {
    if (!node) return 0;
    int s = 1 + countSize(node->left) + countSize(node->right);
    subtreeSize[node->val] = s;
    return s;
}

TreeNode* buildTree(int n, const vector<int>& levelOrder, int targetX) {
    if (n == 0) return NULL;

    TreeNode* root = new TreeNode(levelOrder[0]);
    if (root->val == targetX) targetNode = root;

    queue<Task> q;
    int rootIdx = inorderPos[root->val];

    if (0 <= rootIdx - 1)
        q.push({root, true, 0, rootIdx - 1});
    if (rootIdx + 1 <= n - 1)
        q.push({root, false, rootIdx + 1, n - 1});

    int currentLevelIdx = 1;

    while (!q.empty() && currentLevelIdx < n) {
        Task task = q.front();
        q.pop();

        int val = levelOrder[currentLevelIdx++];
        TreeNode* newNode = new TreeNode(val);

        if (val == targetX) targetNode = newNode;

        if (task.isLeft) {
            task.parent->left = newNode;
        } else {
            task.parent->right = newNode;
        }

        int currIdx = inorderPos[val];

        if (task.l <= currIdx - 1) {
            q.push({newNode, true, task.l, currIdx - 1});
        }
        if (currIdx + 1 <= task.r) {
            q.push({newNode, false, currIdx + 1, task.r});
        }
    }
    return root;
}

void solve_case() {
    int targetX, n;
    if (!(cin >> targetX >> n)) return;

    targetNode = NULL;

    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        inorderPos[val] = i;
    }

    vector<int> levelOrder(n);
    for (int i = 0; i < n; i++) {
        cin >> levelOrder[i];
    }

    TreeNode* root = buildTree(n, levelOrder, targetX);
    countSize(root);

    bool canWin = false;
    if (targetNode) {
        int leftSize = (targetNode->left) ? subtreeSize[targetNode->left->val] : 0;
        int rightSize = (targetNode->right) ? subtreeSize[targetNode->right->val] : 0;
        int parentSize = n - subtreeSize[targetX];

        if (leftSize > n / 2 || rightSize > n / 2 || parentSize > n / 2) {
            canWin = true;
        }
    }
    
    cout << (canWin ? "1" : "0") << "\n";
}

int main() {
    if(!freopen("testcase4.txt","r",stdin)) return -1;
    if(!freopen("output4.txt","w",stdout)) return -1;

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        while (t--) {
            solve_case();
        }
    }
    return 0;
}